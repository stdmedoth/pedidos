#define QUERY_LEN 1000
#define RANDOM_STRING_SIZE 10

static int imp_opc=0;

static void popup(GtkWidget *widget,gchar *string);

int iniciar_impressao(char *gerado, char *gerando_file)
{
	g_print("Finalizando iniciar_impressao()\n");
	g_print("%s para impressora\n",gerado);

	#ifdef WIN32
	char *chamada;

	chamada = malloc(strlen(gerado)+50);

	g_print("%s para LPT1\n",gerado);
	if(imp_opc==1)
		sprintf(chamada,"xcopy %s LPT1",gerado);
	if(imp_opc==2)
		sprintf(chamada,"xcopy %s LPT2",gerado);

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
	popup(NULL,"Documento enviado para impressão");

	#endif

	#ifdef __linux__
		popup(NULL,gerado);
	#endif
	g_print("Finalizando iniciar_impressao()\n");
	return 0;
}

int desenhar_pdf(char *gerando_file)
{
	char *chamada,*gerado;
	g_print("Iniciando desenhar_pdf()\n");

	chamada = malloc(strlen(PDF_GEN)+strlen(gerando_file)*2+10);
	gerado = malloc(strlen(gerando_file)+1);
	sprintf(gerado,"%s",gerando_file);

	if(strlen(gerado)>5)
		gerado[strlen(gerado)-5] = '\0';



	g_print("de %s para %s.pdf\n",gerando_file,gerado);
	sprintf(chamada,"%s %s %s.pdf",PDF_GEN,gerando_file,gerado);

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
		sprintf(gerado,"%s.pdf",gerado);
		iniciar_impressao(gerado,gerando_file);
	}
	else
	{
		popup(NULL,"Não foi possivel gerar documento");
		return 1;
	}
	#endif
	#ifdef __linux__
	if(system(chamada)!=0)
	{
		popup(NULL,"Não foi possivel gerar documento");
		return 1;
	}
	iniciar_impressao(gerado,gerando_file);
	#endif

	g_print("Finalizando desenhar_pdf()\n");
	return 0;
}

char *randomizar_string()
{
    int i;
    char *res = malloc(RANDOM_STRING_SIZE + 1);
    srand(time( NULL ));
    for(i = 0; i < RANDOM_STRING_SIZE; i++) {
        res[i] = (char) (rand()%(122-97))+97;
    }
    res[i] = '\0';
    return res;
}

int close_window_callback(GtkWidget *widget,gpointer *ponteiro)
{
	gtk_widget_destroy(GTK_WIDGET(ponteiro));
	return 0;
}
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
GtkWidget *popup_fechar;
static void popup(GtkWidget *widget,gchar *string)
{
	int len;
	GtkWidget *popup, *fields, *fixed, *box;
	int resultado;

	popup = gtk_dialog_new_with_buttons("Mensagem",NULL,4,"Ok",GTK_RESPONSE_ACCEPT,NULL);

	gtk_window_set_title(GTK_WINDOW(popup),"Mensagem");
	gtk_window_set_icon_name(GTK_WINDOW(popup),"user-availables");
	gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);

	autologger(string);

	gtk_window_set_position(GTK_WINDOW(popup),3);

	fields = gtk_bin_get_child(GTK_BIN(popup));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),gtk_label_new(string),0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);

	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);

	gtk_widget_grab_focus(gtk_dialog_get_widget_for_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT));
	gtk_dialog_set_default_response(GTK_DIALOG(popup),GTK_RESPONSE_ACCEPT);
	gtk_widget_show_all(popup);

	resultado = gtk_dialog_run(GTK_DIALOG(popup));

	gtk_widget_destroy(popup);
	return ;
}
static MYSQL conectar;
MYSQL_RES *vetor;
static int primeira_conexao=0;

MYSQL_RES *consultar(char *query)
{
	int err=1;
	if(primeira_conexao==0)
	{
		if(!mysql_init(&conectar))
		{
			popup(NULL,"Não foi possivel conectar ao servidor");
			g_print("Erro mysql\n");
			g_print("Erro: %s\n",mysql_error(&conectar));
			autologger("Não foi possivel conectar ao servidor");
			return NULL;
		}
		g_print("%s\n",query);
		if(!mysql_real_connect(&conectar,SERVER,USER,PASS,DATABASE,0,NULL,0))
		{
			g_print("Erro mysql : %s\n",mysql_error(&conectar));
			autologger((char*)mysql_error(&conectar));
			return NULL;
		}
		if (!mysql_set_character_set(&conectar, "utf8"))
		{
			g_print("Novo caracter setado: %s\n",
			mysql_character_set_name(&conectar));
		}
		primeira_conexao=1;
	}

	g_print("%s\n",query);
	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		autologger(query);
		autologger((char*)mysql_error(&conectar));
		g_print("Erro mysql : %s\n",mysql_error(&conectar));
		popup(NULL,"Erro de formato\n");
		primeira_conexao=0;
		return NULL;
	}
	vetor = mysql_store_result(&conectar);
	if(vetor==NULL)
	{
		autologger((char*)mysql_error(&conectar));
		g_print("%s\n",mysql_error(&conectar));
		popup(NULL,"Erro de formato\n");
		primeira_conexao=0;
		return NULL;
	}
	//mysql_close(&conectar);
	return vetor;
}
int enviar_query(char *query)
{
	int err=1;
	if(primeira_conexao==0)
	{
		if(!mysql_init(&conectar))
		{
			g_print("Erro mysql : %s\n",mysql_error(&conectar));
			popup(NULL,"Não foi possivel conectar ao servidor");
			autologger("Não foi possivel conectar ao servidor");
			primeira_conexao=0;
			return 1;
		}
		g_print("%s\n",query);
		if(!mysql_real_connect(&conectar,SERVER,USER,PASS,DATABASE,0,NULL,0))
		{

			popup(NULL,"Não foi possivel conectar ao servidor");
			g_print("Erro mysql : %s\n",mysql_error(&conectar));
			autologger("Não foi possivel conectar ao servidor");
			primeira_conexao=0;
			return 1;
		}
		if (!mysql_set_character_set(&conectar, "utf8"))
		{
			g_print("Novo caracter setado: %s\n",
			mysql_character_set_name(&conectar));
		}
	}
	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		g_print("%s\n",query);
		autologger(query);
		autologger((char*)mysql_error(&conectar));
		g_print("Erro mysql %s\n",mysql_error(&conectar));
		popup(NULL,"Erro de formato\n");
		return 1;
	}
	return 0;
}
int tasker(char *table)
{
	char task[8];
	MYSQL connect;

	MYSQL_RES *result_vetor;
	MYSQL_ROW campos;

	int err=0,task_num=0;
	char query[QUERY_LEN];

	printf("Iniciando Tasker()\n");
	sprintf(query,"select MAX(code) from %s;",table);
	result_vetor = consultar(query);

	if(result_vetor == NULL)
	{
		popup(NULL,"Não foi possivel receber o id do servidor");
		return 1;
	}

	campos = mysql_fetch_row(result_vetor);
	if(campos==NULL)
	{
		return 1;
	}

	#ifdef __linux__
	sprintf(task,"%s",campos[0]);
	task_num = stoi(task);
	#endif
	#ifdef WIN32
	task_num = stoi(campos[0]);
	#endif

	if(task_num==-1)
	{
		return 1;
	}
	g_print("Query_code recebida com sucesso\n");
	g_print("Tasker Finalizado\n");
	return (task_num+1);
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

	if(vetor==NULL)
	{
		popup(NULL,"Erro ao receber dados da empresa");
		return "";
	}
	g_print("Buscando %s\n",info[pos]);
	if((campos = mysql_fetch_row(vetor))==NULL)
	{
		g_print("%s não encontrado\n",info[pos]);
		//popup(NULL,info[pos]);
		return "";
	}

	g_print("%s encontrado\n",info[pos]);
	retorno = malloc(62);
	g_print("%s\n",campos[pos]);

	if(strlen(campos[pos])>=60)
	{
		campos[pos][60] = '.';
		campos[pos][61] = '\0';
	}

	sprintf(retorno,"%s",campos[pos]);

	return retorno;
}
