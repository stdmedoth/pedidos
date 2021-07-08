x86_64-w64-mingw32-gcc src/Pedidos/Pedidos.c -o PedidosSemConsole `pkg-config --libs --cflags libxml-2.0 gtk+-3.0` -llibmysql -lws2_32 -llibcurl -mwindows -I src/etc
x86_64-w64-mingw32-gcc src/Pedidos/Pedidos.c -o PedidosComConsole `pkg-config --libs --cflags libxml-2.0 gtk+-3.0` -llibmysql -lws2_32 -llibcurl -g -I src/etc
