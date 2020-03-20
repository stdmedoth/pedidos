int conclui_ter(GtkWidget* nome, gpointer *botao)
{
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW campos;
	char query[110],code[30];
	g_print("iniciando concluir_ter()\n");
	
	if(strlen(codigos_ter)<1||strlen(nomes_ter)<1||strlen(endereco_ter)<1||strlen(tipo_ter)<1)
	{
	//	code[0] = '\0';
	//	sprintf(code,"%i",tasker("terceiros"));
	//	gtk_entry_set_text(GTK_ENTRY(code_ter_field),code);
	//	gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
	//	gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
	//	gtk_entry_set_text(GTK_ENTRY(type_ter_field),"");
		popup(NULL,"Voce deve preencher todos os campos");	
		gtk_widget_grab_focus(code_ter_field);
		return 1;
	}
	sprintf(query,"insert into terceiros(code,name,address,type) values('%s','%s','%s','%s');",codigos_ter,nomes_ter,endereco_ter,tipo_ter);
	g_print("[...] Criando conexão com o banco\n\n");
	MYSQL connect;
	mysql_init(&connect);
	g_print("[...] Tentando conexão com o banco\n\n");
	if(mysql_real_connect(&connect,"localhost",USER,PASS,"erp",0,NULL,0))
	{
		g_print("[!] conectado ao banco com sucesso\n\n");
	}
	else
	{
		popup(NULL,"Algum erro no servidor\nLigue para suporte");
		g_print("[!] Erro ao tentar se conectar %s\n",mysql_error(&connect));
		return 1;
	}	
	if(stoi(codigos_ter)==-1)
	{
		if(strlen(codigos_ter)>8)
		{
			g_print("Codigo terceiro muito grande %s\n",codigos_ter);
			popup(NULL,"O código do terceiro deve ser menor\n");
			return -1;
		}
		else
		{
			g_print("Codigo do terceiro incorreto %s\n",codigos_ter);
			popup(NULL,"Codigo terceiro deve ser numérico\nPor favor corrija");
			gtk_widget_grab_focus(GTK_WIDGET(code_ter_field));
			return 1;
		}
	}
	err = mysql_query(&connect,query);
	if(err!=0)
	{
		g_print("Query para tabela terceiros\n");
		g_print("codigo do erro %i\n",err);
		g_print("%s\n\n",mysql_error(&connect));
		gtk_button_set_label(GTK_BUTTON(botao),"erro");
		popup(NULL,(gchar*)mysql_error(&connect));
		return 1;
	}
	else
	{
		autologger(query);
		g_print("Query para tabela terceiros\n");
		g_print("Query envida com sucesso\n");
		sprintf(query,"select code from terceiros where code = '%s'",codigos_ter);
		resultado = consultar(query);
		campos = mysql_fetch_row(resultado);
		if(campos!=NULL)
		{
			autologger(query);
			g_print("Query envida com sucesso\n");
			gtk_button_set_label(GTK_BUTTON(botao),"concluido");
			popup(NULL,"Concluido");
			code[0] = '\0';
			sprintf(code,"%i",tasker("terceiros"));
			gtk_entry_set_text(GTK_ENTRY(code_ter_field),code);
			gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
			gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
		//	gtk_entry_set_text(GTK_ENTRY(type_ter_field),"");
			gtk_widget_grab_focus (GTK_WIDGET(name_ter_field));
		//	gtk_widget_destroy(janela);
			memset(nomes_ter,0x0,strlen(nomes_ter));
		//	memset(codigos_ter,0x0,strlen(codigos_ter));
		//	memset(endereco_ter,0x0,strlen(endereco_ter));
		//	memset(tipo_ter,0x0,strlen(tipo_ter));
		}
		else
		{
			popup(NULL,"O cadastro nao foi feito\nverifique os campos");
		}
		return 0;
	}
	if(tipo_ter!=NULL)
	{
		tipo_ter = NULL;
	}
	return 0;
	printf("finalizando conclui_ter()\n");
}
