int consulta_contrib_consulta(gchar *cnpj, gchar *uf){

  CURL *curl = curl_easy_init();
  struct upload_status upload_ctx;
  upload_ctx.lines_read = 0;
  xmlBufferPtr xmlbuf = xmlBufferCreate();
  struct MemoryStruct chunk;
  gchar *useragent = strdup("curl/7.39.0");

  chunk.memory = malloc(1);
  chunk.size = 0;

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

  curl_easy_setopt(curl, CURLOPT_URL, "https://nfe.fazenda.sp.gov.br/ws/cadconsultacadastro4.asmx");
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl, CURLOPT_POST, 1L);
  curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
  curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
  curl_easy_setopt(curl,CURLOPT_USERAGENT, useragent);

  //curl_easy_setopt(curl, CURLOPT_CAINFO, "/home/calistu/Desktop/pedidos/iceminas.pem");
  curl_easy_setopt(curl, CURLOPT_SSLCERT, "/home/calistu/Desktop/pedidos/iceminas.pem");
  //curl_easy_setopt(curl, CURLOPT_SSLCERTPASSWD, "1234");

  curl_easy_setopt(curl, CURLOPT_SSLKEY, "/home/calistu/Desktop/pedidos/iceminas.pem");
  curl_easy_setopt(curl, CURLOPT_KEYPASSWD, "1234");


  curl_easy_setopt(curl, CURLOPT_READFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_READDATA, &chunk);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

  gchar *content;
  int size;
  xmlDocDumpMemory(doc,(xmlChar**) &content, &size);
  //g_print(content);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(content));

  gchar *length = malloc(100);
  sprintf(length,"Content-Length: %li", strlen(content));
  struct curl_slist *header=NULL;
  header = curl_slist_append(header, length);
  header = curl_slist_append(header, "Accept: application/soap+xml, multipart/related");
  header = curl_slist_append(header, "Content-Type: application/soap+xml; charset=utf-8");
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);


  CURLcode res = curl_easy_perform(curl);
  gchar *msg;
  if(res  != CURLE_OK){
    switch (res) {
      case CURLE_REMOTE_ACCESS_DENIED:
        popup(NULL, "Acesso Negado!");
        break;

      case CURLE_COULDNT_CONNECT:
        popup(NULL, "Não foi possível conectar no webservice!");
        break;

      case CURLE_COULDNT_RESOLVE_HOST:
        popup(NULL, "Não foi possível resolver nome!");
        break;

      case CURLE_HTTP2_STREAM:
        popup(NULL, "Utilize HTTP v1!");
        break;

      case CURLE_HTTP_RETURNED_ERROR:
        popup(NULL, "Erro de retorno da SEFAZ!");
        break;

      default:
        msg = malloc(20 + strlen(curl_easy_strerror(res)));
        sprintf(msg,"Erro na consulta: %i %s", res, curl_easy_strerror(res));
        popup(NULL, msg);
        break;
    }
  }
  curl_easy_cleanup(curl);
  return 0;
}
