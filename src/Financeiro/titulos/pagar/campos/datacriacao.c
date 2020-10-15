int cad_pag_datacriacao_fun(){
  char *formatado;
  cad_pag_datacriacao_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_pag_datacriacao_entry));

  if(!(formatado = formatar_data(cad_pag_datacriacao_gchar))){
    gtk_widget_grab_focus(cad_pag_datacriacao_entry);
    return 1;
  }
  gtk_entry_set_text(GTK_ENTRY(cad_pag_datacriacao_entry),formatado);

  gtk_widget_grab_focus(cad_pag_datavencimento_entry);


  return 0;
}
