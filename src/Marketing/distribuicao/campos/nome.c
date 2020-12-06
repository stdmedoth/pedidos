int mkt_cad_distrib_nome_fun(){

  distrib_nome_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(distrib_nome_entry));
  if(!strlen(distrib_nome_gchar)){
    popup(NULL,"Insira o nome");
    return 1;
  }
  gtk_widget_grab_focus(distrib_pessoas_treeview);
  return 0;
}
