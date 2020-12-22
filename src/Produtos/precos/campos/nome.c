int prod_precos_nome_fun(){

  prod_prc_nome_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(prod_prc_nome_entry));

  if(strlen(prod_prc_nome_gchar)>=20){
    popup(NULL,"Nome muito grande");
    return 1;
  }
  if(!strlen(prod_prc_nome_gchar)){
    popup(NULL,"Inserir nome");
    return 1;
  }

  gtk_widget_grab_focus(prod_prc_prodcode_entry);
  return 0;
}
