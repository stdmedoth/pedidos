int enviar_email_orcamento(char *nome_destino,char *email_destino, char *arquivo_orcamento){
  CURL *curl;
  CURLcode res = CURLE_OK;
  xmlNodePtr xml_email;
  char *corpo_email;
  char *email_cli = malloc(MAX_EMAIL_LEN);
  char *email_copia = malloc(MAX_EMAIL_LEN);
  char *inline_text = malloc(MAX_OBS_LEN);
  enviando_email=1;

  if(!nome_destino){
    popup(NULL,"Nome do destino nulo");
    return 1;
  }

  if(!email_destino){
    popup(NULL,"Email destino nulo");
    return 1;
  }

  if(!arquivo_orcamento){
    popup(NULL,"Caminho do arquivo nulo");
    return 1;
  }

  if(!cad_emp_strc.xNome || !cad_emp_strc.telefone){
    popup(NULL,"Não há nome ou telefone cadastrado para inserção no corpo do email");
    return 1;
  }

  //mensagem temporaria
  sprintf(inline_text,"Olá! ' %s '\r\nSegue pedido impresso referente aos produtos comprados na ' %s '.\r\nCaso haja alguma dúvida, ligar em ' %s '.\r\n",
  nome_destino,cad_emp_strc.xNome,cad_emp_strc.telefone);

  GDateTime *data = g_date_time_new_now(g_time_zone_new(NULL));
  char mensagem[1000];
  char **headers_text = malloc(MAX_EMAIL_LEN*2+MAX_NAME_LEN+MAX_DATE_LEN+50);;

  if(strlen(email_destino)<=0){
    popup(NULL,"Não há email para o cliente");
    return 1;
  }

  if(!fopen(arquivo_orcamento,"r")){
    popup(NULL,"Pedido não foi gerado impresso");
    return 1;
  }

  xml_email = confirmar_envio_email(email_destino,inline_text);
  if(!xml_email){
    return 0;
  }

  xmlNodePtr email_cli_nd = getContentByTagName(xml_email,"cliente");
  xmlNodePtr email_copia_nd = getContentByTagName(xml_email,"copia");
  xmlNodePtr inline_text_nd =getContentByTagName(xml_email,"corpo_email");

  strcpy(email_cli,"");
  strcpy(email_copia,"");
  strcpy(inline_text,"");


  if(email_cli_nd && email_cli_nd->content && strlen((char*)email_cli_nd->content) < MAX_EMAIL_LEN)
    strcpy(email_cli,(char*) email_cli_nd->content);
  else{
    popup(NULL,"Erro na identificação do email destino");
    return 1;
  }
  if(email_cli_nd && email_cli_nd->content && strlen((char*)email_cli_nd->content) < MAX_EMAIL_LEN)
    strcpy(email_copia,(char*) email_copia_nd->content);
  else{
    popup(NULL,"Erro na identificação do email copia");
    return 1;
  }
  if(email_cli_nd && email_cli_nd->content && strlen((char*)email_cli_nd->content) < MAX_OBS_LEN)
      strcpy(inline_text,(char*) inline_text_nd->content);
  else{
    popup(NULL,"Erro na identificação do arquivo de envio");
    return 1;
  }

  headers_text[0] = malloc(300);
  sprintf(headers_text[0],"Date: %s",g_date_time_format(data,"%T"));

  headers_text[1] = malloc(MAX_EMAIL_LEN + 10);
  sprintf(headers_text[1],"To: %s",email_cli);

  headers_text[2] = malloc(MAX_EMAIL_LEN + 10);
  if(strcmp(email_copia,SEM_EMAIL))
    sprintf(headers_text[2],"CC: %s",email_copia);
  else
    strcpy(headers_text[2]," ");

  headers_text[3] = malloc(MAX_NAME_LEN + 10);
  sprintf(headers_text[3],"Subject: Envio %s",cad_emp_strc.xNome);

  headers_text[4] = NULL;

  curl = curl_easy_init();
  if(curl_global_init(CURL_GLOBAL_ALL)){
    popup(NULL,"Não foi iniciar criar conexão");
    return 1;
  }
  if(curl) {
    struct curl_slist *headers = NULL;
    struct curl_slist *recipients = NULL;
    struct curl_slist *slist = NULL;
    curl_mime *mime;
    curl_mime *alt;
    curl_mimepart *part;
    char **cpp;

    if(!cad_emp_strc.email || !strlen(cad_emp_strc.email)){
      popup(NULL,"Não há email cadastrado para envio de emails");
      return 1;
    }

    if(!cad_emp_strc.email_senha || !strlen(cad_emp_strc.email_senha)){
      popup(NULL,"Não há senha cadastrado para o envio de emails");
      return 1;
    }

    curl_easy_setopt(curl, CURLOPT_USERNAME, cad_emp_strc.email);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, cad_emp_strc.email_senha);
    curl_easy_setopt(curl, CURLOPT_URL, cad_emp_strc.url_smtp);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_CAINFO, MOZ_CERT);

    curl_easy_setopt(curl, CURLOPT_MAIL_FROM,  cad_emp_strc.email);

    recipients = curl_slist_append(recipients, email_cli);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    if(strcmp(email_copia,SEM_EMAIL)){
      recipients = curl_slist_append(recipients, email_copia);//copia
      curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    }

    //curl_easy_setopt(curl, CURLOPT_MAIL_RCPT_ALLLOWFAILS, 1L);

    for(cpp = headers_text; *cpp; cpp++)
      headers = curl_slist_append(headers, *cpp);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    mime = curl_mime_init(curl);

    alt = curl_mime_init(curl);

    part = curl_mime_addpart(alt);
    curl_mime_data(part, inline_text, CURL_ZERO_TERMINATED);

    part = curl_mime_addpart(mime);
    curl_mime_subparts(part, alt);
    curl_mime_type(part, "multipart/alternative");
    slist = curl_slist_append(NULL, "Content-Disposition: inline");
    curl_mime_headers(part, slist, 1);

    part = curl_mime_addpart(mime);
    curl_mime_filedata(part, arquivo_orcamento);
    curl_mime_type(part, "pdf");
    curl_mime_encoder(part, "base64");
    curl_mime_name(part,cad_emp_strc.xNome);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

    res = curl_easy_perform(curl);

    if(res != CURLE_OK){
      file_logger("Erro no envio do email\n");
      if(nome_destino)
        file_logger(nome_destino);

      if(email_destino)
        file_logger(email_destino);

      if(email_copia)
        file_logger(email_copia);

      if(email_copia)
        file_logger(arquivo_orcamento);

      if(inline_text)
        file_logger(inline_text);

      file_logger(cad_emp_strc.email);
      file_logger(cad_emp_strc.email_senha);

      sprintf(mensagem, "Envio do email falhou: %s\n",curl_easy_strerror(res));
      popup(NULL,mensagem);
    }
    curl_slist_free_all(recipients);
    curl_slist_free_all(headers);

    curl_easy_cleanup(curl);

    curl_mime_free(mime);
  }
  enviando_email=0;
  return (int)res;
}


int enviar_email_suporte( char *arquivo_suporte ){

  CURL *curl;
  CURLcode res = CURLE_OK;
  char *corpo_email;
  char **headers_text;
  char mensagem[1000];
  char sup_email[] = "jovictor210@gmail.com";
  GDateTime *data = g_date_time_new_now(g_time_zone_new(NULL));
  enviando_email=1;
  headers_text = malloc(1200);
  headers_text[0] = malloc(300);
  sprintf(headers_text[0],"Date: %s",g_date_time_format(data,"%T"));
  headers_text[1] = malloc(300);
  sprintf(headers_text[1],"Subject: Suporte %s",cad_emp_strc.xNome);
  headers_text[2] = NULL;

    curl = curl_easy_init();
    if(curl_global_init(CURL_GLOBAL_ALL)){
      popup(NULL,"Não foi iniciar criar conexão");
      return 1;
    }
    if(curl) {
      struct curl_slist *headers = NULL;
      struct curl_slist *recipients = NULL;
      struct curl_slist *slist = NULL;
      curl_mime *mime;
      curl_mime *alt;
      curl_mimepart *part;
      char **cpp;

      if(!strlen(cad_emp_strc.email)){
        popup(NULL,"Não há email cadastrado para envio de emails");
        return 1;
      }

      if(!strlen(cad_emp_strc.email_senha)){
        popup(NULL,"Não há senha cadastrado para o envio de emails");
        return 1;
      }

      curl_easy_setopt(curl, CURLOPT_USERNAME, cad_emp_strc.email);
      curl_easy_setopt(curl, CURLOPT_PASSWORD, cad_emp_strc.email_senha);
      curl_easy_setopt(curl, CURLOPT_URL,  cad_emp_strc.url_smtp);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
      curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
      curl_easy_setopt(curl, CURLOPT_CAINFO, MOZ_CERT);

      curl_easy_setopt(curl, CURLOPT_MAIL_FROM,  cad_emp_strc.email);

      recipients = curl_slist_append(recipients, sup_email);
      curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

      //curl_easy_setopt(curl, CURLOPT_MAIL_RCPT_ALLLOWFAILS, 1L);

      for(cpp = headers_text; *cpp; cpp++)
        headers = curl_slist_append(headers, *cpp);

      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

      mime = curl_mime_init(curl);

      alt = curl_mime_init(curl);

      part = curl_mime_addpart(mime);
      curl_mime_subparts(part, alt);
      curl_mime_type(part, "multipart/alternative");
      slist = curl_slist_append(NULL, "Content-Disposition: inline");
      curl_mime_headers(part, slist, 1);

      part = curl_mime_addpart(alt);
      curl_mime_data(part, "Segue arquivo xml com dados do suporte", CURL_ZERO_TERMINATED);

      part = curl_mime_addpart(mime);
      curl_mime_filedata(part, arquivo_suporte);
      curl_mime_type(part, "pdf");
      curl_mime_encoder(part, "base64");
      curl_mime_name(part,cad_emp_strc.xNome);
      curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

      res = curl_easy_perform(curl);
      curl_slist_free_all(recipients);
      curl_slist_free_all(headers);

      curl_easy_cleanup(curl);

      curl_mime_free(mime);

      if(res != CURLE_OK){
        sprintf(mensagem, "Envio do email falhou: %s\n",curl_easy_strerror(res));
        popup(NULL,mensagem);
        return 1;
      }

    }
    enviando_email=0;
    popup(NULL,"O email foi enviado com sucesso");
    return 0;
}
