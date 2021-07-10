int mysql_res_to_cvs_file(char *filename, MYSQL_RES *res){
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	FILE *fp = fopen(filename, "w");
	if(!fp){
		popup(NULL,"Não foi possível abrir arquivo");
		file_logger("Erro no arquivo:");
		file_logger(filename);
		return 1;
	}

	
	int rows_qnt = mysql_num_rows(res);
	int fields_qnt = mysql_num_fields(res);
	int types[fields_qnt];
	int field_pos=0;
	while((field = mysql_fetch_field(res))){
		fprintf(fp,"%s;", field->name);
		types[field_pos] = field->type;
		field_pos++;
	}
	fprintf(fp,"\n");
	char *oldLocale = setlocale(LC_NUMERIC, NULL);
	setlocale(LC_NUMERIC, "pt_BR");
	while((row = mysql_fetch_row(res))){
		for (int i = 0; i < fields_qnt; ++i){
			if(!row[i]){
				fprintf(fp,";");	
			}else{
				char value[strlen(row[i]) + 12];
				switch(types[i]){
					case MYSQL_TYPE_DECIMAL:
					case MYSQL_TYPE_FLOAT: 
						sprintf(value, "%.2f", atof(row[i])); 		
						break;
					default:
						sprintf(value, "%s", row[i]); 		
					break;
				}
				fprintf(fp,"%s;", row[i]);	
			}
			
		}
		fprintf(fp,"\n");
	}
	setlocale(LC_NUMERIC, oldLocale);
	fclose(fp);
	return 0;
}

int row_exists(char *table, int id){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	sprintf(query, "select * from %s where code = %i", table ,id);

	if(!(res = consultar(query))){
		return 0;
	}
	if(mysql_num_rows(res)){
		return 1;
	}
	return 0;
}

int conectar_mysql(){
	global_progress_bar_active = 1;

	carregar_interface();

	if(!mysql_init(&conectar)){
		global_progress_bar_active = 0;
		popup(NULL,"Não foi possivel iniciar conector");
		autologger((char*)mysql_error(&conectar));
		encerrando();
		return 1;
	}
	unsigned int timeout = 60 * 60 * 24;
	int reconnect = 1;
	mysql_options(&conectar, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);
	mysql_options(&conectar, MYSQL_OPT_RECONNECT, &reconnect);

	carregar_interface();
	if(!mysql_real_connect(&conectar, server_confs.server_endereco, server_confs.server_user, server_confs.server_senha, server_confs.server_database, 0,NULL,0)){
		global_progress_bar_active = 0;
		popup(NULL,"Não foi possível conectar ao servidor");
		encerrando();
		return 1;
	}

	gchar *character = strdup("utf8");
	gchar *msg = malloc(strlen(character) + 200);
	sprintf(msg, "setando caracete %s", character);
	autologger( msg );
	if (mysql_set_character_set(&conectar, character)){
		autologger("Não foi possivel setar novo caracter");
	}

	global_progress_bar_active = 0;
	primeira_conexao=1;
	return 0;
}

MYSQL_RES *consultar(char *query){
	MYSQL_RES *vetor;

	int err=1;
	FILE *backup_query;
	backup_query = fopen(BACKUP_QUERY_FILE,"+a");

	if(!primeira_conexao){
		if(conectar_mysql())
			return NULL;
	}

	#ifdef QUERY_DEBUG
	g_print("%s\n",query);
	#endif
	if((err = mysql_query(&conectar,query))){
		file_logger((char*)mysql_error(&conectar));
		file_logger(query);
		autologger((char*)mysql_error(&conectar));
		autologger(query);
		popup(NULL,"Erro de formato\n");
		primeira_conexao=0;
		return NULL;
	}

	if(!(vetor = mysql_store_result(&conectar))){
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
	if(!primeira_conexao){
		if(conectar_mysql())
			return 1;
	}

	#ifdef QUERY_DEBUG
	g_print("%s\n",query);
	#endif

	carregar_interface();

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
