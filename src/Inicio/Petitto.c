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
	#ifdef WIN32
		FreeConsole();
	#endif
	gtk_init(&argc,&argv);
	abrir_css(DESKTOP_STYLE);
	init();
	g_signal_connect(GTK_WIDGET(janela_principal),"key_press_event",G_CALLBACK(tecla_menu),NULL);
	g_signal_connect(GTK_WIDGET(botao_iniciar),"clicked",G_CALLBACK(clique_menu),NULL);
	gtk_main();
	
}
char *infos(int pos)
{
	char *info[] = {"Razao","Endereco","CNPJ"};
	char *retorno;
	char *requisicao;
	requisicao = malloc(strlen("select razao,endereco,cnpj from empresa;"));
	MYSQL_RES *vetor;
	MYSQL_ROW campos;
	requisicao = "select razao,endereco,cnpj from empresa;";
	g_print("\nTestando Campo %i\n",pos);
	vetor = consultar(requisicao);
	campos = mysql_fetch_row(vetor);
	g_print("Buscando %s\n",info[pos]);
	if(campos!=NULL)
	{	
		g_print("%s encontrado\n",info[pos]);
		retorno = malloc(30);
		g_print("%s\n",campos[pos]);
		sprintf(retorno,"%s: %s",info[pos],campos[pos]);
	}
	else
	{
		g_print("%s não encontrado\n",info[pos]);
		//popup(NULL,info[pos]);
		retorno = NULL;
	}	
	return retorno;
}	
