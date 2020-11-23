int mkt_mail_code_fun(){

  MYSQL_RES * res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  mkt_mail_code_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(mkt_mail_code_entry));
  if(!strlen(mkt_mail_code_gchar)){
    popup(NULL,"Insira o código do email");
    return 1;
  }

  sprintf(query,"SELECT * FROM emails_model WHERE code = %i", atoi(mkt_mail_code_gchar));
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar o modelo");
    return 1;
  }
  if((row=mysql_fetch_row(res))){
    if(!mkt_email_alterando && !mkt_email_concluindo && !mkt_email_visualizando){
      mkt_mail_alterar_fun();
      return 0;
    }
  }
  gtk_widget_grab_focus(mkt_mail_nome_entry);

  return 0;
}
