int cotac_data_fun(){
  gchar *cotac_data_gchar2;

  if(!strlen(cotac_data_gchar2 = (gchar*)gtk_entry_get_text(GTK_ENTRY(cotac_data_entry)))){

    cotac_data_gchar = formatar_data(cotac_data_gchar2);
    if(!cotac_data_gchar)
      return 1;

    cotacao_new->data = strdup(cotac_data_gchar);
    gtk_entry_set_text(GTK_ENTRY(cotac_data_entry),cotac_data_gchar);
    return 0;
  }

  cotac_data_gchar = formatar_data(cotac_data_gchar2);
  if(!cotac_data_gchar)
    return 1;

  cotacao_new->data = strdup(cotac_data_gchar);
  gtk_entry_set_text(GTK_ENTRY(cotac_data_entry),cotac_data_gchar);

  gtk_widget_grab_focus(cotac_validade_entry);
  return 0;
}
