// Copyright (c) 2014, Quentin Sonrel (Sudiukil) <sudiukil@gmx.fr>
// File under the terms of the ISC license, see LICENSE (or http://opensource.org/licenses/ISC) for complete copy.

#include <alsa/asoundlib.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int *get_alsa_infos(char *selem_name) {

	snd_mixer_t *handle; //mixer handle
	snd_mixer_selem_id_t *sid; //mixer simple element id
	snd_mixer_selem_channel_id_t channel = SND_MIXER_SCHN_MONO; //simple element channel id
	snd_mixer_elem_t *elem; //mixer element
	const char *card = "default"; //card name

	long max, min, vol;
	int is_active;
	int *infos = calloc(2, sizeof(int));

	snd_mixer_open(&handle, 0); //open an empty mixer on the mixer handle
	snd_mixer_attach(handle, card); //attach the card to the handle
	snd_mixer_selem_register(handle, NULL, NULL); //register a simple element on the handle with no options
	snd_mixer_load(handle); //load the mixer elements

	snd_mixer_selem_id_alloca(&sid); //allocate the id for the simple element
	snd_mixer_selem_id_set_index(sid, 0); //set the index of the simple element
	snd_mixer_selem_id_set_name(sid, selem_name); //set the name of the simple element

	elem = snd_mixer_find_selem(handle, sid); //get the simple element from the handle

	snd_mixer_selem_get_playback_volume_range(elem, &min, &max); //get the volume range from the simple element
	snd_mixer_selem_get_playback_volume(elem, channel, &vol); //get the volume from the simple element

	snd_mixer_selem_get_playback_switch(elem, channel, &is_active); //get the simple element mixer status (muted or not)

	snd_mixer_close(handle); //close the mixer

	infos[0] = (int)round((float)vol/(float)max*100);
	infos[1] = is_active;

	return infos;
}

char *gen_alsa_str_volume_pcent(int *alsa_infos) {

	int pcent = alsa_infos[0];
	int is_active = alsa_infos[1];
	char *str_pcent = calloc(8, sizeof(char));

	if(is_active) {
		if(pcent<10) snprintf(str_pcent, 8, "0%d%%", pcent);
		else snprintf(str_pcent, 8, "%d%%", pcent);
	}
	else {
		if(pcent<10) snprintf(str_pcent, 8, "0%d%% [M]", pcent);
		else snprintf(str_pcent, 8, "%d%% [M]", pcent);
	}

	return str_pcent;
}

int test_alsa_volume_pcent(int *alsa_infos, int limit) {

	int pcent = alsa_infos[0];
	int is_active = alsa_infos[1];
	
	if(!is_active) return 1;
	if(pcent>limit) return 2;
	return 0;
}
