ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    detected_OS := Windows
else
    detected_OS := $(shell uname)  # same as "uname -s"
endif

MINGWCC=x86_64-w64-mingw32-gcc

ifeq ($(detected_OS),Windows)
CC=$(MINGWCC)
CURLFLAGS=-llibcurl
BDFLAGS=-llibmysql
SOFLAGS=-lws2_32
endif

ifeq ($(detected_OS),Linux  )
CC=gcc
CURLFLAGS=`pkg-config --libs --cflags  libcurl`
BDFLAGS=-I /usr/include/mysql -l mysqlclient
SOFLAGS=
endif

PEDFLAGS=-I src/etc/
GTKFLAGS=`pkg-config --libs --cflags gtk+-3.0`
#BDFLAGS=`pkg-config --libs --cflags mysqlclient`

XMLFLAGS=`pkg-config --libs --cflags  libxml-2.0`
JSONFLAGS=`pkg-config --libs --cflags  json-glib-1.0`

CCFLAGS1=-Wall -Wredundant-decls -Wuninitialized -Wreturn-type -Wno-deprecated-declarations
CCFLAGS2=-Wpedantic -O0 -Woverflow -Wno-write-strings -Wfatal-errors -Wformat-overflow  
CCFLAGS3=-Wunused-variable 
DEBUG=-g
ALLFLAGS=$(PEDFLAGS) $(GTKFLAGS) $(BDFLAGS) $(XMLFLAGS) $(CURLFLAGS) $(JSONFLAGS) $(CCFLAGS1) $(CCFLAGS2) $(CCFLAGS3) $(DEBUG) $(SOFLAGS)


TARGET_FILE=src/Pedidos/Pedidos.c

ifeq ($(detected_OS),Windows)
RESULT_FILE=PedidosSemConsole
RESULT_FILE_CONSOLE=PedidosComConsole
endif

ifeq ($(detected_OS),Linux  )
RESULT_FILE=pedidos
RESULT_FILE_CONSOLE=pedidos
endif

OBJS=Pedidos.o

COMPILE_ENV=$(detected_OS)


COPY_FILES=data
DIR_ROOT=/usr/share/pedidos/
DIR_FILES=/usr/share/pedidos/files
DIR_BIN=/bin/


all: $(OBJS) $(COMPILE_ENV)


Linux:
	echo $(detected_OS);
	$(CC) $(OBJS) -o $(RESULT_FILE) $(ALLFLAGS)

Windows:
	$(CC) $(OBJS) -o $(RESULT_FILE) $(ALLFLAGS) -mwindows
	$(CC) $(OBJS) -o $(RESULT_FILE_CONSOLE) $(ALLFLAGS)

Pedidos.o:
	$(CC) $(TARGET_FILE) -c $(ALLFLAGS)

clear:
	rm *.o *.gcda $(RESULT_FILE) $(RESULT_FILE_CONSOLE)

install:
	mkdir -p $(DIR_FILES)
	cp -r $(COPY_FILES)/* $(DIR_FILES)
	cp -r $(RESULT_FILE) $(DIR_BIN)
	chmod -R 777 $(DIR_FILES)


# build do migrate wrapper
BUILD_MGRT_FLAGS=-I build_migrate
BUILD_MGRT_OBJ=migrate.o portable.o
BUILD_MGRT_TARGET=build_migrate/migrate.c
BUILD_MGRT_RESULT=migrate

migrate.o:
	$(CC) $(BUILD_MGRT_TARGET) -c  $(ALLFLAGS) $(BUILD_MGRT_FLAGS)

portable.o: 
	$(CC) src/etc/portable.c -c  $(ALLFLAGS) $(BUILD_MGRT_FLAGS)

build_migrate: $(BUILD_MGRT_OBJ)
	$(CC) $(BUILD_MGRT_OBJ) -o $(BUILD_MGRT_RESULT) $(ALLFLAGS) $(BUILD_MGRT_FLAGS)
