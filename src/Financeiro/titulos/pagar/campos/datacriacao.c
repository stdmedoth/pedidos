int cad_pag_datacriacao_fun(){
  cad_pag_datacriacao_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_pag_datacriacao_entry));

  if(!strlen(cad_pag_datacriacao_gchar)){
    popup(NULL,"Insira a data de criação");
    return 1;
  }
  gtk_widget_grab_focus(cad_pag_datavencimento_entry);


  return 0;
}
