int ordem_cmp_dtentrega_fun(){
  ordem_cmp_dtentrega_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(ordem_cmp_dtentrega_entry));
  if(!strlen(ordem_cmp_dtentrega_gchar)){
    ordem_cmp_dtentrega_gchar = strdup("");
  }
  gchar *ordem_cmp_dtentrega_gchar2 = strdup(ordem_cmp_dtentrega_gchar);
  gchar *formated = formatar_data(ordem_cmp_dtentrega_gchar2);
  if(!formated){
    return 1;
  }
  gtk_entry_set_text(GTK_ENTRY(ordem_cmp_dtentrega_entry), formated);
  strcpy(ordem_cmp_dtentrega_gchar, formated);

  gtk_widget_grab_focus(ordem_cmp_condpag_entry);
  return 0;
}
