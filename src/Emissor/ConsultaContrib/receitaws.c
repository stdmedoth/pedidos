struct _consulta_cnpj *consulta_contrib_receitaws(char *cnpj){

  char *url = malloc(strlen(APP_CONSULT_DOC_URL) + strlen(cnpj) + 2);
  sprintf(url, "%s/%s", APP_CONSULT_DOC_URL, cnpj);
  char *response_file = get_response(url);
  if(!response_file){
    return NULL;
  }

  struct _consulta_cnpj *consulta_receitaws = malloc(sizeof(struct _consulta_cnpj));
  printf("arquivo de resposta %s\n", response_file);

  JsonParser *parser = json_parser_new();
  GError *error = NULL;

  if(!json_parser_load_from_file(parser, response_file, &error)){
    return NULL;
  }

  JsonNode *root = json_parser_get_root (parser);
  JsonObject *obj = json_node_get_object(root);
  if(!obj){
    return NULL;
  }
  const gchar *nome = json_object_get_string_member (obj, "nome");
  if(!nome){
    nome = "";
  }

  //const gchar *cnpj = json_object_get_string_member (obj, "cnpj");
  const gchar *ie = json_object_get_string_member (obj, "ie");
  if(!ie){
    ie = "";
  }

  const gchar *fantasia = json_object_get_string_member (obj, "fantasia");
  if(!fantasia){
    fantasia = "";
  }

  const gchar *cep = json_object_get_string_member (obj, "cep");
  if(!cep){
    cep = "";
  }

  const gchar *logradouro = json_object_get_string_member (obj, "logradouro");
  if(!logradouro){
    logradouro = "";
  }

  const gchar *numero = json_object_get_string_member (obj, "numero");
  if(!numero){
    numero = "";
  }

  const gchar *bairro = json_object_get_string_member (obj, "bairro");
  if(!bairro){
    bairro = "";
  }

  const gchar *municipio = json_object_get_string_member (obj, "municipio");
  if(!municipio){
    municipio = "";
  }

  consulta_receitaws->cnpj = strdup(cnpj);
  consulta_receitaws->xNome = strdup(nome);
  consulta_receitaws->NFantasia = strdup(fantasia);
  consulta_receitaws->IE = strdup(ie);
  consulta_receitaws->CEP = format_only_num(strdup(cep));
  consulta_receitaws->xLgr = strdup(logradouro);
  consulta_receitaws->nro = strdup(numero);
  consulta_receitaws->xBairro = strdup(bairro);
  consulta_receitaws->xMun = strdup(municipio);


  return consulta_receitaws;
}
