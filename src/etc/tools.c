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
	GtkWidget *popup, *fields, *mensagem, *fixar;
	popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_keep_above(GTK_WINDOW(popup), TRUE);
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
	gtk_widget_set_size_request(fields,8*len,len*3);
	gtk_widget_set_size_request(popup,8*len,len*3);
	gtk_box_pack_start(GTK_BOX(fields),mensagem,0,0,20);
	gtk_box_pack_start(GTK_BOX(fields),popup_fechar,0,0,30);
	gtk_container_add(GTK_CONTAINER(fixar),fields);
	gtk_container_add(GTK_CONTAINER(popup),fixar);
	gtk_widget_grab_focus(popup_fechar);
	g_signal_connect(GTK_WINDOW(popup),"delete-event",G_CALLBACK(gtk_widget_destroy),NULL);
	g_signal_connect(GTK_BUTTON(popup_fechar),"clicked",G_CALLBACK(close_window_callback),popup);
	
	gtk_widget_show_all(popup);
	return 0;
}
static MYSQL conectar;
MYSQL_RES *vetor;
MYSQL_RES *consultar(char *query)
{
	int err=1;
	if(!mysql_init(&conectar))
	{
		popup(NULL,"Não foi possivel conectar ao servidor");	
		autologger("Não foi possivel conectar ao servidor");
		return NULL;
	}
	if(!mysql_real_connect(&conectar,SERVER,USER,PASS,DATABASE,0,NULL,0));
	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		autologger(query);
		autologger((char*)mysql_error(&conectar));
		g_print("%s\n",mysql_error(&conectar));
		popup(NULL,"Erro de formato\n");
		return NULL;
	}
	vetor = mysql_store_result(&conectar);
	if(vetor==NULL)
	{
		autologger((char*)mysql_error(&conectar));
		g_print("%s\n",mysql_error(&conectar));
		popup(NULL,"Erro de formato\n");
		return NULL;	
	}
	return vetor;
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
	char query[100];
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
