int install_get_db_tables(){

  	FILE *fp = fopen(DB_TABLES_LIST_FILE, "r");
  	if(!fp){
  		char url[strlen(PEDIDOS_APP_URL_FILES) + 200];
  		sprintf(url, "%s/data/db_tables_list", PEDIDOS_APP_URL_FILES);
  		if(download_from_to(url, DB_TABLES_LIST_FILE)){
  			popup(NULL,"Não foi possível efetuar download da verificação de tabelas");
  			return 1;
  		}
  		if(!(fp = fopen(DB_TABLES_LIST_FILE, "r"))){
  			popup(NULL,"Ainda não foi possível abrir arquivo de verificação das tabelas");
  			return 1;
  		}
  	}

  	int pos_line = 0;
  	size_t line_buf_size = 0;
  	pedidos_db_tables = malloc(MAX_TABLE_LEN * MAX_TABLE_QNT);
  	pedidos_db_tables[pos_line] = malloc(MAX_TABLE_LEN);

  	while((getline(&pedidos_db_tables[pos_line], &line_buf_size, fp))>0){
      
      if(!strcmp(pedidos_db_tables[pos_line], "\n")){
        continue;
      }
      remover_barra_n(pedidos_db_tables[pos_line]);

  		pos_line++;
  		pedidos_db_tables[pos_line] = malloc(MAX_TABLE_LEN);
  		pedidos_db_tables_qnt++;
  	}

  	return 0;
}

int check_installed_pedidos_db(){
  FILE *installed_flag_fp = fopen(INSTALL_FLAG_FILE, "r");
  if(installed_flag_fp){
    return 1;
  }
  return 0;
}

int install_pedidos_db_tables(){
  for(int cont=0; cont<pedidos_db_tables_qnt; cont++){

    int path_len = strlen(SCHEMAS_DIR) + strlen(pedidos_db_tables[cont] + 6);
    char script_path[path_len];

    char msg[50 + strlen(pedidos_db_tables[cont])];
    sprintf(msg, "Instalando tabela %s", pedidos_db_tables[cont]);
    global_progress_bar_text = strdup(msg);


    sprintf(script_path, "%s/%s.sql", SCHEMAS_DIR, pedidos_db_tables[cont]);
    FILE *fp = fopen(script_path, "r");
    if(!fp){
      global_progress_bar_active = 0;
      sprintf(msg, "Não foi possível abrir schema para tabela %s", pedidos_db_tables[cont]);
      file_logger(script_path);
      file_logger(strerror(errno));
      popup(NULL,msg);
      return 1;
    }
    fclose(fp);
    if(run_sql_from_file(script_path, 0)){
      sprintf(msg, "Erro durante instalação da tabela %s", pedidos_db_tables[cont]);
      popup(NULL,msg);
      return 1;
    }
  }
  return 0;
}

int install_pedidos_db_data(){

  char msg[50];
  sprintf(msg, "Instalando dados básicos ...");
  global_progress_bar_text = strdup(msg);

  if(run_sql_from_file(SQL_DATA_SCRIPT, 0)){
    sprintf(msg, "Erro durante instalação dos dados básicos");
    popup(NULL,msg);
    return 1;
  }
  return 0;
}

int install_pedidos_db(){

  if(install_get_db_tables()){
    return 1;
  }

  if(!pedidos_db_tables){
    return 1;
  }

  global_progress_bar_active = 1;

  if(install_pedidos_db_tables()){
    global_progress_bar_active = 0;
    return 1;
  }
  if(install_pedidos_db_data()){
    global_progress_bar_active = 0;
    return 1;
  }

  global_progress_bar_active = 0;

  FILE *installed_flag_fp = fopen(INSTALL_FLAG_FILE, "w");
  if(!installed_flag_fp){
    global_progress_bar_active = 0;
    char msg[60 + strlen(strerror(errno)) ];
    sprintf(msg, "Não foi possível finalizar instalação (flag final) erro: %s", strerror(errno));
    popup(NULL,msg);
    return 1;
  }
  fprintf(installed_flag_fp, "%s", data_sys);
  fclose(installed_flag_fp);

  return 0;
}
