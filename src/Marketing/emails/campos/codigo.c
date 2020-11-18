int mkt_email_code_fun(){
  mkt_mail_code_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(mkt_mail_code_entry));
  if(!strlen(mkt_mail_code_gchar)){
    popup(NULL,"Insira o código do email");
    return 1;
  }
  return 0;
}
