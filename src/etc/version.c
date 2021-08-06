int check_compat_version(){
  db_version = get_db_version();

  if(!db_version){
    file_logger("Sem versão do banco de dados");
    return 1;
  }

  if(strcmp(GET_APP_VERSION(), db_version)){
      int cont=0;
      while(compat_db_versions[cont]){
        if(! strcmp( compat_db_versions[cont], db_version) ){
          return 0;
        }
        cont++;
      }
      return 1;
  }

  return 0;
}

char *get_db_version(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  sprintf(query, "select versao from versao");
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível receber versao");
    return NULL;
  }
  if(!(row = mysql_fetch_row(res))  || !row[0]){
    popup(NULL,"Não há informação de versão cadastrada");
    return NULL;
  }

  return strdup(row[0]);
}
