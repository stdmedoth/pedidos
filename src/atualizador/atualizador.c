#include <stdio.h>
#include <stdlib.h>
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

#ifdef __linux__
#define LOGGER             "\\usr\\share\\usr\\share\\petitto\\files\\logger.log"
#define IMAGE_FUNDO        "\\usr\\share\\usr\\share\\petitto\\files\\atualizacao\\img\\fundo_atualizacao.png"
#define ATUALIZA_STYLE     "\\usr\\share\\usr\\share\\petitto\\files\\atualizacao\\estilo.css"
#define TMP_FILES_PATH     "\\usr\\share\\petitto\\files\\atualizacao\\tmp\\atualizacao\\files\\"
#define TMP_BIN_PATH       "\\usr\\share\\usr\\share\\petitto\\files\\atualizacao\\tmp\\atualizacao\\Petitto"
#define FILES_PATH         "\\usr\\share\\petitto\\files\\"
#define BIN_PATH           "\\usr\\share\\petitto\\gtk\\bin"
#define UNZIP_BIN          "unrar"
#define CURL_BIN           "curl"
#define GIT_MASTER         "https:\\\\codeload.github.com\\sistemapetitto\\atualizacao\\zip\\master"
#define PETITTO_FILE       "\\usr\\share\\petitto\\files\\atualizacao\\tmp\\atualizacao.zip"
#define PETITTO_UNZIP_FILE "\\usr\\share\\petitto\\files\\atualizacao\\tmp\\atualizacao"
#define PETITTO_UNZIP_DIR  "\\usr\\share\\petitto\\files\\atualizacao\\tmp\\"
#endif

#ifdef WIN32
#define TMP_FILES_PATH     "C:\\petitto\\files\\atualizacao\\tmp\\atualizacao-master\\files\\"
#define TMP_BIN_PATH       "C:\\petitto\\files\\atualizacao\\tmp\\atualizacao-master\\Petitto.exe"
#define FILES_PATH         "C:\\petitto\\files\\"
#define BIN_PATH           "C:\\petitto\\gtk\\bin"
#define UNZIP_BIN          "C:\\petitto\\files\\atualizacao\\bin\\unzip.exe"
#define CURL_BIN           "C:\\petitto\\files\\atualizacao\\bin\\curl.exe"
#define GIT_MASTER         "https:\\\\codeload.github.com\\sistemapetitto\\atualizacao\\zip\\master"
#define PETITTO_FILE       "C:\\petitto\\files\\atualizacao\\tmp\\atualizacao.zip"
#define PETITTO_UNZIP_FILE "C:\\petitto\\files\\atualizacao\\tmp\\atualizacao-master"
#define PETITTO_UNZIP_DIR  "C:\\petitto\\files\\atualizacao\\tmp\\"
#define ATUALIZA_STYLE     "C:\\petitto\\files\\atualizacao\\estilo.css"
#define LOGGER             "C:\\petitto\\files\\logger.log"
#define IMAGE_FUNDO        "C:\\petitto\\files\\atualizacao\\img\\fundo_atualizacao.png"
#endif

#define REC_ATUALIZA "select * from atualizacoes where visto = 0"

#define USER "petitto"
#define PASS "1234@Petitto"
#define DB "petitto"
#define HOST "db4free.net"
#define MAX_INFO_QNT 100

MYSQL conector;
MYSQL_RES *res;
MYSQL_ROW row;

int autologger(char *string)
{
	FILE *logger;
	char *string2;
	string2 = malloc(100);
	if(strlen(string)>100)
		return 1;
	sprintf(string2,"%s\n",string);
	logger = fopen(LOGGER,"a+");
	if(logger==NULL)
	{
		g_print("Erro no arquivo logger\n");
		return 1;
	}
	fprintf(logger,"%s",string2);
	fclose(logger);
	return 0;
}

int abrir_css(char *path)
{
	//GdkDisplay *display;
	GtkCssProvider *fornecedor;
	GFile *arquivo;
	GError *erro=NULL;
	GdkScreen *screen;
	fornecedor = gtk_css_provider_new();
	arquivo    = g_file_new_for_path(path);
	//display    = gdk_display_get_default();
	//screen     = gdk_display_get_default_screen(display);
	screen = gdk_screen_get_default();
	gtk_style_context_add_provider_for_screen(screen,GTK_STYLE_PROVIDER(fornecedor),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);	
	gtk_css_provider_load_from_file(fornecedor,arquivo,&erro);
	if(erro)
	{
		g_print("erro no css: %i %s\n",erro->code,erro->message);
		return 1;
	}
	//g_object_unref(fornecedor);
	return 0;
}

int close_window_callback(GtkWidget *widget,gpointer *ponteiro)
{	
	gtk_widget_destroy(GTK_WIDGET(ponteiro));
//	gtk_widget_hide_all(GTK_WIDGET(ponteiro));
	return 0;
}
GtkWidget *popup_fechar;
int popup(gchar *string)
{
	int len;
	GtkWidget *popup, *fields, *mensagem, *fixar;

	popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(popup),string);	
	autologger(string);
	fields = gtk_box_new(1,0);
	gtk_window_set_resizable(GTK_WINDOW(popup),FALSE);
	gtk_window_set_position(GTK_WINDOW(popup),3);
	fixar = gtk_fixed_new();
	mensagem = gtk_label_new(string);
	popup_fechar = gtk_button_new_with_label("fechar");
	len = strlen(string);
	if(len<10)
		len=30;
	g_print("%s\n",string);
	autologger(string);
	gtk_widget_set_size_request(fields,8*len,len*3);
	gtk_widget_set_size_request(popup,8*len,len*3);
	gtk_box_pack_start(GTK_BOX(fields),mensagem,0,0,20);
	gtk_box_pack_start(GTK_BOX(fields),popup_fechar,0,0,30);
	gtk_container_add(GTK_CONTAINER(fixar),fields);
	gtk_container_add(GTK_CONTAINER(popup),fixar);
	gtk_widget_grab_focus(popup_fechar);
	gtk_window_set_keep_above(GTK_WINDOW(popup), TRUE);
	g_signal_connect(GTK_WINDOW(popup),"delete-event",G_CALLBACK(gtk_widget_destroy),NULL);
	g_signal_connect(GTK_BUTTON(popup_fechar),"clicked",G_CALLBACK(close_window_callback),popup);	
	gtk_widget_show_all(popup);
	return 0;
}
int efetuar_download()
{
	char *chamada;
	chamada = malloc(strlen(GIT_MASTER)+strlen(CURL_BIN)+strlen(PETITTO_FILE)+20);
	sprintf(chamada,"%s %s --output %s",CURL_BIN,GIT_MASTER,PETITTO_FILE);
	g_print("%s\n",chamada);
	#ifdef WIN32
	STARTUPINFO infoBina={sizeof(infoBina)};
	PROCESS_INFORMATION processInfoBina;
	infoBina.dwFlags = STARTF_USESHOWWINDOW;
	infoBina.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, chamada, NULL, NULL, FALSE, 0, NULL, NULL, &infoBina, &processInfoBina)) 
    {
		WaitForSingleObject(processInfoBina.hProcess, INFINITE);
		CloseHandle(processInfoBina.hProcess);
		CloseHandle(processInfoBina.hThread);
	}
	#endif
	return 0;
}
int efetuar_instalacao()
{
	char *chamada;
	chamada = malloc(strlen(UNZIP_BIN)+strlen(PETITTO_FILE)+strlen(PETITTO_UNZIP_DIR)+20);
	#ifdef WIN32
	sprintf(chamada,"%s -o %s -d %s ",UNZIP_BIN,PETITTO_FILE,PETITTO_UNZIP_DIR);
	g_print("%s\n",chamada);
	STARTUPINFO infoBina={sizeof(infoBina)};
	PROCESS_INFORMATION processInfoBina;
	infoBina.dwFlags = STARTF_USESHOWWINDOW;
	infoBina.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, chamada, NULL, NULL, FALSE, 0, NULL, NULL, &infoBina, &processInfoBina)) 
    {
		WaitForSingleObject(processInfoBina.hProcess, INFINITE);
		CloseHandle(processInfoBina.hProcess);
		CloseHandle(processInfoBina.hThread);
	}
	sprintf(chamada,"xcopy /S /E /Y %s %s",TMP_BIN_PATH,BIN_PATH);
	g_print("%s\n",chamada);
	infoBina.dwFlags = STARTF_USESHOWWINDOW;
	infoBina.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, chamada, NULL, NULL, FALSE, 0, NULL, NULL, &infoBina, &processInfoBina)) 
    {
		WaitForSingleObject(processInfoBina.hProcess, INFINITE);
		CloseHandle(processInfoBina.hProcess);
		CloseHandle(processInfoBina.hThread);
	}
	sprintf(chamada,"xcopy /S /E /Y %s* %s",TMP_FILES_PATH,FILES_PATH);
	g_print("%s\n",chamada);
	infoBina.dwFlags = STARTF_USESHOWWINDOW;
	infoBina.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, chamada, NULL, NULL, FALSE, 0, NULL, NULL, &infoBina, &processInfoBina)) 
    {
		WaitForSingleObject(processInfoBina.hProcess, INFINITE);
		CloseHandle(processInfoBina.hProcess);
		CloseHandle(processInfoBina.hThread);
	}
	#endif
	return 0;
}

int remover_arquivos()
{
	char *chamada;
	chamada = malloc(strlen(TMP_FILES_PATH)+20);
	#ifdef WIN32
	sprintf(chamada,"rd /S /Q %s",TMP_FILES_PATH);
	g_print("%s\n",chamada);
	STARTUPINFO infoBina={sizeof(infoBina)};
	PROCESS_INFORMATION processInfoBina;
	infoBina.dwFlags = STARTF_USESHOWWINDOW;
	infoBina.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, chamada, NULL, NULL, FALSE, 0, NULL, NULL, &infoBina, &processInfoBina)) 
    {
		WaitForSingleObject(processInfoBina.hProcess, INFINITE);
		CloseHandle(processInfoBina.hProcess);
		CloseHandle(processInfoBina.hThread);
	}
	sprintf(chamada,"del %s",TMP_BIN_PATH);
	g_print("%s\n",chamada);
	infoBina.dwFlags = STARTF_USESHOWWINDOW;
	infoBina.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, chamada, NULL, NULL, FALSE, 0, NULL, NULL, &infoBina, &processInfoBina)) 
    {
		WaitForSingleObject(processInfoBina.hProcess, INFINITE);
		CloseHandle(processInfoBina.hProcess);
		CloseHandle(processInfoBina.hThread);
	}
	sprintf(chamada,"del %s",PETITTO_FILE);
	g_print("%s\n",chamada);
	infoBina.dwFlags = STARTF_USESHOWWINDOW;
	infoBina.wShowWindow = SW_HIDE;
	if (CreateProcess(NULL, chamada, NULL, NULL, FALSE, 0, NULL, NULL, &infoBina, &processInfoBina)) 
    {
		WaitForSingleObject(processInfoBina.hProcess, INFINITE);
		CloseHandle(processInfoBina.hProcess);
		CloseHandle(processInfoBina.hThread);
	}	
	#endif
	return 0;
}
int iniciar_processo()
{
	g_print("download\n");
	efetuar_download();
	g_print("instalacao\n");
	efetuar_instalacao();
	g_print("removendo arquivos\n");
	remover_arquivos();
	return 0;
}
int main()
{

	char *query,*qnt_at;
	int erro,pos=0;
	
	GtkWidget *janela,*image_fundo;
	GtkWidget *layout,*caixa_grande;
	
	GtkWidget **info_titulo_label,**info_label,**info_box;
	GtkWidget *infos_scroll,*infos_box,*infos_fixed;
	GtkWidget *atualizacoes_qnt_label;
	
	GtkWidget *iniciar_button,*caixa_opcoes;
	gtk_init(NULL,NULL);
	if(!mysql_init(&conector))
	{
		popup("Erro ao tentar criar conector");
		autologger((char*)mysql_error(&conector));
		return 1;
	}
	g_print("Mysql iniciado\n");
	if(!mysql_real_connect(&conector,HOST,USER,PASS,DB,0,NULL,0))	
	{
		popup("Erro ao tentar conectar");
		autologger((char*)mysql_error(&conector));
		return 1;
	}
	g_print("Mysql conectado\n");
	query = malloc(strlen(REC_ATUALIZA));
	qnt_at = malloc(MAX_INFO_QNT);
	info_titulo_label = malloc(sizeof(GtkLabel)*MAX_INFO_QNT);
	info_label = malloc(sizeof(GtkLabel)*MAX_INFO_QNT);
	info_box = malloc(sizeof(GtkLabel)*MAX_INFO_QNT);
	
	
	sprintf(query,REC_ATUALIZA);
	
	erro = mysql_query(&conector,query);
	if(erro!=0)
	{
		popup("Erro de query");
		return 1;
	}
	g_print("Query enviada\n");
	res = mysql_store_result(&conector);
	if(res==NULL)
	{
		popup("Erro em Mysql_RES");
		return 1;
	}
	
	abrir_css(ATUALIZA_STYLE);
	infos_box = gtk_box_new(1,0);
	caixa_opcoes = gtk_box_new(1,0);
	gtk_widget_set_name(infos_box,"infos_atualizacao");
	gtk_widget_set_size_request(infos_box,300,3000);
	while((row=mysql_fetch_row(res))!=NULL)
	{
	
		info_titulo_label[pos] = gtk_label_new(row[1]);
		gtk_widget_set_name(info_titulo_label[pos],"atualizacao_infos");
		info_label[pos] = gtk_label_new(row[2]);
		gtk_widget_set_name(info_label[pos],"atualizacao_infos");
		
		info_box[pos] = gtk_box_new(1,0);
		gtk_widget_set_name(info_box[pos],"info_box");
		
		gtk_box_pack_start(GTK_BOX(info_box[pos]),info_titulo_label[pos],0,0,0);
		gtk_box_pack_start(GTK_BOX(info_box[pos]),info_label[pos],0,0,0);
		
		gtk_box_pack_start(GTK_BOX(infos_box),info_box[pos],0,0,10);
		pos++;
	}
	infos_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(infos_scroll,300,200);
	infos_fixed = gtk_fixed_new();
	
	
	#ifdef __linux__
	gtk_container_add(GTK_CONTAINER(infos_scroll),infos_box);
	#endif
	
	sprintf(qnt_at,"%i atualizacões",pos);
	atualizacoes_qnt_label = gtk_label_new(qnt_at);
	gtk_widget_set_name(atualizacoes_qnt_label,"atualizacoes_qnt");
	
	iniciar_button = gtk_button_new_with_label("Iniciar Atualização");

	gtk_box_pack_start(GTK_BOX(caixa_opcoes),iniciar_button,0,0,10);

	
	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	image_fundo = gtk_image_new_from_file(IMAGE_FUNDO);
	layout = gtk_layout_new(NULL,NULL);
	caixa_grande = gtk_box_new(1,0);

	gtk_widget_set_size_request(janela,325,340);
	gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
	gtk_window_set_position(GTK_WINDOW(janela),3);
	
	gtk_fixed_put(GTK_FIXED(infos_fixed),infos_scroll,10,20);
	gtk_box_pack_start(GTK_BOX(caixa_grande),infos_fixed,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),atualizacoes_qnt_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(caixa_grande),caixa_opcoes,0,0,5);
	
	gtk_layout_put(GTK_LAYOUT(layout),image_fundo,0,0);
	gtk_layout_put(GTK_LAYOUT(layout),caixa_grande,0,0);
	
	gtk_container_add(GTK_CONTAINER(janela),layout);
	gtk_widget_show_all(janela);
	g_signal_connect(iniciar_button,"clicked",G_CALLBACK(iniciar_processo),NULL);
	g_signal_connect(janela,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_main();
}
