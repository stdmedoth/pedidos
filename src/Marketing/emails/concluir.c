int mkt_mail_concluir_fun(){

  int email_len=0;
  char *query;
  mkt_email_concluindo = 1;

  if(mkt_mail_code_fun())
    return 1;

  if(mkt_mail_nome_fun())
    return 1;

  if(mkt_mail_tipo_fun())
    return 1;

  if(mkt_mail_setor_fun())
    return 1;

  if(mkt_mail_header_fun())
    return 1;

  if(mkt_mail_body_fun())
    return 1;

  if(mkt_mail_footer_fun())
    return 1;

  while (g_main_context_pending(NULL))
    g_main_context_iteration(NULL,FALSE);


  if(!mkt_mail_header_gchar || !strlen(mkt_mail_header_gchar))
    mkt_mail_header_gchar = strdup("<header></header>");

  if(!mkt_mail_body_gchar || !strlen(mkt_mail_body_gchar))
    mkt_mail_body_gchar = strdup("<body></body>");

  if(!mkt_mail_footer_gchar || !strlen(mkt_mail_footer_gchar))
    mkt_mail_footer_gchar = strdup("<footer></footer>");

  MYSQL_RES *res;
  MYSQL_ROW row;
  query = malloc(MAX_QUERY_LEN);
  sprintf(query,"SELECT * FROM  emails_model WHERE code =  %i",atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível pesquisar existencia do modelo");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){

    sprintf(query,"INSERT INTO emails_model(code, nome, tipo, setor) values (%i, '%s', %i, %i)",atoi(mkt_mail_code_gchar), mkt_mail_nome_gchar, mkt_mail_tipo_int, mkt_mail_setor_int);

    if(enviar_query(query)){
      popup(NULL,"Não foi possível  cadastrar modelo");
      return 1;
    }

    char *unvulned_query = malloc(strlen(mkt_mail_header_gchar) * 2);
    mysql_real_escape_string(&conectar, unvulned_query, mkt_mail_header_gchar, strlen(mkt_mail_header_gchar));
    free(query);
    query = malloc(MAX_QUERY_LEN + strlen(unvulned_query));
    sprintf(query,"INSERT INTO emails_header(conteudo, email_id) values ( '%s', %i)",unvulned_query, atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível inserir heeader");
      return 1;
    }

    free(unvulned_query);
    unvulned_query = malloc(strlen(mkt_mail_body_gchar) * 2);
    mysql_real_escape_string(&conectar, unvulned_query, mkt_mail_body_gchar, strlen(mkt_mail_body_gchar));
    free(query);

    query = malloc(MAX_QUERY_LEN + strlen(unvulned_query));
    sprintf(query,"INSERT INTO emails_body( conteudo, email_id) values ( '%s', %i)",unvulned_query, atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível  cadastrar modelo");
      return 1;
    }

    free(unvulned_query);
    unvulned_query = malloc(strlen(mkt_mail_footer_gchar) * 2);
    mysql_real_escape_string(&conectar, unvulned_query, mkt_mail_body_gchar, strlen(mkt_mail_footer_gchar));
    free(query);
    query = malloc(MAX_QUERY_LEN + strlen(unvulned_query));
    sprintf(query,"INSERT INTO emails_footer( conteudo, email_id) values ( '%s', %i)",unvulned_query, atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível  cadastrar modelo");
      return 1;
    }

  }else{
    sprintf(query,"UPDATE emails_model set nome = '%s', tipo = %i, setor = %i where code = %i",mkt_mail_nome_gchar, mkt_mail_tipo_int, mkt_mail_setor_int, atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível atualizar modelo");
      return 1;
    }

    char *unvulned_query = malloc(strlen(mkt_mail_header_gchar) * 2);
    mysql_real_escape_string(&conectar, unvulned_query, mkt_mail_header_gchar, strlen(mkt_mail_header_gchar));
    free(query);
    query = malloc(MAX_QUERY_LEN + strlen(unvulned_query));
    sprintf(query,"UPDATE emails_header set conteudo = '%s' where email_id = %i", unvulned_query, atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível atualizar header");
      return 1;
    }

    free(unvulned_query);
    unvulned_query = malloc(strlen(mkt_mail_body_gchar) * 2);
    mysql_real_escape_string(&conectar, unvulned_query, mkt_mail_body_gchar, strlen(mkt_mail_body_gchar));
    free(query);
    query = malloc(MAX_QUERY_LEN + strlen(unvulned_query));
    sprintf(query,"UPDATE emails_body set conteudo = '%s' where email_id = %i", unvulned_query, atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível atualizar corpo");
      return 1;
    }
    free(unvulned_query);
    unvulned_query = malloc( strlen(mkt_mail_footer_gchar) * 2);
    mysql_real_escape_string(&conectar, unvulned_query, mkt_mail_footer_gchar, strlen(mkt_mail_footer_gchar));
    free(query);
    query = malloc(MAX_QUERY_LEN + strlen(unvulned_query));
    sprintf(query,"UPDATE emails_footer set conteudo = '%s' where email_id = %i", unvulned_query, atoi(mkt_mail_code_gchar));
    if(enviar_query(query)){
      popup(NULL,"Não foi possível atualizar footer");
      return 1;
    }

  }

  if(!mkt_email_alterando)
    popup(NULL,"Modelo cadastrado com sucesso");
  else
    popup(NULL,"Modelo atualizado com sucesso");

  return 0;
}
