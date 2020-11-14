int cotac_validade_fun(){
  gchar *cotac_validade_gchar2;

  cotac_validade_gchar2 = (gchar*)gtk_entry_get_text(GTK_ENTRY(cotac_validade_entry));
  if(!strlen(cotac_validade_gchar2)){

    cotac_validade_gchar2 = strdup("");
    cotac_validade_gchar = formatar_data(cotac_validade_gchar2);
    if(!cotac_validade_gchar)
      return 1;

    cotacao_new->validade = strdup(cotac_validade_gchar);
    gtk_entry_set_text(GTK_ENTRY(cotac_validade_entry),cotac_validade_gchar);
    return 0;
  }

  cotac_validade_gchar = formatar_data(cotac_validade_gchar2);
  if(!cotac_validade_gchar)
    return 1;

  cotacao_new->validade = strdup(cotac_validade_gchar);
  gtk_entry_set_text(GTK_ENTRY(cotac_validade_entry),cotac_validade_gchar);

  gtk_widget_grab_focus(cotac_partc_combo);
  return 0;
}
