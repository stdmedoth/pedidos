#!/bin/bash

#atualizacao rapida de arquivos para o sistema

cp -r data/* /usr/share/petitto/files/
cp -r data/Petitto.desktop /usr/share/applications
gcc src/Inicio/Petitto.c -o /usr/bin/petitto `pkg-config --libs --cflags gtk+-3.0 mysqlclient` -g -Wall -Wredundant-decls -Wuninitialized -g -Wreturn-type  -Wpedantic #-Wconversion -Wextra 

