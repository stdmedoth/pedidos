int mkt_mail_alterar_fun(){
  mkt_email_alterando = 1;

  GtkTextIter inicio, fim;
  GtkTextBuffer *buffer;
  MYSQL_RES * res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];


  sprintf(query,"SELECT * FROM emails_model WHERE code = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if(!(row=mysql_fetch_row(res))){
    popup(NULL,"Modelo não existe");
    return 1;
  }
  gtk_entry_set_text(GTK_ENTRY(mkt_mail_nome_entry), row[EMAILMODEL_NOME_COL]);

  sprintf(query,"SELECT * FROM emails_header WHERE email_id = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if((row=mysql_fetch_row(res))){
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_header_view));
    gtk_text_buffer_set_text(buffer, row[EMLHEADER_CONTEUDO], strlen(row[EMLHEADER_CONTEUDO]));
  }


  sprintf(query,"SELECT * FROM emails_body WHERE email_id = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if((row=mysql_fetch_row(res))){
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_corpo_view));
    gtk_text_buffer_set_text(buffer, row[EMLBODY_CONTEUDO], strlen(row[EMLBODY_CONTEUDO]));
  }

  sprintf(query,"SELECT * FROM emails_footer WHERE email_id = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if((row=mysql_fetch_row(res))){
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_footer_view));
    gtk_text_buffer_set_text(buffer, row[EMLFOOTER_CONTEUDO], strlen(row[EMLFOOTER_CONTEUDO]));
  }
  gtk_button_set_label(GTK_BUTTON(mkt_mail_concluir_button),"Atualizar");

  return 0;
}
