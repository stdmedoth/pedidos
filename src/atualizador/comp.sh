#!/bin/bash
gcc atualizador.c -o atualizador `pkg-config --libs --cflags gtk+-3.0 mysqlclient` -g -Wall -Wredundant-decls -Wuninitialized -g  #-Wextra 

