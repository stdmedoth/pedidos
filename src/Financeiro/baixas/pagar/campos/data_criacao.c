int cad_bxs_pag_dtc_fun(){

  cad_bxs_pag_datacriacao_gchar = (gchar* ) gtk_entry_get_text(GTK_ENTRY(cad_bxs_pag_datacriacao_entry));

  if(!strlen(cad_bxs_pag_datacriacao_gchar)){
    cad_bxs_pag_datacriacao_gchar = malloc(strlen(data_sys)+1);
    strcpy(cad_bxs_pag_datacriacao_gchar,data_sys);
    gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_datacriacao_entry),cad_bxs_pag_datacriacao_gchar);
  }

  if(!(cad_bxs_pag_datacriacao_gchar = formatar_data(cad_bxs_pag_datacriacao_gchar)))
    return 1;

  gtk_entry_set_text(GTK_ENTRY(cad_bxs_pag_datacriacao_entry),cad_bxs_pag_datacriacao_gchar);

  pag_baixas.data = malloc(strlen(cad_bxs_pag_datacriacao_gchar));
  strcpy(pag_baixas.data,cad_bxs_pag_datacriacao_gchar);

  gtk_widget_grab_focus(cad_bxs_pag_valor_entry);
  return 0;
}
