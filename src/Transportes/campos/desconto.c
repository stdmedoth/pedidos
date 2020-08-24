int trsp_cad_descfrt_fun(){
  char *formatar = malloc(MAX_PRECO_LEN);

  trsp_cad_descfrt_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(trsp_cad_descfrt_entry));

  if(critica_real(trsp_cad_descfrt_gchar,trsp_cad_descfrt_entry))
    return 1;

  gtk_widget_grab_focus(trsp_cad_concluir_button);
  return 0;
}
