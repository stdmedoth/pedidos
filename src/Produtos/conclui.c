int conclui_prod(GtkWidget* nome, gpointer *botao)
{
	
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW campos;
	char *code;
	code = malloc(10);
	char *query;
	int cont;
	for(cont=0;cont<=CAMPOS_QNT;cont++)
	{
		if(vet_erro[cont]!=0)
		{
			popup(NULL,"Você tem campos incorretos\n\t\tRepasse com tecla ENTER");
			g_print("Tentou concluir cadastro com campos incorretos: campo %i\n",cont);
			autologger("Tentou concluir cadastro com campos incorretos");
			return 1;
		}
	}
	g_print("alocando memoria para query %i\n",(int)(QUERY_LEN+INSERT_QUERY));
	query = malloc((int)(QUERY_LEN+INSERT_QUERY));
	if(query==NULL)
	{
			popup(NULL,"Erro de memoria");
			autologger("Erro de memoria");
			return 1;
	}
	g_print("iniciando concluir_ter()\n");
	
	if(alterando==0)
	{
		sprintf(query,PROD_CAD_QUERY,ARGS_PROD_CAD_QUERY);
	}
	else
	{
		sprintf(query,PROD_UPD_QUERY,ARGS_PROD_CAD_QUERY);
	}
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
		autologger("[!] Erro ao tentar se conectar\n");
		autologger((char*)mysql_error(&connect));
		return 1;
	}	
	if(stoi(codigos_prod)==-1)
	{
		if(strlen(codigos_prod)>8)
		{
			autologger("Codigo produto chegou ao limite\n");
			popup(NULL,"O código do produto deve ser menor\n");
			return -1;
		}
	}
	g_print("%s\n",query);
	autologger(query);
	err = mysql_query(&connect,query);
	if(err!=0)
	{
		g_print("Query para tabela produtos\n");
		autologger("Query para tabela produtos");
		g_print("codigo do erro %i\n",err);
		g_print("%s\n",mysql_error(&connect));
		g_print("%s\n\n",query);
		autologger(query);
		gtk_button_set_label(GTK_BUTTON(botao),"Tente Novamente");
		popup(NULL,(gchar*)mysql_error(&connect));
		return 1;
	}
	else
	{
		autologger(query);
		g_print("Query para tabela produtos\n");
		g_print("Query envida com sucesso\n");
		sprintf(query,"select code from produtos where code = %s",codigos_prod);
		resultado = consultar(query);
		if(resultado==NULL)
		{	
			popup(NULL,"Erro na confirmação do envio");
			return 1;
		}
		campos = mysql_fetch_row(resultado);
		if(campos!=NULL)
		{
			autologger(query);
			g_print("Query envida com sucesso\n");
			gtk_button_set_label(GTK_BUTTON(botao),"concluido");
			popup(NULL,"Concluido");
			gtk_label_set_text(GTK_LABEL(acao_atual2),"Cadastrando");
			alterar=0;
			code[0] = '\0';
			sprintf(code,"%i",tasker("produtos"));
			gtk_entry_set_text(GTK_ENTRY(codigo_prod_field),code);
			gtk_entry_set_text(GTK_ENTRY(nome_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(preco_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(peso_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(unidade_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(fornecedor_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(grupo_prod_field),"");
			gtk_entry_set_text(GTK_ENTRY(marca_prod_field),"");
			buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacao_prod_field));
			gtk_text_buffer_get_start_iter (buffer,&inicio);
			gtk_text_buffer_get_end_iter (buffer,&fim);
			gtk_text_buffer_delete (buffer,&inicio,&fim);	
			gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),FALSE);		
		}
		else
		{
			popup(NULL,"O cadastro nao foi feito\nverifique os campos");
			autologger("O cadastro nao foi feito\nverifique os campos");
		}
	}
	
	printf("finalizando conclui_ter()\n");
	autologger("O cadastro nao foi feito\nverifique os campos");
//	gtk_widget_grab_focus (GTK_WIDGET(name_ter_field));
	return 0;
}
