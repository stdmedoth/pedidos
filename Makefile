CC=gcc

GTKFLAGS=`pkg-config --libs --cflags gtk+-3.0`
BDFLAGS=`pkg-config --libs --cflags mariadb`
XMLFLAGS=`pkg-config --libs --cflags  libxml-2.0`
JSONFLAGS=`pkg-config --libs --cflags  json-glib-1.0`
CURLFLAGS=`pkg-config --libs --cflags  libcurl`
CCFLAGS=-Wall -Wredundant-decls -Wuninitialized -g -Wreturn-type  -Wpedantic -O0  -fprofile-generate -Wno-write-strings#-Wfatal-errors
ALLFLAGS=$(GTKFLAGS) $(BDFLAGS) $(XMLFLAGS) $(CURLFLAGS) $(JSONFLAGS) $(CCFLAGS)

TARGET_FILE=Pedidos.c
RESULT_FILE=pedidos

OBJS=Pedidos.o

COPY_FILES=data
DIR_ROOT=/usr/share/pedidos/
DIR_FILES=/usr/share/pedidos/files
DIR_BIN=/bin/

all: $(OBJS)
	$(CC) $(OBJS) -o $(RESULT_FILE) $(ALLFLAGS)

Pedidos.o:
	$(CC) src/Inicio/$(TARGET_FILE) -c  $(ALLFLAGS)

clear:
	rm *.o *.gcda $(RESULT_FILE)

install:
	mkdir -p $(DIR_FILES)
	cp -r $(COPY_FILES)/* $(DIR_FILES)
	cp -r $(RESULT_FILE) $(DIR_BIN)
