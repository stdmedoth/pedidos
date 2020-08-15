int cad_pag_code_fun(){

  cad_pag_code_gchar = (gchar*  )gtk_entry_get_text(GTK_ENTRY(cad_pag_code_entry));

  if(!strlen(cad_pag_code_gchar)){
    popup(NULL,"Insira o código do título");
    return 1;
  }

  gtk_widget_grab_focus(cad_pag_parcela_spin);
  return 0;
}
