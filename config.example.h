// Object to configure and display
date d;
volume v;
battery b;
mem m;
cpu c;
fs home;
fs root;
wireless w;
net n;
music mu;

// Objects configuration, will only be called once
void conf(void) {

	label_color = "#767676";
	data_color = "#cccccc";

	d.format = "%d/%m/%Y - %H:%M:%S";	

	b.label = "BAT";

	c.load_pcent_enable = 1;
	c.temperature_enable = 1;

	n.interface = "enp4s0";
	n.unit = 'o';

	w.interface = "enp4s0";

	home.mount_point = "/home";
	root.mount_point = "/";

	mu.ncmpcpp = 1;
	mu.label = "♪";
}

// What to display in the status bar
void update(void) {

	display_music(&mu);
	display_fs(&root);
	display_fs(&home);
	display_wireless(&w);
	display_net(&n);
	display_cpu(&c);
	display_mem(&m);
	display_battery(&b);
	display_volume(&v);
	display_date(&d);
}
