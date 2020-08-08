static struct {
  char *server_endereco;
  char *server_user;
  char *server_senha;
  char *server_database;
}server_confs;


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
  xmlNodePtr server_conf = root->children;
  xmlNodePtr endereco_tag = server_conf->next;
  xmlNodePtr user_tag = endereco_tag->next->next;
  xmlNodePtr senha_tag = user_tag->next->next;
  xmlNodePtr database_tag = senha_tag->next->next;

  strcpy(server_confs.server_endereco,(char *)endereco_tag->children->content);
  strcpy(server_confs.server_user,(char *)user_tag->children->content);
  strcpy(server_confs.server_senha,(char *)senha_tag->children->content);
  strcpy(server_confs.server_database,(char *)database_tag->children->content);

  file_logger(server_confs.server_endereco);
  file_logger(server_confs.server_user);
  file_logger(server_confs.server_senha);
  file_logger(server_confs.server_database);
  return 0;
}
