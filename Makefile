CC=gcc

PEDFLAGS=-I src/etc/
GTKFLAGS=`pkg-config --libs --cflags gtk+-3.0`
#BDFLAGS=`pkg-config --libs --cflags mysqlclient`
BDFLAGS=-I /usr/include/mysql -l mysqlclient
XMLFLAGS=`pkg-config --libs --cflags  libxml-2.0`
JSONFLAGS=`pkg-config --libs --cflags  json-glib-1.0`
CURLFLAGS=`pkg-config --libs --cflags  libcurl`
CCFLAGS1=-Wall -Wredundant-decls -Wuninitialized -Wreturn-type -Wno-deprecated-declarations
CCFLAGS2=-Wpedantic -O0 -Woverflow -Wno-write-strings -Wfatal-errors -Wformat-overflow  
CCFLAGS3=-Wunused-variable 
DEBUG=-g
ALLFLAGS=$(PEDFLAGS) $(GTKFLAGS) $(BDFLAGS) $(XMLFLAGS) $(CURLFLAGS) $(JSONFLAGS) $(CCFLAGS1) $(CCFLAGS2) $(CCFLAGS3) $(DEBUG)


BUILD_MGRT_FLAGS=-I build_migrate
BUILD_MGRT_OBJ=migrate.o
BUILD_MGRT_TARGET=build_migrate/migrate.c
BUILD_MGRT_RESULT=migrate

TARGET_FILE=src/Pedidos/Pedidos.c
RESULT_FILE=pedidos

OBJS=Pedidos.o

COPY_FILES=data
DIR_ROOT=/usr/share/pedidos/
DIR_FILES=/usr/share/pedidos/files
DIR_BIN=/bin/

all: $(OBJS)
	$(CC) $(OBJS) -o $(RESULT_FILE) $(ALLFLAGS)

Pedidos.o:
	$(CC) $(TARGET_FILE) -c  $(ALLFLAGS)

clear:
	rm *.o *.gcda $(RESULT_FILE)

install:
	mkdir -p $(DIR_FILES)
	cp -r $(COPY_FILES)/* $(DIR_FILES)
	cp -r $(RESULT_FILE) $(DIR_BIN)
	chmod -R 777 $(DIR_FILES)

migrate.o:
	$(CC) $(BUILD_MGRT_TARGET) -c  $(ALLFLAGS) $(BUILD_MGRT_FLAGS)

build_migrate: migrate.o
	$(CC) $(BUILD_MGRT_TARGET) -o $(BUILD_MGRT_RESULT) $(ALLFLAGS) $(BUILD_MGRT_FLAGS)
