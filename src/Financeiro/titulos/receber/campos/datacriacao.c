int cad_rec_datacriacao_fun(){
  cad_rec_datacriacao_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_rec_datacriacao_entry));

  if(!strlen(cad_rec_datacriacao_gchar)){
    popup(NULL,"Insira a data de criação");
    return 1;
  }
  gtk_widget_grab_focus(cad_rec_datavencimento_entry);


  return 0;
}
