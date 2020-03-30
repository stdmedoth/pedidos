#include <stdio.h>
#include <errno.h>
#include <gtk/gtk.h>
#ifdef __linux__
#include <mysql/mysql.h>
#endif
#include <time.h>
#ifdef WIN32
#include <windows.h>
#include <mysql.h>
#endif
GtkWidget  *janela_principal;
#include "../etc/libs.h"
//#include "../etc/tipo_listagem.c"


GtkWidget *superior, *superior_1, *superior_2;
GtkWidget *inferior, *inferior_1, *inferior_2;
GtkWidget *area_de_trabalho;
GtkWidget *barra;

GtkWidget *imagem_barra,*layout_barra;
#include "../Menu/icones.h"
#include "../Menu/abas.c"
#include "init.c"
int main(int argc,char *argv[])
{
	gtk_init(&argc,&argv);
	abrir_css(DESKTOP_STYLE);
	init();
	gtk_main();
	
}
