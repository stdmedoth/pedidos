#!/bin/bash
#./comp.sh para dar permissões de leitura e escrita na pasta de arquivos
#atualizacao rapida de arquivos para o sistema

if [ "$1" == "mover" ]
then
if [ ! -d "/usr/share/pedidos" ]; then
mkdir /usr/share/pedidos
fi
if [ ! -d "/usr/share/pedidos/files" ]; then
mkdir /usr/share/pedidos/files
fi
echo "Movendo files..."
cp -r data/* /usr/share/pedidos/files/
echo "Movendo icone..."
cp -r data/Petitto.desktop /usr/share/applications
fi
if [ "$1" == "perm" ]
then
echo "mudando permissões..."
chmod 777 /usr/share/pedidos/files -R
fi
echo "compilando..."
gcc src/Inicio/Pedidos.c -o /usr/bin/pedidos `pkg-config --libs --cflags gtk+-3.0 mariadb libxml-2.0 libcurl` -Wall -Wredundant-decls -Wuninitialized -g -Wreturn-type  -Wpedantic -O0 #-Wshadow #-Wmissing-prototypes #-Wstrict-prototypes #-Wconversion #-Wextra -Wfatal-errors
