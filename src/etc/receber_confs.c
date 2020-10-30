#include "libs.h"

int rec_vars_from_file(){

  server_confs.server_endereco = malloc(MAX_SERVER_LEN);
  server_confs.server_user = malloc(MAX_SEN_LEN);
  server_confs.server_senha = malloc(MAX_SEN_LEN);
  server_confs.server_database = malloc(MAX_SERVER_LEN);

  xmlDocPtr doc = xmlParseFile(SERVER_CONF);

  if(!doc){
      popup(NULL,"Não foi possível ler arquivo de configuração");
      file_logger("Não foi possivel abrir xml de configuração server");
      return 1;
  }

  xmlNodePtr root = xmlDocGetRootElement(doc);
  xmlNodePtr server_conf = getContentByTagName(root,"server_conf");
  xmlNodePtr endereco_tag = getContentByTagName(root,"endereco");
  xmlNodePtr user_tag = getContentByTagName(root,"usuario");
  xmlNodePtr senha_tag = getContentByTagName(root,"senha");
  xmlNodePtr database_tag = getContentByTagName(root,"banco");

  if(endereco_tag)
    strcpy(server_confs.server_endereco,(char *)endereco_tag->content);
  else{
    popup(NULL,"Não foi possível receber endereço do server");
    return 1;
  }

  if(user_tag)
    strcpy(server_confs.server_user,(char *)user_tag->content);
  else{
    popup(NULL,"Não foi possível receber usuario do server");
    return 1;
  }

  if(senha_tag)
    strcpy(server_confs.server_senha,(char *)senha_tag->content);
  else{
    popup(NULL,"Não foi possível receber senha do server");
    return 1;
  }

  if(database_tag)
    strcpy(server_confs.server_database,(char *)database_tag->content);
  else{
    popup(NULL,"Não foi possível receber banco de dados do server");
    return 1;
  }

  file_logger(server_confs.server_endereco);
  file_logger(server_confs.server_user);
  file_logger(server_confs.server_senha);
  file_logger(server_confs.server_database);
  return 0;
}
