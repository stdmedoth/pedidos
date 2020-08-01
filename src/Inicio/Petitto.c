#define DEBUG
#define QUERY_DEBUG

#ifdef DEBUG
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#include <stdio.h>
#include <locale.h>
#include <errno.h>
#include <gtk/gtk.h>
#include <libxml/xinclude.h>
#include <time.h>

#ifdef __linux__
#include <mysql/mysql.h>
#endif

#ifdef WIN32
#include <windows.h>
#include <mysql.h>
#endif

static GtkWidget  *janela_principal;
static GtkWidget *imagem_desktop;
#include "../etc/libs.h"

static GtkWidget *superior, *superior_1, *superior_2;
static GtkWidget *inferior, *inferior_1, *inferior_2;
static GtkWidget *area_de_trabalho;
static GtkWidget *barra;

static GtkWidget *imagem_barra,*layout_barra;
#include "../Menu/icones.c"
#include "../Menu/abas.c"
#include "init.c"


int main(int argc,char *argv[])
{
	gtk_disable_setlocale();

	setlocale(LC_CTYPE,"pt_BR");
	setlocale(LC_COLLATE,"pt_BR");
	setlocale(LC_MONETARY,"en_US");
	setlocale(LC_NUMERIC,"en_US");

	gtk_init(&argc, &argv);

	if(rec_vars_from_file())
		return 1;

	abrir_css(DESKTOP_STYLE);
	if(init())
		return 1;

	gtk_main();
	return 0;
}
