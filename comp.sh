#!/bin/bash
#./comp.sh para dar permissões de leitura e escrita na pasta de arquivos
#atualizacao rapida de arquivos para o sistema

if [ "$1" == "mover" ]
then
if [ ! -d "/usr/share/petitto" ]; then
mkdir /usr/share/petitto
fi
if [ ! -d "/usr/share/petitto/files" ]; then
mkdir /usr/share/petitto/files
fi
echo "Movendo files..."
cp -r data/* /usr/share/petitto/files/
echo "Movendo icone..."
cp -r data/Petitto.desktop /usr/share/applications
fi
if [ "$1" == "perm" ]
then
echo "mudando permissões..."
chmod 777 /usr/share/petitto/files -R
fi
echo "compilando..."
gcc src/Inicio/Petitto.c -o /usr/bin/petitto `pkg-config --libs --cflags gtk+-3.0 mariadb libxml-2.0 libcurl` -Wall -Wredundant-decls -Wuninitialized -g -Wreturn-type  -Wpedantic -O0 #-Wshadow #-Wmissing-prototypes #-Wstrict-prototypes #-Wconversion #-Wextra -Wfatal-errors
