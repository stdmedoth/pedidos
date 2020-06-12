#!/bin/bash
#./comp.sh para dar permissões de leitura e escrita na pasta de arquivos
#atualizacao rapida de arquivos para o sistema

echo "Movendo files..."
cp -r data/* /usr/share/petitto/files/
echo "Movendo icone..."
cp -r data/Petitto.desktop /usr/share/applications

if [ "$1" == "perm" ]
then
echo "mudando permissões..."
chmod 777 /usr/share/petitto/files -R
fi
echo "compilando..."
gcc src/Inicio/Petitto.c -o /usr/bin/petitto `pkg-config --libs --cflags gtk+-3.0 mysqlclient` -g -Wall -Wredundant-decls -Wuninitialized -g -Wreturn-type  -Wpedantic #-Wshadow #-Wmissing-prototypes #-Wstrict-prototypes #-Wconversion #-Wextra 

