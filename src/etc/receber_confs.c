static struct {
  char server_endereco[MAX_SERVER_LEN];
  char server_user[MAX_SEN_LEN];
  char server_senha[MAX_SEN_LEN];
  char server_database[MAX_SEN_LEN];
}server_confs;

int rec_vars_from_file(){
  FILE *conf;
  char variaveis[MAX_VAR_LEN*2+1];
  char server_endereco[MAX_SERVER_LEN];
  char server_user[MAX_SEN_LEN];
  char server_senha[MAX_SEN_LEN];
  char server_database[MAX_SEN_LEN];

  char *conf_string;
  int ascii=0, cont=0;

  conf_string = malloc(MAX_CONF_STRING_LEN);

  if((conf = fopen(SERVER_CONF,"r"))==NULL){
    popup(NULL,"Não foi possivel encontrar arquivo de configuração de servidores");
    g_print("%s\n",strerror(errno));
    return 1;
  }
  strcpy(server_endereco,"");
  strcpy(server_user,"");
  strcpy(server_senha,"");
  strcpy(server_database,"");

  while((ascii = fgetc(conf)) != EOF){
    conf_string[cont] = ascii;
    cont++;
  }

  if(!strstr(conf_string,SERVER_VAR_NAME)){
    popup(NULL,"Endereço não foi possivel encontrar endereco do servidor");
    return 1;
  }
  strcpy(server_endereco,strstr(conf_string,SERVER_VAR_NAME)+strlen(SERVER_VAR_NAME));

  if(!strstr(conf_string,USER_VAR_NAME)){
    popup(NULL,"Endereço não foi possível encontrar usuário do servidor");
    return 1;
  }
  strcpy(server_user,strstr(conf_string,USER_VAR_NAME)+strlen(USER_VAR_NAME));

  if(!strstr(conf_string,SENHA_VAR_NAME)){
    popup(NULL,"Endereço não foi possível encontrar senha do servidor");
    return 1;
  }
  strcpy(server_senha,strstr(conf_string,SENHA_VAR_NAME)+strlen(SENHA_VAR_NAME));

  if(!strstr(conf_string,DATABASE_VAR_NAME)){
    popup(NULL,"Endereço não foi possível encontrar banco de dados do servidor");
    return 1;
  }
  strcpy(server_database,strstr(conf_string,DATABASE_VAR_NAME)+strlen(DATABASE_VAR_NAME));

  cont=0;
  while(cont<strlen(server_endereco)){
    if(server_endereco[cont] == '\n'||server_endereco[cont] == '\r'){
      server_endereco[cont] = '\0';
      break;
    }
    cont++;
  }
  cont=0;
  while(cont<strlen(server_user)){
    if(server_user[cont] == '\n'||server_user[cont] == '\r'){
      server_user[cont] = '\0';
      break;
    }
    cont++;
  }
  cont=0;
  while(cont<strlen(server_senha)){
    if(server_senha[cont] == '\n'||server_senha[cont] == '\r'){
      server_senha[cont] = '\0';
      break;
    }
    cont++;
  }

  cont=0;
  while(cont<strlen(server_database)){
    if(server_database[cont] == '\n' || server_database[cont] == '\r'){
      server_database[cont] = '\0';
      break;
    }
    cont++;
  }

  strcpy(server_confs.server_endereco,server_endereco);
  strcpy(server_confs.server_user,server_user);
  strcpy(server_confs.server_senha,server_senha);
  strcpy(server_confs.server_database,server_database);

  file_logger(server_confs.server_endereco);
  file_logger(server_confs.server_user);
  file_logger(server_confs.server_senha);
  file_logger(server_confs.server_database);
  return 0;
}
