int error_migrate_popup(){
  char *ask = "Houve um erro em um dos comandos migrate, deseja continuar?";
  char msg[ strlen(ask) +  3 + strlen(mysql_error(&conectar)) ];
  sprintf(msg, "%s\n\n%s", ask, mysql_error(&conectar));
  if(!PopupBinario(msg, "Sim, continue o processo", "Deixar para depois")){
    file_logger("erro no migrate");
    file_logger(mysql_error(&conectar));
    return 1;
  }
  return 0;
}

int get_migrate_loaded(){
  MYSQL_RES *res;
	MYSQL_ROW row;

	char query[50];
	sprintf(query, "SELECT * FROM migrate;");
	if(!(res = consultar(query))){
		popup(NULL,"Não foi receber migrates");
		return 1;
	}
  migrates_loaded_qnt = mysql_num_rows(res);
	if(!migrates_loaded_qnt){
		printf("Não há migrates carregados no server\n");
		return 0;
	}

  int cont = 0;
  migrates_loaded = malloc( sizeof(struct _migrate) *migrates_loaded_qnt );
  while( (row = mysql_fetch_row(res)) ){
    migrates_loaded[cont].code = atoi(row[MIGRATE_CODE]);
    migrates_loaded[cont].descricao = strdup(row[MIGRATE_DESCRICAO]);
    migrates_loaded[cont].arquivo = strdup(row[MIGRATE_ARQUIVO]);
    migrates_loaded[cont].versao = strdup(row[MIGRATE_VERSAO]);
    migrates_loaded[cont].lancamento = strdup(row[MIGRATE_LANCAMENTO]);
    cont++;
  }

  return 0;
}

int migrate_is_loaded(const char *filename){
  for(int cont=0; cont < migrates_loaded_qnt; cont++){
    if( !strcmp(migrates_loaded[cont].arquivo, filename) ){
      return 1;
    }
  }
  return 0;
}


int update_migrates(){
  int atual_version_pos = 0, versions_qnt = 0;

  if(get_migrate_loaded()){
    return 1;
  }

  for(int cont=0; version_migrates_list[cont][VER_MIGRATES_VERSION]; cont++){
    if( !strcmp( GET_APP_VERSION_NAME(), version_migrates_list[cont][VER_MIGRATES_VERSION] ) ){
        atual_version_pos = cont;
    }
    versions_qnt++;
  }

  int migrates_not_loaded_qnt = 0;
  char **migrates_not_loaded = malloc(sizeof(char*) *versions_qnt);
  int migrates_not_loaded_pos = 0;
  for(int cont=0; version_migrates_list[cont][VER_MIGRATES_VERSION] ; cont++){
    if(migrate_is_loaded(version_migrates_list[cont][UP_MIGRATE_FILE])){
      continue;
    }
    migrates_not_loaded[migrates_not_loaded_qnt] = strdup(version_migrates_list[cont][UP_MIGRATE_FILE]);
    migrates_not_loaded_qnt++;
  }


  if(!migrates_not_loaded_qnt){
    if(janelas_gerenciadas.aplicacao.criada){
      popup(NULL,"Não há migrates para atualizar");
      return 1;
    }else{
      printf("Nenhum migrate a realizar\n");
      return 0;
    }
  }


  char msg[350];
  sprintf(msg, "Existem %i migrates à executar, deseja atualizar já?", migrates_not_loaded_qnt);
  if(PopupBinario(msg, "Sim, continuar o processo", "Deixar para depois")){

    global_progress_bar_active = 1;
    for(int cont=0; cont < migrates_not_loaded_qnt; cont++){

      const char *text = "Executando arquivo ";
      char filepath[ strlen(MIGRATE_FOLDER) + 3 + strlen(migrates_not_loaded[cont]) ];
      char msg[ strlen(text) + strlen(migrates_not_loaded[cont]) ];
      sprintf(msg,"%s%s",text, migrates_not_loaded[cont]);
      global_progress_bar_text = strdup(msg);
      sprintf(filepath, "%s/%s", MIGRATE_FOLDER, migrates_not_loaded[cont]);
      if(run_sql_from_file(filepath)){
        global_progress_bar_active = 0;
        if(error_migrate_popup()){
          return 1;
        }
      }

    }
    global_progress_bar_active = 0;
    popup(NULL,"Migrates atualizados com sucesso");
  }


  return 0;
}

int remove_migrates(){
  int atual_version_pos = 0, versions_qnt;
  if(get_migrate_loaded()){
    return 1;
  }

  for(int cont=0; version_migrates_list[cont][VER_MIGRATES_VERSION]; cont++){
    if(!strcmp(GET_APP_VERSION_NAME(), version_migrates_list[cont][VER_MIGRATES_VERSION])){
        atual_version_pos = cont;
    }
    versions_qnt++;
  }

  int migrates_loaded_qnt = 0;
  char **migrates_loaded = malloc(sizeof(char*) *versions_qnt);
  for(int cont=0; version_migrates_list[cont][VER_MIGRATES_VERSION]; cont++){
    if(cont<=atual_version_pos){
      if(!migrate_is_loaded(version_migrates_list[cont][UP_MIGRATE_FILE])){
        continue;
      }
      migrates_loaded[migrates_loaded_qnt] = strdup(version_migrates_list[cont][DOWN_MIGRATE_FILE]);
      migrates_loaded_qnt++;
    }
  }

  if(migrates_loaded_qnt){
    char msg[200];
    sprintf(msg, "As alterações do banco de dados serão resetadas\nExistem %i migrates para downgrade, continuar?", migrates_loaded_qnt);
    if(PopupBinario(msg, "Sim, faça o processo", "Deixar para depois")){
      global_progress_bar_active = 1;
      for(int cont=migrates_loaded_qnt-1; cont >= 0 ; cont--){
        if(migrates_loaded[cont]){
          int filepath_len = strlen(MIGRATE_FOLDER) + 2 + strlen(migrates_loaded[cont]);
          char filepath[ filepath_len ];
          sprintf(msg, "Executando arquivo %s", migrates_loaded[cont]);
          global_progress_bar_text = strdup(msg);
          sprintf(filepath, "%s/%s", MIGRATE_FOLDER, migrates_loaded[cont]);
          if(run_sql_from_file(filepath)){
            global_progress_bar_active = 0;
            if(error_migrate_popup())
              return 1;
          }
        }
      }
      global_progress_bar_active = 0;
      popup(NULL,"Migrates removidos com sucesso (É altamente recomendado a reinicialização do sistema)");
    }
  }else{
    popup(NULL,"Não migrates para remover");
  }

  return 0;
}
