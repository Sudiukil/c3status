# c3status

c3status is a simple status bar for i3wm written in C.

The main goal of c3status is to be simple to understand and easily extensible by writing functions and recompile the code, which allow you to display almost anything in your status bar.
c3status is designed to be as lightweight as possible by using system calls and by getting info at a low level without needing to run shell commands.

## Current and planned features

Even if c3status aims to be extensible by anyone using it, I obviously wrote some functions for my personal use, and I plan to write some more, here is what is currently available and what will probably be:

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
  - [x] Network download and upload speed
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
  - [x] Better command line arguments handling
  - [ ] Real config file (instead of config.h + recompile)

## How to build, install and use c3status

### Dependencies

To build c3status you will need to install a few dependencies which are Alsa and Wireless-tools development files.
Under Debian 8 "Jessie" you can have those by installing the following packages:

```
libasound2-dev
libiw-dev
```

You can install those with:

```
apt-get install libasound2-dev libiw-dev
```

Additionally, if you want to rebuild the man page of c3status, you will need those packages:

```
asciidoc
libxml2-utils
docbook-xml
xsltproc
```

Note that you should use `apt-get install --no-install-recommends` for installing the asciidoc as apt-get will try to install a **lot** of recommended yet useless packages.

Note that those packages should be available under any Linux distribution, though their names may vary.

### Building and installing

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
