#include "libs.h"

int rec_vars_from_file(){

  xmlDocPtr doc = xmlParseFile(SERVER_CONF);

  if(!doc){
    popup(NULL,"Não foi possível ler arquivo de configuração");
    file_logger("Não foi possivel abrir xml de configuração server");
    return 1;
  }

  xmlNodePtr root = xmlDocGetRootElement(doc);
  xmlNodePtr endereco_tag = get_tag_by_namepath(doc,"/server_conf/endereco");
  xmlNodePtr user_tag = get_tag_by_namepath(doc,"/server_conf/usuario");
  xmlNodePtr senha_tag = get_tag_by_namepath(doc,"/server_conf/senha");
  xmlNodePtr database_tag = get_tag_by_namepath(doc,"/server_conf/banco");

  if(!endereco_tag || !xmlNodeGetContent(endereco_tag)){
    popup(NULL,"Não foi possível receber endereço do server");
    return 1;
  }
  if(!user_tag || !xmlNodeGetContent(user_tag)){
    popup(NULL,"Não foi possível receber usuario do server");
    return 1;
  }
  if(!senha_tag || !xmlNodeGetContent(senha_tag)){
    popup(NULL,"Não foi possível receber senha do server");
    return 1;
  }
  if(!database_tag || !xmlNodeGetContent(database_tag)){
    popup(NULL,"Não foi possível receber banco de dados do server");
    return 1;
  }

  server_confs.server_endereco = strdup((char*)xmlNodeGetContent(endereco_tag));
  server_confs.server_user = strdup((char*)xmlNodeGetContent(user_tag));
  server_confs.server_senha = strdup((char*)xmlNodeGetContent(senha_tag));
  server_confs.server_database = strdup((char*)xmlNodeGetContent(database_tag));

  file_logger(server_confs.server_endereco);
  file_logger(server_confs.server_user);
  file_logger(server_confs.server_senha);
  file_logger(server_confs.server_database);
  return 0;
}
