int enviar_email_orcamento(char *nome_destino,char *email_destino, char *arquivo_orcamento){
  CURL *curl;
  CURLcode res = CURLE_OK;

  char inline_text[1000];
  sprintf(inline_text,"<h1>Olá! ' %s '</h1>\r\n"
  "<p>Segue pedido impresso referente aos produtos comprados na ' %s '.</p>\r\n"
  "<p>Caso haja alguma dúvida, ligar em ' %s '.</p>\r\n",nome_destino,cad_emp_strc.xNome,cad_emp_strc.telefone);

  GDateTime *data = g_date_time_new_now(g_time_zone_new(NULL));
  char mensagem[1000];
  char **headers_text;

  if(strlen(email_destino)<=0){
    popup(NULL,"Não há email para o cliente");
    return 1;
  }

  if(!fopen(arquivo_orcamento,"r")){
    popup(NULL,"Pedido não foi gerado impresso");
    return 1;
  }


  headers_text = malloc(1200);
  headers_text[0] = malloc(300);
  sprintf(headers_text[0],"Date: %s",g_date_time_format(data,"%T"));
  headers_text[1] = malloc(300);
  sprintf(headers_text[1],"To: %s",email_destino);
  headers_text[2] = malloc(300);
  sprintf(headers_text[2],"To: %s",email_destino);
  headers_text[3] = malloc(300);
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

    strcpy(cad_emp_strc.email_senha,"987817853bash");

    /* This is the URL for your mailserver */
    curl_easy_setopt(curl, CURLOPT_USERNAME, cad_emp_strc.email);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, cad_emp_strc.email_senha);
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
    //curl_easy_setopt(curl, CURLOPT_CAINFO, "google.pem");


    /* Note that this option isn't strictly required, omitting it will result
     * in libcurl sending the MAIL FROM command with empty sender data. All
     * autoresponses should have an empty reverse-path, and should be directed
     * to the address in the reverse-path which triggered them. Otherwise,
     * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
     * details.
     */
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM,  cad_emp_strc.email);

    /* Add two recipients, in this particular case they correspond to the
     * To: and Cc: addressees in the header, but they could be any kind of
     * recipient. */
    recipients = curl_slist_append(recipients, email_destino);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    /* Build and set the message header list. */
    for(cpp = headers_text; *cpp; cpp++)
      headers = curl_slist_append(headers, *cpp);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    /* Build the mime message. */
    mime = curl_mime_init(curl);

    /* The inline part is an alternative proposing the html and the text
       versions of the e-mail. */
    alt = curl_mime_init(curl);

    /* HTML message. */
    part = curl_mime_addpart(alt);
    curl_mime_data(part, inline_text, CURL_ZERO_TERMINATED);
    curl_mime_type(part, "text/html");

    /* Create the inline part. */
    part = curl_mime_addpart(mime);
    curl_mime_subparts(part, alt);
    curl_mime_type(part, "multipart/alternative");
    slist = curl_slist_append(NULL, "Content-Disposition: inline");
    curl_mime_headers(part, slist, 1);

    /* Add the current source program as an attachment. */
    part = curl_mime_addpart(mime);
    curl_mime_filedata(part, arquivo_orcamento);
    curl_mime_type(part, "pdf");
    curl_mime_encoder(part, "base64");
    curl_mime_name(part,cad_emp_strc.xNome);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

    /* Send the message */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK){
      file_logger("Erro no envio do email\n");
      file_logger(nome_destino);
      file_logger(email_destino);
      file_logger(arquivo_orcamento);
      file_logger(cad_emp_strc.email);
      file_logger(cad_emp_strc.email_senha);

      sprintf(mensagem, "Envio do email falhou: %s\n",curl_easy_strerror(res));
      popup(NULL,mensagem);
    }
    /* Free lists. */
    curl_slist_free_all(recipients);
    curl_slist_free_all(headers);

    /* curl won't send the QUIT command until you call cleanup, so you should
     * be able to re-use this connection for additional messages (setting
     * CURLOPT_MAIL_FROM and CURLOPT_MAIL_RCPT as required, and calling
     * curl_easy_perform() again. It may not be a good idea to keep the
     * connection open for a very long time though (more than a few minutes
     * may result in the server timing out the connection), and you do want to
     * clean up in the end.
     */
    curl_easy_cleanup(curl);

    /* Free multipart message. */
    curl_mime_free(mime);
  }

  return (int)res;
}
