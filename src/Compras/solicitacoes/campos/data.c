int req_prod_data_fun(){

  if(!strlen(req_prod_data_gchar = (gchar *)gtk_entry_get_text(GTK_ENTRY(req_prod_data_entry)))){
    gtk_entry_set_text(GTK_ENTRY(req_prod_data_entry),data_sys);
  }

  gchar *req_prod_data_gchar2 = strdup(req_prod_data_gchar);
  strcpy(req_prod_data_gchar2 , req_prod_data_gchar);
  if(!(req_prod_data_gchar = formatar_data(req_prod_data_gchar2))){
    return 1;
  }

  gtk_widget_grab_focus(req_prod_concluir_button);
  return 0;
}
