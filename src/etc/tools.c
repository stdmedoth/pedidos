#define QUERY_LEN 1000

int close_window_callback(GtkWidget *widget,gpointer *ponteiro)
{	
	gtk_widget_destroy(GTK_WIDGET(ponteiro));
//	gtk_widget_hide_all(GTK_WIDGET(ponteiro));
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
int popup(GtkWidget *widget,gchar *string)
{
	int len;
	GtkWidget *popup, *fields, *fixed, *box; 
	int resultado;

	popup = gtk_dialog_new_with_buttons("Mensagem",NULL,4,"Ok",GTK_RESPONSE_ACCEPT,NULL);
	
	gtk_window_set_title(GTK_WINDOW(popup),"Mensagem");	
	gtk_window_set_keep_above(GTK_WINDOW(popup),TRUE);	

	autologger(string);

	gtk_window_set_position(GTK_WINDOW(popup),3);
	
	fields = gtk_bin_get_child(GTK_BIN(popup));
	fixed = gtk_fixed_new();
	box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box),gtk_label_new(string),0,0,10);
	gtk_fixed_put(GTK_FIXED(fixed),box,30,0);
	
	gtk_box_pack_end(GTK_BOX(fields),fixed,0,0,30);
	
	gtk_widget_show_all(popup);

	resultado = gtk_dialog_run(GTK_DIALOG(popup));

	gtk_widget_destroy(popup);

	return 0;
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
	if(!mysql_init(&connect))
		return 1;
	MYSQL_RES *result_vetor;
	MYSQL_ROW campos;
	int err=0,task_num=0;
	char query[QUERY_LEN];
	printf("Iniciando Tasker()\n");
	sprintf(query,"select MAX(code) from %s;",table);
	mysql_real_connect(&connect,SERVER,USER,PASS,DATABASE,0,NULL,0);
	err = mysql_query(&connect,query);
	if(err!=0)
	{
		g_print("Query para tabela %s\n",table);
		g_print("codigo do erro %i\n",err);
		g_print("Mensagem_query: %s",mysql_error(&connect));
		popup(NULL,(gchar *)mysql_error(&connect));
		return 1;
	}
	else
	{
		g_print("Query para tabela %s\n",table);
		g_print("Query_code envida com sucesso\n");
	}
	result_vetor = mysql_store_result(&connect);
	if(mysql_errno(&connect)!=0)
	{
		g_print("%s\n",mysql_error(&connect));
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
	campos = mysql_fetch_row(vetor);
	g_print("Buscando %s\n",info[pos]);
	if(campos!=NULL)
	{	
		g_print("%s encontrado\n",info[pos]);
		retorno = malloc(200);
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
