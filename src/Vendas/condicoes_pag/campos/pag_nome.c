int pag_nome_fun(){
  pag_nome_gchar = (gchar *) gtk_entry_get_text(GTK_ENTRY(pag_nome_entry));
  if(strlen(pag_nome_gchar)<=0){
    popup(NULL,"Insira o nome da condição");
    gtk_widget_grab_focus(pag_nome_entry);
    return 1;
  }

  gtk_widget_grab_focus(pag_init_spin);
  return 0;
}
