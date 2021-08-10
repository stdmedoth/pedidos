int rec_vars_from_xml_file(){
  xmlDocPtr doc = xmlParseFile(SERVER_CONF_XML);

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

  return 0;

}

int rec_vars_from_json_file(){

  JsonParser *parser = json_parser_new();
  GError *error = NULL;

  if(!json_parser_load_from_file(parser, SERVER_CONF_JSON, &error)){
    return 1;
  }

  JsonNode *root = json_parser_get_root (parser);
  JsonObject *obj = json_node_get_object(root);
  if(!obj){
    return 1;
  }

  const gchar *endereco = json_object_get_string_member (obj, "endereco");
  if(!endereco){
    return 1;
  }
  server_confs.server_endereco = strdup(endereco);

  const gchar *usuario = json_object_get_string_member (obj, "usuario");
  if(!usuario){
    return 1;
  }
  server_confs.server_user = strdup(usuario);

  const gchar *senha = json_object_get_string_member (obj, "senha");
  if(!senha){
    return 1;
  }
  server_confs.server_senha = strdup(senha);

  const gchar *banco = json_object_get_string_member (obj, "banco");
  if(!banco){
    return 1;
  }
  server_confs.server_database = strdup(banco);

  return 0;

}

int rec_vars_from_file(){

  switch (param_funcionalidades.conf_format_file) {
    case JSON_FILE:
      if(rec_vars_from_json_file())
        return 1;
      break;

    case XML_FILE:
      if(rec_vars_from_xml_file())
        return 1;

      break;
  }

  file_logger(server_confs.server_endereco);
  file_logger(server_confs.server_user);
  file_logger(server_confs.server_senha);
  file_logger(server_confs.server_database);

  return 0;
}
