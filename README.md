# c3status

c3status is a simple status bar for i3wm written in C.

The main goal of c3status is to be simple to understand and easily extensible by writing functions and recompile the code, which allow you to display almost anything in your status bar.
c3status is designed to be as lightweight as possible by using system calls and by getting info at a low level without needing to run shell commands.

## Current and planned features

Even if c3status aims to be extensible by anyone using it, i obviously wrote some functions for my personal use, and i plan to write some more, here is what is currently available and what will probably be:

- Basic infos:
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
  - [x] Wifi ESSID
  - [ ] Wifi signal percentage

- Battery infos:
  - [x] Battery percentage
  - [x] Battery state
  - [x] Possibility to select another battery than BAT0
  - [ ] Remaining time on battery

- Other infos:
  - [x] ncmpcpp current playing music
  - [x] moc current playing music

- Other things to do:
  - [x] Cleaner and easier way to configure c3status (main C file is currently the only way to configure it)
  - [x] Better errors handling
  - [x] Real makefile
  - [x] Man page

## How to install and use c3status

Installing c3status is quite easy:

```
$ git clone "https://github.com/Sudiukil/c3status"
$ cd c3status
# make install
```

Then you need to modify the *status_command* line in you i3wm config file to use c3status:

> status_command c3status

You can also specify an update interval in seconds (default is 1) with the '-t' option:

> status_command c3status -t 5

## How to configure c3status

To change what is displayed by c3status you need to edit a **config.h** file.

Provided **config.example.h** displays a few informations on the status bar and quickly explains how to write your **config.h**.
You can also see the man page for more info about the way to configure c3status.

## License

c3status is licensed under the ISC license, see LICENSE for complete copy.
