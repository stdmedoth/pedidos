int cad_rec_code_fun(){

  cad_rec_code_gchar = (gchar*  )gtk_entry_get_text(GTK_ENTRY(cad_rec_code_entry));

  if(!strlen(cad_rec_code_gchar)){
    popup(NULL,"Insira o código do título");
    return 1;
  }

  gtk_widget_grab_focus(cad_rec_parcela_spin);
  return 0;
}
