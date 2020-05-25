@ECHO OFF
C:\windows\system32\Xcopy /E /I data C:\petitto\files
set PATH=;C:\petitto\gnu\lib\pkgconfig;C:\petitto\gnu\bin;C:\petitto\gnu\include;C:\petitto\gnu\lib;C:\petitto\gtk\bin;"

ECHO COMPILANDO
gcc src/Inicio/Petitto.c -o C:\gtk\bin\Petitto -LC:\petitto\mysql\lib -IC:\petitto\mysql\include -llibmysql -mms-bitfields -IC:/gtk/include/gtk-3.0 -IC:/gtk/include/atk-1.0 -IC:/gtk/include -IC:/gtk/include/cairo -IC:/gtk/include/gdk-pixbuf-2.0 -IC:/gtk/include/glib-2.0 -IC:/gtk/lib/glib-2.0/include -IC:/gtk/include/pango-1.0 -IC:/gtk/include/pixman-1 -IC:/msys/opt/include -IC:/msys/opt/include/freetype2 -IC:/msys/opt/include/libpng16 -IC:/gtk/include/freetype2 -IC:/gtk/include/libpng16  -Wl,-luuid -LC:/gtk/lib -lgtk-3 -lgdk-3 -lgdi32 -limm32 -lshell32 -lole32 -lwinmm -lsetupapi -lcfgmgr32 -lz -latk-1.0 -lgio-2.0 -lpangowin32-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo -lgobject-2.0 -lglib-2.0 -lintl  
pause
