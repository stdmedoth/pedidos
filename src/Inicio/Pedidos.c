#define DEBUG
#define QUERY_DEBUG

#ifdef DEBUG
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <gtk/gtk.h>
#include <libxml/xinclude.h>
#include <cairo/cairo-pdf.h>
#include <curl/curl.h>
#include <libxml/xpath.h>
#include <time.h>

#ifdef __linux__
#include <mariadb/mysql.h>
#endif

#ifdef WIN32
#include <windows.h>
#include <mysql/mysql.h>
#endif

#include "../etc/libs.h"
#include "../etc/libs.c"

int main(int argc,char *argv[])
{

	gtk_disable_setlocale();
	//setlocale(LC_ALL,"");
	setlocale(LC_COLLATE,"pt_BR");
	//setlocale(LC_CTYPE,"pt_BR");
	setlocale(LC_MONETARY,"en_US");
	setlocale(LC_NUMERIC,"en_US");

	gtk_init(&argc, &argv);

	if(rec_vars_from_file())
		return 1;

	load_styles();

	janelas_gerenciadas.aplicacao.criada = 0;

	if(init())
		return 1;

	gtk_main();
	return 0;
}
