@ECHO OFF
C:\windows\system32\Xcopy /E /I data C:\petitto\data
IF NOT EXIST C:\petitto\data\var.txt (
ECHO variavel ja criada > C:\petitto\data\var.txt
setx PATH "%PATH%;C:\petitto\gnu\lib\pkgconfig;C:\petitto\gnu\bin;C:\petitto\gnu\include;C:\petitto\gnu\lib;C:\petitto\gtk\bin;"
)
ECHO COMPILANDO
gcc src/Inicio/Petitto.c -o C:\petitto\gtk\bin\Petitto -LC:\petitto\mysql\lib -IC:\petitto\mysql\include -llibmysql -mms-bitfields -IC:/petitto/gtk/include/gtk-3.0 -IC:/petitto/gtk/include/cairo -IC:/petitto/gtk/include/pango-1.0 -IC:/petitto/gtk/include/atk-1.0 -IC:/petitto/gtk/include/cairo -IC:/petitto/gtk/include/pixman-1 -IC:/petitto/gtk/include -IC:/petitto/gtk/include/freetype2 -IC:/petitto/gtk/include -IC:/petitto/gtk/include/libpng15 -IC:/petitto/gtk/include/gdk-pixbuf-2.0 -IC:/petitto/gtk/include/libpng15 -IC:/petitto/gtk/include/glib-2.0 -IC:/petitto/gtk/lib/glib-2.0/include -LC:/petitto/gtk/lib -lgtk-3 -lgdk-3 -lgdi32 -limm32 -lshell32 -lole32 -Wl,-luuid -lpangocairo-1.0 -lpangoft2-1.0 -lfreetype -lfontconfig -lpangowin32-1.0 -lgdi32 -lpango-1.0 -lm -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl 
pause
