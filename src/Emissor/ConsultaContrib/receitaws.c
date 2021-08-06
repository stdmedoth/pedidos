struct _consulta_cnpj *consulta_contrib_receitaws(const char *cnpj){

  char *url = malloc(strlen(APP_CONSULT_DOC_URL) + strlen(cnpj) + 2);
  sprintf(url, "%s/%s", APP_CONSULT_DOC_URL, cnpj);
  char *response_file = get_response(url);
  if(!response_file){
    return NULL;
  }

  const char *empty_field = "\"\"";

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

  const gchar *status = json_object_get_string_member (obj, "status");
  if(!status){
    return NULL;
  }

  const gchar *situacao = json_object_get_string_member (obj, "situacao");
  if(!situacao){
    situacao = "";
  }

  if(strcmp(status, "OK")){
    const gchar *message = json_object_get_string_member (obj, "message");
    if(!message){
      return NULL;
    }
    popup(NULL, message);
    return NULL;
  }

  if(strcmp(situacao, "ATIVA")){
    popup(NULL, "OBS: CNPJ não está mais ativo na receita");
  }

  const gchar *nome = json_object_get_string_member (obj, "nome");
  if(!nome){
    nome = "";
  }

  //const gchar *cnpj = json_object_get_string_member (obj, "cnpj");
  const gchar *ie = NULL;
  if(json_object_has_member (obj, "ie")){
    ie = json_object_get_string_member (obj, "ie");
  }

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

  const gchar *uf = json_object_get_string_member (obj, "uf");
  if(!uf){
    uf = "";
  }


  consulta_receitaws->contato = malloc(sizeof(struct _Contato));
  consulta_receitaws->contatos_qnt = 0;
  const gchar *email = json_object_get_string_member (obj, "email");
  if(!email || !strlen(email) || !strcmp(empty_field, email)){
    email = "";
  }else{
    consulta_receitaws->contatos_qnt = 1;
    consulta_receitaws->contato[0].email = strdup(email);
  }

  const gchar *telefone = json_object_get_string_member (obj, "telefone");
  if(!telefone || !strlen(telefone) || !strcmp(empty_field, telefone)){
    telefone = "";
  }else{
    consulta_receitaws->contatos_qnt = 1;
    consulta_receitaws->contato[0].telefone = strdup(telefone);
  }

  if(consulta_receitaws->contatos_qnt){
    consulta_receitaws->contato[0].ativo = 1;
    consulta_receitaws->contato[0].exists = 0;
  }

  consulta_receitaws->contato[0].nome = g_strdup ("-");
  consulta_receitaws->contato[0].celular = g_strdup ("-");

  consulta_receitaws->cnpj = strdup(cnpj);
  consulta_receitaws->xNome = strdup(nome);
  consulta_receitaws->NFantasia = strdup(fantasia);
  consulta_receitaws->IE = strdup(ie);
  consulta_receitaws->CEP = format_only_num(strdup(cep));
  consulta_receitaws->xLgr = strdup(logradouro);
  consulta_receitaws->nro = strdup(numero);
  consulta_receitaws->xBairro = strdup(bairro);
  consulta_receitaws->xMun = strdup(municipio);
  consulta_receitaws->UF = strdup(uf);


  return consulta_receitaws;
}
