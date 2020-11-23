int mkt_mail_nome_fun(){
  mkt_mail_nome_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(mkt_mail_nome_entry));
  if(!strlen(mkt_mail_nome_gchar)){
    popup(NULL,"Insira um nome para o email");
    return 1;
  }
  gtk_widget_grab_focus(mkt_mail_tipo_combo);
  return 0;
}
