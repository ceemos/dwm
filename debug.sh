#!/bin/bash
clang -o dwm -g3 -std=c99 -pedantic -Wall -Wno-deprecated-declarations -I/usr/X11R6/include -I/usr/include/freetype2 -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION='"6.1"' -DXINERAMA -L/usr/X11R6/lib -lX11 -lXinerama -lXft dwm.c util.c drw.c
Xephyr -ac -br -noreset -screen 1024x768 :1.0 &
sleep 1
DISPLAY=:1.0 gdb ./dwm