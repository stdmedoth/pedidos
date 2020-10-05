int cad_conta_fixa_descr(){

  conta_fix_descr_gchar =(gchar*) gtk_entry_get_text(GTK_ENTRY(conta_fix_descr_entry));
  if(!conta_fix_descr_gchar || strlen(conta_fix_descr_gchar)<=0){
    popup(NULL,"Insira uma descrição");
    gtk_widget_grab_focus(conta_fix_descr_entry);
    return 1;
  }

  gtk_widget_grab_focus(conta_fix_forn_entry);

  return 0;
}
