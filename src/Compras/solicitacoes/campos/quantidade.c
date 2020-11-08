int req_prod_qnt_fun(){
  if(!strlen(req_prod_qnt_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(req_prod_qnt_spin)))){
    popup(NULL,"Insira a quantidade");
    return 1;
  }
  gtk_widget_grab_focus(req_prod_data_entry);
  return 0;
}
