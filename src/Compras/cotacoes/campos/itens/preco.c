int cotat_itens_prc_fun(GtkEntry *entry, int pos){
  gchar *text = (gchar*)gtk_entry_get_text(entry);
  if(!strlen(text)){
    popup(NULL,"Insira o valor do produto");
    return 1;
  }

  if(cotac_ativo[pos+1])
    gtk_widget_grab_focus(cotac_prod_cod_entry[pos+1]);
  else
    gtk_widget_grab_focus(cotac_add_button);
  return 0;
}
