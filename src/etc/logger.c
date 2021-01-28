int init_logger(){
  g_timeout_add(2000, app_tracelog, NULL);
  file_logger("-------------------------------Iniciando Logger--------------------------\n");
  return 0;
}

int app_tracelog(){
  FILE *tracelog_file = fopen(APP_TRACELOG, "a+");
  GDateTime *data = g_date_time_new_now(g_time_zone_new(NULL));
  if(!data){
    file_logger("app_tracelog() -> datetime nulo, não foi possível carregar data");
  }
  if(!tracelog_file){
    popup(NULL,"Não foi possível abrir o arquivo de tracelog");
    encerrando();
    exit(1);
  }

  if(tracelog_function_name)
    fprintf(tracelog_file, "%s - Função: %s()\n",g_date_time_format(data,"%F %T"), (char*) NOT_NULL(tracelog_function_name));

  if(tracelog_wnd_name){
    fprintf(tracelog_file, "%s - Janela: %s\n",g_date_time_format(data,"%F %T"), (char*)NOT_NULL(tracelog_wnd_name));
  }

  fclose(tracelog_file);
  return G_SOURCE_CONTINUE ;
}

void tracelogger_set_func_name(gchar *func_name){
  if(func_name)
    tracelog_function_name = strdup(func_name);
}

void tracelogger_set_widget_name(gchar *widget_name){
  if(widget_name)
    tracelog_widget_name = strdup(widget_name);
}

void tracelogger_set_obj_name(gchar *obj_name){
  if(obj_name)
    tracelog_obj_name = strdup(obj_name);
}

void tracelogger_set_wnd_name(gchar *wnd_name){
  if(wnd_name)
    tracelog_wnd_name = strdup(wnd_name);
}

int file_logger(char *string){
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


int autologger(char *string)
{
	char *string1, *string2,*unvulned_query;
  GDateTime *data = g_date_time_new_now(g_time_zone_new(NULL));
	logging = 1;
	string1 = malloc(MAX_QUERY_LEN+strlen(string) + strlen(g_date_time_format(data,"%F %T")));
	//string2 = malloc(MAX_QUERY_LEN+strlen(string));

	sprintf(string1,"%s - %s",g_date_time_format(data,"%F %T"), string);

  //ainda um pouco pesado, vou melhorar...

/*
	for(int cont=0;cont<strlen(string1);cont++){
		if(string1[cont] == '\n')
			string1[cont] = ' ';
		if(string1[cont] == '\0' || string1[cont] == -1)
			break;
	}
	unvulned_query = malloc(strlen(string1)*2);

	if(primeira_conexao!=0)
		mysql_real_escape_string(&conectar,unvulned_query,string1,strlen(string1));

	sprintf(string2,"insert into logs(descricao,data) values('%s',CURRENT_TIMESTAMP());",unvulned_query);

	if(strlen(string2)>MAX_LOG_DESC)
		string2[MAX_LOG_DESC] = '\0';

	if(enviar_query(string2)!=0)
		g_print("Log não pode ser enviado\n%s\n",string2);
*/
  file_logger(string1);
  //	file_logger(string2);
  free(string1);
  //free(string2);

	logging = 0;
	return 0;
}
