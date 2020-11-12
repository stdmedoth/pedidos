int cotac_validade_fun(){
  gchar *cotac_validade_gchar2;
  if(!strlen(cotac_validade_gchar2 = (gchar*)gtk_entry_get_text(GTK_ENTRY(cotac_validade_entry)))){
    cotac_validade_gchar = formatar_data(cotac_validade_gchar2);
    gtk_entry_set_text(GTK_ENTRY(cotac_validade_entry),cotac_validade_gchar);
    return 0;
  }
  cotac_validade_gchar = formatar_data(cotac_validade_gchar2);
  if(!cotac_validade_gchar){
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(cotac_validade_entry),cotac_validade_gchar);
  int pos = contac_get_ult_pos();
  gtk_widget_grab_focus(cotac_prod_cod_entry[pos]);
  return 0;
}
