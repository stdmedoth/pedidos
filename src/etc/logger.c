int file_logger(const char *string){
	FILE *logger;
  	char *string1;
	if(!string)
		return 1;

	logger = fopen(LOGGER,"a+");
	if(logger){
	    GDateTime *data = g_date_time_new_now(g_time_zone_new(NULL));
	    if(!data){
	      file_logger("app_tracelog() -> datetime nulo, não foi possível carregar data");
	    }
	    string1 = malloc( strlen(string) + strlen( g_date_time_format(data,"%F %T") ) + 20 );
	    sprintf(string1,"%s - %s", g_date_time_format(data,"%F %T"), string);
	    fprintf(logger, "%s\n", string1);
	}else{
		popup(NULL,"Não foi possivel atualizar logs, verifique com suporte");
		encerrando();
	    exit(1);
	}
	fclose(logger);
	return 0;
}


int autologger(const char *string)
{
	GDateTime *data = g_date_time_new_now(g_time_zone_new(NULL));
	logging = 1;
	char string1[MAX_QUERY_LEN + strlen(string) + strlen(g_date_time_format(data,"%F %T"))];
	//char string2[MAX_QUERY_LEN+strlen(string)*2];
	//char *unvulned_query[MAX_QUERY_LEN+strlen(string)*2];

	sprintf(string1,"%s - %s",g_date_time_format(data,"%F %T"), string);

  //ainda um pouco pesado, vou melhorar...

/*
	for(int cont=0;cont<strlen(string1);cont++){
		if(string1[cont] == '\n')
			string1[cont] = ' ';
		if(string1[cont] == '\0' || string1[cont] == -1)
			break;
	}

	if(primeira_conexao!=0)
		mysql_real_escape_string(&conectar,unvulned_query,string1,strlen(string1));

	sprintf(string2,"insert into logs(descricao,data) values('%s',CURRENT_TIMESTAMP());",unvulned_query);

	if(strlen(string2)>MAX_LOG_DESC)
		string2[MAX_LOG_DESC] = '\0';

	if(enviar_query(string2)!=0)
		g_print("Log não pode ser enviado\n%s\n",string2);
*/
	file_logger(string1);
 	//file_logger(string2);

	logging = 0;
	return 0;
}
