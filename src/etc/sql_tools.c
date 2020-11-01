
MYSQL_RES *consultar(char *query){
	MYSQL_RES *vetor;

	int err=1;
	FILE *backup_query;
	backup_query = fopen(BACKUP_QUERY_FILE,"+a");

	if(primeira_conexao==0)
	{
		GtkWidget *loading_wnd = carregando_wnd();
		while (g_main_context_pending(NULL))
			g_main_context_iteration(NULL,FALSE);
		if(!mysql_init(&conectar))
		{
			popup(NULL,"Não foi possivel iniciar conector");
			autologger((char*)mysql_error(&conectar));
			gtk_widget_destroy(loading_wnd);
			return NULL;
		}

		if(!mysql_real_connect(&conectar,server_confs.server_endereco,server_confs.server_user,server_confs.server_senha,server_confs.server_database,0,NULL,0))
		{
      popup(NULL,"Não foi possível conectar ao servidor");
			gtk_widget_destroy(loading_wnd);
			return NULL;
		}

		if (mysql_set_character_set(&conectar, "utf8"))
		{
			autologger("Erro ao setar caracter");
		}
		gtk_widget_destroy(loading_wnd);
		primeira_conexao=1;
	}

	#ifdef QUERY_DEBUG
	g_print("%s\n",query);
	#endif
	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		file_logger((char*)mysql_error(&conectar));
		file_logger(query);
		autologger((char*)mysql_error(&conectar));
		autologger(query);
		popup(NULL,"Erro de formato\n");
		primeira_conexao=0;
		return NULL;
	}

	vetor = mysql_store_result(&conectar);
	if(vetor==NULL)
	{
		file_logger((char*)mysql_error(&conectar));
		file_logger(query);
		autologger((char*)mysql_error(&conectar));
		autologger(query);
		popup(NULL,"Erro de formato\n");
		primeira_conexao=0;
		return NULL;
	}

	if(backup_query){
		fprintf(backup_query,"%s\n",query);
		fclose(backup_query);
	}
	return vetor;
}

int enviar_query(char *query){
	FILE *backup_query;
	backup_query = fopen(BACKUP_QUERY_FILE,"a+");

	int err=1;
	if(primeira_conexao==0)
	{
		GtkWidget *loading_wnd = carregando_wnd();
		if(!mysql_init(&conectar))
		{
			popup(NULL,"Não foi possivel conectar ao servidor");
			if(logging == 0){
				autologger("Não foi possivel conectar ao servidor");
				autologger((char*)mysql_error(&conectar));
			}
			primeira_conexao=0;
			gtk_widget_destroy(loading_wnd);
			return 1;
		}
		if(!mysql_real_connect(&conectar,server_confs.server_endereco,server_confs.server_user,server_confs.server_senha,server_confs.server_database,0,NULL,0))
		{
			popup(NULL,"Não foi possivel conectar ao servidor");
      file_logger((char*)mysql_error(&conectar));
			if(logging == 0){
				autologger("Não foi possivel conectar ao servidor");
				autologger((char*)mysql_error(&conectar));
			}
			primeira_conexao=0;
			gtk_widget_destroy(loading_wnd);
			return 1;
		}

		if (mysql_set_character_set(&conectar, "utf8"))
		{
			autologger("Não foi possivel setar novo caracter");
		}
		gtk_widget_destroy(loading_wnd);
		primeira_conexao=1;
	}

	#ifdef QUERY_DEBUG
	g_print("%s\n",query);
	#endif

	err = mysql_query(&conectar,query);
	if(err!=0)
	{
    //popup(NULL,(char*)mysql_error(&conectar));
    file_logger((char*)mysql_error(&conectar));
		popup(NULL,"Erro de formato\n");
		if(logging == 0){
      autologger(query);
			autologger((char*)mysql_error(&conectar));
		}
		return err;
	}

	if(backup_query){
		fprintf(backup_query,"%s\n",query);
		fclose(backup_query);
	}

	return 0;
}
