int trsp_cad_vlrfrt_fun(){
  char *formatar = malloc(MAX_PRECO_LEN);
  trsp_cad_vlrfrt_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(trsp_cad_vlrfrt_entry));

  if(critica_real(trsp_cad_vlrfrt_gchar,trsp_cad_vlrfrt_entry))
    return 1;

  gtk_widget_grab_focus(trsp_cad_descfrt_entry);
  return 0;
}
