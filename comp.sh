#!/bin/bash
gcc src/Inicio/Petitto.c -o /usr/share/petitto/bin/Petitto `pkg-config --libs --cflags gtk+-3.0 mysqlclient` -g -Wall #-Wextra 
