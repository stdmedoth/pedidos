struct _cad_cep *get_cep_from_consulta(gchar *cep){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN],
  code_task[MAX_CODE_LEN];

  CURL *curl = curl_easy_init();
  struct upload_status upload_ctx;
  upload_ctx.lines_read = 0;
  struct MemoryStruct header_chunk, body_chunk;

  struct _cad_cep *cad_cep = malloc(sizeof(struct _cad_cep));
  cad_cep->cidade = malloc(sizeof(struct _cad_cidade));

  header_chunk.memory = malloc(1);
  header_chunk.size = 0;

  body_chunk.memory = malloc(1);
  body_chunk.size = 0;

  gchar *consulta_url = malloc(200 + strlen(cep));
  //gchar *ws_url = strdup("https://viacep.com.br/ws");
  gchar *ws_url = strdup("https://viacep.com.br/ws/");
  sprintf(consulta_url,"%s%s/xml", ws_url, cep);

  curl_easy_setopt(curl, CURLOPT_URL, consulta_url);
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_NONE);
  curl_easy_setopt(curl, CURLOPT_CAINFO, MOZ_CERT);
  
  //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
  //curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

  //curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_SSLv3);
  //curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_DEFAULT);

  //curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

  //curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

  //curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
  //curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);

  //curl_easy_setopt(curl,CURLOPT_USERAGENT, "curl/7.39.0");

  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_chunk);

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body_chunk);

  struct curl_slist *header=NULL;
  header = curl_slist_append(header, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
  //header = curl_slist_append(header, "Accept-Encoding: gzip, deflate, br");
  //header = curl_slist_append(header, "Accept-Language: pt-BR,pt;q=0.9,en;q=0.8");
  header = curl_slist_append(header, "Content-Type: text/xml; charset=utf-8;");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

  CURLcode curl_res = curl_easy_perform(curl);
  gchar *msg;

  autologger("consultando cep...");
  autologger(consulta_url);
  autologger("resposta header");
  autologger(header_chunk.memory);
  autologger("resposta body");
  autologger(body_chunk.memory);

  if(curl_res  != CURLE_OK){

    switch (curl_res) {
      case CURLE_REMOTE_ACCESS_DENIED:
        popup(NULL, "Acesso Negado!");
        return NULL;

      case CURLE_COULDNT_CONNECT:
        popup(NULL, "Não foi possível conectar no webservice!");
        return NULL;

      case CURLE_COULDNT_RESOLVE_HOST:
        popup(NULL, "Não foi possível resolver nome!");
        return NULL;

      case CURLE_HTTP2_STREAM:
        popup(NULL, "Utilize HTTP v1!");
        return NULL;

      case CURLE_HTTP_RETURNED_ERROR:
        popup(NULL, "Erro de retorno do webservice!");
        return NULL;

      default:
        msg = malloc(100 + strlen(curl_easy_strerror(curl_res)));
        sprintf(msg,"Erro código %i na consulta:\n%s", curl_res, curl_easy_strerror(curl_res));
        popup(NULL, msg);
        return NULL;
    }
  }
  xmlDocPtr resp_doc = xmlReadDoc((xmlChar*)body_chunk.memory, "", "UTF-8", XML_PARSE_RECOVER);
  if(!resp_doc){
    popup(NULL,"Erro ao fazer parser da resposta do servidor");
    return NULL;
  }

  curl_easy_cleanup(curl);

  xmlNodePtr cep_node = get_tag_by_namepath(resp_doc, "//*[name()=\"cep\"]");

  xmlNodePtr logradouro_node = get_tag_by_namepath(resp_doc, "//*[name()=\"logradouro\"]");

  xmlNodePtr bairro_node = get_tag_by_namepath(resp_doc, "//*[name()=\"bairro\"]");

  xmlNodePtr cidade_node = get_tag_by_namepath(resp_doc, "//*[name()=\"localidade\"]");

  xmlNodePtr uf_node = get_tag_by_namepath(resp_doc, "//*[name()=\"uf\"]");

  xmlNodePtr ibge_node = get_tag_by_namepath(resp_doc, "//*[name()=\"ibge\"]");

  xmlNodePtr ddd_node = get_tag_by_namepath(resp_doc, "//*[name()=\"ddd\"]");

  xmlNodePtr erro_node = get_tag_by_namepath(resp_doc, "//*[name()=\"erro\"]");

  if(erro_node){
    popup(NULL,"O webservice retornou erro");
    return NULL;
  }

  if(cep_node && xmlNodeGetContent(cep_node)){
    cad_cep->cep = strdup((gchar*)xmlNodeGetContent(cep_node));
  }else{
    autologger("Não foi possível receber cep na consulta");
    return NULL;
  }

  if(logradouro_node && xmlNodeGetContent(logradouro_node)){
    cad_cep->ldescricao = strdup((gchar*)xmlNodeGetContent(logradouro_node));
  }else{
    autologger("Não foi possível receber logradouro na consulta");
    return NULL;
  }

  if(cep_node && xmlNodeGetContent(bairro_node)){
    cad_cep->bairro = strdup((gchar*)xmlNodeGetContent(bairro_node));
  }else{
    autologger("Não foi possível receber bairro na consulta");
    return NULL;
  }

  if(cidade_node && xmlNodeGetContent(cidade_node)){
    cad_cep->cidade->descricao = strdup((gchar*)xmlNodeGetContent(cidade_node));
  }else{
    autologger("Não foi possível receber cidade na consulta");
    return NULL;
  }

  if(uf_node && xmlNodeGetContent(uf_node)){
    cad_cep->cidade->uf = strdup((gchar*)xmlNodeGetContent(uf_node));
  }else{
    autologger("Não foi possível receber UF na consulta");
    return NULL;
  }

  if(ddd_node && xmlNodeGetContent(ddd_node)){
    cad_cep->cidade->ddd = strdup((gchar*)xmlNodeGetContent(ddd_node));
  }else{
    autologger("Não foi possível receber DDD da UF na consulta");
    return NULL;
  }

  if(ibge_node && xmlNodeGetContent(ibge_node)){
    cad_cep->cidade->code_ibge = atoi((gchar*)xmlNodeGetContent(ibge_node));
  }else{
    autologger("Não foi possível receber Código IBGE na consulta");
    return NULL;
  }

  return cad_cep;
}


int cad_ceps_consultar_fun(){

  char query[MAX_QUERY_LEN];
  cad_ceps_consultando = 1;
  gtk_widget_set_sensitive(cad_cep_consulta_button, FALSE);

  g_main_context_iteration(NULL,FALSE);

  if(cad_ceps_code_fun()){
    gtk_widget_set_sensitive(cad_cep_consulta_button, TRUE);
    return 1;
  }

  if(cad_ceps_cep_fun())
    return 1;

  struct _cad_cep *cep_consultado = get_cep_from_consulta(strdup(cad_ceps_cep_gchar));

  if(!cep_consultado){
    popup(NULL,"Não foi possível receber dados na consulta");
    gtk_widget_set_sensitive(cad_cep_consulta_button, TRUE);
    return 1;
  }

  autologger("Preechendo campos do cep");
  //gtk_entry_set_text(GTK_ENTRY(cad_ceps_cep_entry), cep_consultado->cep);
  struct _cad_cidade *cidade;
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_descr_entry), cep_consultado->ldescricao);
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_bairro_entry), cep_consultado->bairro);
  gtk_combo_box_set_active_id(GTK_COMBO_BOX(cad_ceps_uf_combo), cep_consultado->cidade->uf);

  while(!(cidade = get_cidade_by_ibgecode(cep_consultado->cidade->code_ibge))){
    sprintf(query,"insert into cidade(descricao, uf, codigo_ibge, ddd) values('%s', '%s', %i, '%s')",
      cep_consultado->cidade->descricao,
      cep_consultado->cidade->uf,
      cep_consultado->cidade->code_ibge,
      cep_consultado->cidade->ddd
    );
    if(enviar_query(query)){
      popup(NULL,"Não foi possível cadastrar a cidade para o cep");
      return 1;
    }
  }
  if(!(cidade = get_cidade_by_ibgecode(cep_consultado->cidade->code_ibge)))
    return 1;

  gchar *text = malloc(MAX_CODE_LEN);
  sprintf(text,"%i", cidade->code);
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_cid_code_entry), text);
  gtk_widget_activate(cad_ceps_cid_code_entry);

  gtk_widget_set_sensitive(cad_cep_consulta_button, TRUE);
  cad_ceps_consultando = 0;
  return 0;
}
