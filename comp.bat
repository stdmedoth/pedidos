@ECHO OFF
C:\windows\system32\Xcopy /E /I data C:\pedidos\files
set PATH=;C:\gnu\lib\pkgconfig;C:\gnu\bin;C:\gnu\include;C:\gnu\lib;C:\gnu\bin;C:\gnu\bin;;C:\gnu\lib;C:\gnu\include"

ECHO COMPILANDO
C:\gnu\bin\gcc src/Inicio/Pedidos.c -o C:\gnu\bin\Pedidos -g -LC:\gnu\lib -IC:\gnu\include -llibmysql -mms-bitfields -IC:/gnu/include/gtk-3.0 -IC:/gnu/include/atk-1.0 -IC:/gnu/include -IC:/gnu/include/cairo -IC:/gnu/include/gdk-pixbuf-2.0 -IC:/gnu/include/glib-2.0 -IC:/gnu/lib/glib-2.0/include -IC:/gnu/include/pango-1.0 -IC:/gnu/include/pixman-1 -IC:/gnu/include/freetype2 -IC:/gnu/include/libpng16  -Wl,-luuid -LC:/gnu/lib -lgtk-3 -lgdk-3 -lgdi32 -limm32 -lshell32 -lole32 -lwinmm -lsetupapi -lcfgmgr32 -lz -latk-1.0 -lgio-2.0 -lpangowin32-1.0 -llibcurl -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo -lgobject-2.0 -llibxml2 -lglib-2.0 -lintl  -static-libgcc
pause
