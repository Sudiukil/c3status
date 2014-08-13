# c3status

c3status is a simple status bar for i3wm written in C.

The main goal of c3status is to be simple to understand and easily extensible by writting functions and recompile the code, which allow you to display almost anything in your status bar.

c3status is probably useless without slight modifications for now because it was originally written for my personal use only and is absolutely not optimized, but now it's "just working" i'll continue to work on it to make it better.

## Current and planned features

Even if c3status aims to be extensible by anyone using it, i obviously wrote some functions for my personal use, and i plan to write some more, here is what is currently available and what will probably be:

- [x] Basic infos:
  - [x] System time and/or date
  - [x] Alsa volume

- System infos:
  - [x] CPU usage
  - [x] CPU temperature
  - [x] RAM usage (in %)
  - [ ] GPU temperature
  - [x] Disks usage (in %)

- Network infos:
  - [x] Network speed
  - [ ] Wifi infos (SSID, percentage, etc...)

- Battery infos:
  - [x] Battery pcent
  - [x] Battery state
  - [ ] Possibily to select another battery than BAT0
  - [ ] Remaining time on battery

- Other infos:
  - [x] ncmpcpp current playing music
  - [x] moc current playing music

- Other things to do:
  - [ ] Real makefile
  - [ ] Cleaner and easier way to configure c3status (main C file is currently the only way to configure it)

## How to install and use c3status

The installation process for c3status is quite rudimentary for now, you just have to download it, compile it and make i3wm use it. Following steps will do the job:

```
git clone "https://github.com/Sudiukil/c3status"
cd c3status
make
```

Then you need to modify the *status_command* line in you i3wm config file to use the c3status generated executable, as an example:

> status_command ~/.i3/c3status/c3status

if you cloned c3status repo in ~/.i3 .

## How to configure c3status

There is currently no config file, to change what is displayed by c3status you need to modify **c3status.c** (which is only containing display instructions anyway) and recompile it.

Provided **c3status.c** only displays system time and date so you can use it as a simple example and a base to add everything you want.

There are currently two steps to follow to display something:

1. Include the header file (.h) corresponding to what you want to display (ex: time.h is for system time): `#include "path_to_the_header"`
2. Use the `display()` function according to this specification:

```
char *str_data = char *function_returning_a_data();
display(
	char *name, 		//name of the data (ex: "cpu-temp")
	char *instance, 	//instance of the data (ex: "core 1")
	char *label, 		//label of the data (ex: "CPU1")
	str_data, 			//the data itself, previously stored in the str_data variable
	char *label_color, 	//the label display color (ex: "#ff0000")
	char *data_color, 	//the data display color (ex: "#ffff00")
	int priority, 		//priority of the data (defining it's color, should be handled by a function checking the data value)
	int is_last 		//set to 1 only in the last display() call
);
free(str_data);
```

See provided **c3status.c** for a concrete example.

## License

c3status is licensed under the ISC license, see LICENSE for complete copy.
