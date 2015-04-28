/* c3status sample config file */

/* Items' declaration
 * Each item to be displayed on the status bar have to be declared here with the following syntax:
 * <item_type> <item_name>;
 * Some examples below, see man page for type list */
date d;
volume v;
mem m;
cpu c;
fs home;
fs root;
net n;

/* Global & items' configuration
 * Every attribute of every item have a default value that will be used if the value is not user-defined here
 * Syntax is the following:
 * <item_name>.<attribute> = <value>;
 * <value> is either a numerical value (e.g: 1), a simple quoted character (e.g: 'a') or a double quoted string (e.g: "abc)
 * See man page for per-item full attribute list and more infos */
void conf(void) {

	/* These are global c3status options (i.e: they are not attributes to an item)
	 * See man page for full list */
	label_color = "#767676";
	data_color = "#cccccc";

	/* These are items' configuration */
	d.format = "%d/%m/%Y - %H:%M";

	c.load_pcent_enable = 1;
	c.temperature_enable = 1;

	n.interface = "eth0";
	n.unit = 'o';

	home.mount_point = "/home";
	root.mount_point = "/";
}

/* Display of items
 * Syntax is the following:
 * display_<item_type>(&<item_name>); */
void update(void) {

	display_fs(&root);
	display_fs(&home);
	display_net(&n);
	display_cpu(&c);
	display_mem(&m);
	display_volume(&v);
	display_date(&d);
}
