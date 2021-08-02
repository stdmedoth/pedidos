int consulta_contrib_consulta(gchar *cnpj, gchar *uf, struct _terc_infos *contrib){

  CURL *curl = curl_easy_init();
  struct upload_status upload_ctx;
  upload_ctx.lines_read = 0;
  struct MemoryStruct header_chunk, body_chunk;
  gchar *useragent = strdup("curl/7.39.0");

  if(!contrib){
    popup(NULL,"Objeto de contribuinte não criado");
    return 1;
  }

  header_chunk.memory = malloc(1);
  header_chunk.size = 0;

  body_chunk.memory = malloc(1);
  body_chunk.size = 0;

  xmlDocPtr doc = consulta_contrib_cria_xml(cnpj, uf);
  if(!doc){
    popup(NULL,"Não foi possível criar xml de consulta");
    return 1;
  }
  xmlNodePtr ConsCad = xmlDocGetRootElement(doc);
  if(!ConsCad){
    popup(NULL,"Documento de consulta sem tag root");
    return 1;
  }

  const gchar soup_header[] =
  "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"
  "<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://www.w3.org/2003/05/soap-envelope\">"
  "<soap:Header>"
  "<nfeCabecMsg xmlns=\"http://www.portalfiscal.inf.br/nfe/wsdl/CadConsultaCadastro4\">"
  "<cUF>35</cUF>"
  "<versaoDados>4.00</versaoDados>"
  "</nfeCabecMsg>"
  "</soap:Header>"
  "<soap:Body>"
  "<nfeDadosMsg xmlns=\"http://www.portalfiscal.inf.br/nfe/wsdl/CadConsultaCadastro4\">";

  const gchar soup_footer[] =
  "</nfeDadosMsg>"
  "</soap:Body>"
  "</soap:Envelope>";

  int size;
  gchar *content;
  xmlBufferPtr xmlbuf = xmlBufferCreate();
  xmlNodePtr conscad = xmlDocGetRootElement(doc);
  if(!xmlNodeDump(xmlbuf, doc, conscad, 0,0)){
    popup(NULL,"Não foi possível gerar o conteúdo da requisição");
    return 1;
  }
  content = (gchar*) xmlBufferContent(xmlbuf);

  gchar *soup_request = malloc( strlen(soup_header) + strlen(content) + strlen(soup_footer) + 1);
  sprintf(soup_request, "%s%s%s", soup_header, content, soup_footer);

  curl_easy_setopt(curl, CURLOPT_URL, "https://homologacao.nfe.fazenda.sp.gov.br/ws/cadconsultacadastro4.asmx");

  curl_easy_setopt(curl, CURLOPT_POST, 1L);

  //curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

  curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
  curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);

  //curl_easy_setopt(curl, CURLOPT_USERPWD, "clark:kent");
  curl_easy_setopt(curl,CURLOPT_USERAGENT, useragent);

  if(!fopen(cad_emp_strc.digcertpath, "r")){
    popup(NULL,"Não foi possível encontrar certificado");
    return 1;
  }

  curl_easy_setopt(curl, CURLOPT_CAINFO, cad_emp_strc.digcertpath);
  curl_easy_setopt(curl, CURLOPT_SSLCERT, cad_emp_strc.digcertpath);
  curl_easy_setopt(curl, CURLOPT_SSLCERTPASSWD, cad_emp_strc.digcertpass);

  //curl_easy_setopt(curl, CURLOPT_SSLKEY, "/home/calistu/Desktop/pedidos/iceminas.pem");
  //curl_easy_setopt(curl, CURLOPT_KEYPASSWD, "1234");

  curl_easy_setopt(curl, CURLOPT_CAPATH, "/etc/ssl/certs/");

  header_chunk.memory = strdup("Sem header");
  body_chunk.memory = strdup("Sem body");

  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_chunk);

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body_chunk);

  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, soup_request);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(soup_request));

  gchar *length = malloc(100);
  sprintf(length,"Content-Length: %li", (long unsigned int) strlen(soup_request));
  struct curl_slist *header=NULL;
  header = curl_slist_append(header, length);
  header = curl_slist_append(header, "Accept: application/soap+xml, multipart/related");
  header = curl_slist_append(header, "Content-Type: text/xml; charset=utf-8; action=\"http://www.portalfiscal.inf.br/nfe/wsdl/CadConsultaCadastro4/consultaCadastro\"");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

  CURLcode res = curl_easy_perform(curl);
  gchar *msg;
  if(res  != CURLE_OK){
    switch (res) {
      case CURLE_REMOTE_ACCESS_DENIED:
        popup(NULL, "Acesso Negado!");
        return 1;

      case CURLE_COULDNT_CONNECT:
        popup(NULL, "Não foi possível conectar no webservice!");
        return 1;

      case CURLE_COULDNT_RESOLVE_HOST:
        popup(NULL, "Não foi possível resolver nome!");
        return 1;

      case CURLE_HTTP2_STREAM:
        popup(NULL, "Utilize HTTP v1!");
        return 1;

      case CURLE_HTTP_RETURNED_ERROR:
        popup(NULL, "Erro de retorno da SEFAZ!");
        return 1;

      default:
        msg = malloc(30 + strlen(curl_easy_strerror(res)));
        sprintf(msg,"Erro na consulta: %i %s", res, curl_easy_strerror(res));
        popup(NULL, msg);
        return 1;
    }
  }
  if(!header_chunk.memory){
    popup(NULL, "Responta do servidor sem header");
    return 1;
  }
  if(!body_chunk.memory){
    popup(NULL, "Responta do servidor sem corpo");
    return 1;
  }

  xmlDocPtr resp_doc = xmlReadDoc((xmlChar*)body_chunk.memory, "", "UTF-8", XML_PARSE_PEDANTIC);
  if(!resp_doc){
    popup(NULL,"Erro ao fazer parser da resposta");
    autologger(body_chunk.memory);
    return 1;
  }
  //g_print("%s\n",body_chunk.memory);

  xmlNodePtr status_node = get_tag_by_namepath(resp_doc, "//*[name()=\"cStat\"]");
  if(!status_node){
    popup(NULL,"Não foi possível receber status da consulta");
    return 1;
  }
  xmlNodePtr motivo_node = get_tag_by_namepath(resp_doc, "//*[name()=\"xMotivo\"]");
  if(!motivo_node){
    popup(NULL,"Não foi possível receber mensagem de resultado da consulta");
    return 1;
  }

  gchar *status_msg=NULL,*motivo_msg=NULL;
  xmlBufferPtr status_buf = xmlBufferCreate();
  xmlBufferPtr motivo_buf = xmlBufferCreate();

  autologger(soup_request);

  status_msg = (gchar*) xmlNodeGetContent(status_node);
  if(!status_msg){
    popup(NULL,"Não foi possível receber conteudo do status");
    return 1;
  }
  motivo_msg = (gchar*) xmlNodeGetContent(motivo_node);
  if(!motivo_msg){
    popup(NULL,"Não foi possível receber motivo do status");
    return 1;
  }

  if(atoi(status_msg) != 111){
    if(strlen(motivo_msg)){
      autologger("Erro ao consultar contribuinte");
      autologger(status_msg);
      autologger(motivo_msg);
      autologger(body_chunk.memory);
      popup(NULL,motivo_msg);
      return 1;
    }else{
      popup(NULL,"Não foi possível receber motivo do erro");
      return 1;
    }
  }

  g_print("\nResposta do header \n\n%s\n\n",header_chunk.memory);
  g_print("\nResposta do body \n\n%s\n\n",body_chunk.memory);

  xmlNodePtr nome_node = get_tag_by_namepath(resp_doc, "//*[name()=\"xNome\"]");
  if(nome_node && xmlNodeGetContent(nome_node)){
    contrib->razao = strdup((gchar*)xmlNodeGetContent(nome_node));
  }else{
    autologger("Não foi possível receber nome na consulta");
    return 1;
  }

  xmlNodePtr cnpj_node = get_tag_by_namepath(resp_doc, "//*[name()=\"CNPJ\"]");
  if(cnpj_node && xmlNodeGetContent(cnpj_node)){
    contrib->doc = strdup((gchar*)xmlNodeGetContent(cnpj_node));
  }else{
    autologger("Não foi possível receber cnpj na consulta");
    return 1;
  }

  xmlNodePtr ie_node = get_tag_by_namepath(resp_doc, "//*[name()=\"IE\"]");
  if(ie_node && xmlNodeGetContent(ie_node)){
    contrib->ie = strdup((gchar*)xmlNodeGetContent(ie_node));
  }else{
    autologger("Não foi possível receber cnpj na consulta");
    return 1;
  }


  xmlNodePtr cep_node = get_tag_by_namepath(resp_doc, "//*[name()=\"CEP\"]");
  if(!cep_node || !xmlNodeGetContent(cep_node)){
    popup(NULL,"Não foi possível receber cep na consulta");
    return 1;
  }
  xmlNodePtr logr_node = get_tag_by_namepath(resp_doc, "//*[name()=\"xLgr\"]");
  if(!logr_node || !xmlNodeGetContent(logr_node)){
    popup(NULL,"Não foi possível receber logradouro na consulta");
    return 1;
  }

  xmlNodePtr bairro_node = get_tag_by_namepath(resp_doc, "//*[name()=\"xBairro\"]");
  if(!bairro_node || !xmlNodeGetContent(bairro_node)){
    popup(NULL,"Não foi possível receber bairro na consulta");
    return 1;
  }

  xmlNodePtr ibgecid_node = get_tag_by_namepath(resp_doc, "//*[name()=\"cMun\"]");
  if(!ibgecid_node || !xmlNodeGetContent(ibgecid_node)){
    popup(NULL,"Não foi possível receber código IBGE na consulta");
    return 1;
  }

  xmlNodePtr cidade_node = get_tag_by_namepath(resp_doc, "//*[name()=\"xMun\"]");
  if(!cidade_node || !xmlNodeGetContent(cidade_node)){
    popup(NULL,"Não foi possível receber cidade na consulta");
    return 1;
  }

  xmlNodePtr uf_node = get_tag_by_namepath(resp_doc, "//*[name()=\"UF\"]");
  if(!uf_node || !xmlNodeGetContent(uf_node)){
    popup(NULL,"Não foi possível receber UF na consulta");
    return 1;
  }

  struct _cad_cep *cep=NULL;
  contrib->cep = (gchar*)xmlNodeGetContent(cep_node);

  if(!(cep = get_ender_by_cep(contrib->cep))){

    cep = malloc(sizeof(struct _cad_cep));
    cep->cep = strdup(contrib->cep);
    cep->ldescricao = (gchar*)xmlNodeGetContent(logr_node);
    cep->bairro = (gchar*)xmlNodeGetContent(bairro_node);


    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[MAX_QUERY_LEN];

    cep->cidade = malloc(sizeof(struct _cad_cidade));
    cep->cidade->code = tasker("cidade");
    cep->cidade->descricao = (gchar*)xmlNodeGetContent(cidade_node);
    cep->cidade->uf = (gchar*)xmlNodeGetContent(uf_node);
    cep->cidade->code_ibge = atoi((gchar*)xmlNodeGetContent(ibgecid_node));

    if(!cep->cidade->code_ibge){
      popup(NULL,"Código IBGE não identificado");
      return 1;
    }

    if(PopupBinario("CEP novo encontrado na consulta, deseja importar?", "Sim! aumente o meu banco de dados", "Não! irei cadastrar manualmente")){
      sprintf(query, "select code from cidade where codigo_ibge = %i", cep->cidade->code_ibge);
      if(!(res = consultar(query))){
        popup(NULL,"Não foi possível pesquisar existencia da cidade");
        return 1;
      }
      if(!(row = mysql_fetch_row(res))){
        sprintf(query, "insert into cidade(code, descricao, uf, codigo_ibge, ddd) values(%i, '%s', '%s', %i, '')",
          cep->cidade->code,
          cep->cidade->descricao,
          cep->cidade->uf,
          cep->cidade->code_ibge
        );
        if(enviar_query(query)){
          popup(NULL,"Não foi possível cadastrar a cidade");
          return 1;
        }
      }else{
        cep->cidade->code = atoi(row[0]);
      }

      sprintf(query, "insert into logradouro(CEP, tipo, descricao, id_cidade, UF, descricao_cidade, codigo_cidade_ibge, descricao_bairro) values('%s', 1, '%s', %i, '%s', '%s', %i, '%s')",
        cep->cep,

        cep->ldescricao,
        cep->cidade->code,
        cep->cidade->uf,
        cep->cidade->descricao,
        cep->cidade->code_ibge,
        cep->bairro);

      if(enviar_query(query)){
        popup(NULL,"Não foi possível cadastrar o cep");
        return 1;
      }
    }
  }
  curl_easy_cleanup(curl);

  return 0;
}
