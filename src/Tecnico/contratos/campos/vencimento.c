int cntrats_vencimento_fun(){

  tracelogger_set_func_name("cntrats_vencimento_fun");
  cntrats_vencimento_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(cntrats_vencimento_entry));
  if(!strlen(cntrats_vencimento_gchar)){
    cntrats_vencimento_gchar = strdup("");
  }

  gchar *cntrats_vencimento_gchar2 = formatar_data(cntrats_vencimento_gchar);
  if(!cntrats_vencimento_gchar2)
    return 1;

  cntrats_vencimento_gchar = strdup(cntrats_vencimento_gchar2);
  gtk_entry_set_text(GTK_ENTRY(cntrats_vencimento_entry), cntrats_vencimento_gchar2);

  gtk_widget_grab_focus(cntrats_concluir_button);
  return 0;
}
