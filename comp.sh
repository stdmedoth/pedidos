#!/bin/bash
cp -r data/* /usr/share/petitto/files/
gcc src/Inicio/Petitto.c -o /usr/share/petitto/bin/Petitto `pkg-config --libs --cflags gtk+-3.0 mysqlclient` -g -Wall # -Wextra 

