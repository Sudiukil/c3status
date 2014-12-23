// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include "volume.h"
#include "display.h"

int *get_alsa_infos(const char *selem_name) {

	snd_mixer_t *handle; //mixer handle
	snd_mixer_selem_id_t *sid; //mixer simple element id
	snd_mixer_selem_channel_id_t channel = SND_MIXER_SCHN_MONO; //simple element channel id
	snd_mixer_elem_t *elem; //mixer element
	const char *card = "default"; //card name

	long max, min, vol;
	int is_active;
	int *infos = malloc(2*sizeof(int));

	snd_mixer_open(&handle, 0); //open an empty mixer on the mixer handle
	snd_mixer_attach(handle, card); //attach the card to the handle
	snd_mixer_selem_register(handle, NULL, NULL); //register a simple element on the handle with no options
	snd_mixer_load(handle); //load the mixer elements

	snd_mixer_selem_id_malloc(&sid); //allocate the id for the simple element
	snd_mixer_selem_id_set_index(sid, 0); //set the index of the simple element
	snd_mixer_selem_id_set_name(sid, selem_name); //set the name of the simple element

	elem = snd_mixer_find_selem(handle, sid); //get the simple element from the handle

	snd_mixer_selem_get_playback_volume_range(elem, &min, &max); //get the volume range from the simple element
	snd_mixer_selem_get_playback_volume(elem, channel, &vol); //get the volume from the simple element

	snd_mixer_selem_get_playback_switch(elem, channel, &is_active); //get the simple element mixer status (muted or not)

	infos[0] = (int)round((float)vol/(float)max*100);
	infos[1] = is_active;

	snd_mixer_selem_id_free(sid); //free the id for the simple element
	snd_mixer_free(handle); //unload and free the mixer elements
	snd_mixer_detach(handle, card); //detach the card from the handle
	snd_mixer_detach(handle, card); //detach the card from the handle
	snd_mixer_close(handle); //close the mixer

	snd_config_update_free_global(); //free the cache for global configuration to avoid memory leak

	return infos;
}

char *gen_alsa_str_volume_infos(int pcent, int is_active) {

	char *str_pcent = malloc(16*sizeof(char));

	if(is_active) {
		if(pcent<10) snprintf(str_pcent, 16, "0%d%%", pcent);
		else snprintf(str_pcent, 16, "%d%%", pcent);
	}
	else {
		if(pcent<10) snprintf(str_pcent, 16, "0%d%% [M]", pcent);
		else snprintf(str_pcent, 16, "%d%% [M]", pcent);
	}

	return str_pcent;
}

int test_alsa_volume_pcent(int pcent, int is_active, int limit) {

	if(!is_active) return 1;
	if(pcent>limit) return 2;
	return 0;
}

void update_volume(volume *v) {

	if(!(v->initialized)) {
		if(!(v->selem)) v->selem = "Master";
		if(!(v->label)) v->label = "VOL";
		if(!(v->limit)) v->limit = 75;
		v->initialized = 1;
	}

	int *alsa_infos = get_alsa_infos(v->selem);
	v->volume = alsa_infos[0];
	v->status = alsa_infos[1];
	free(alsa_infos);
}

void display_volume(volume *v) {

	char *alsa_infos;

	update_volume(v);

	alsa_infos = gen_alsa_str_volume_infos(v->volume, v->status);

	display("volume", v->selem, v->label, alsa_infos, test_alsa_volume_pcent(v->volume, v->status, v->limit));

	free(alsa_infos);
}
