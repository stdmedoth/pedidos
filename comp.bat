@ECHO OFF
C:\windows\system32\Xcopy /E /I data C:\petitto\files
set PATH=;C:\gtk\lib\pkgconfig;C:\gtk\bin;C:\gtk\include;C:\gtk\lib;C:\petitto\gtk\bin;"

ECHO COMPILANDO
gcc src/Inicio/Petitto.c -o C:\gtk\bin\Petitto -g -Wfatal-errors -LC:\gtk\lib -IC:\gtk\include -llibmysql -mms-bitfields -IC:/gtk/include/gtk-3.0 -IC:/gtk/include/atk-1.0 -IC:/gtk/include -IC:/gtk/include/cairo -IC:/gtk/include/gdk-pixbuf-2.0 -IC:/gtk/include/glib-2.0 -IC:/gtk/lib/glib-2.0/include -IC:/gtk/include/pango-1.0 -IC:/gtk/include/pixman-1 -IC:/gtk/include/freetype2 -IC:/gtk/include/libpng16  -Wl,-luuid -LC:/gtk/lib -lgtk-3 -lgdk-3 -lgdi32 -limm32 -lshell32 -lole32 -lwinmm -lsetupapi -lcfgmgr32 -lz -latk-1.0 -lgio-2.0 -lpangowin32-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo -lgobject-2.0 -llibxml2 -lglib-2.0 -lintl  -static-libgcc
pause
