int cotat_itens_qnt_fun(GtkEntry *entry, int pos){
  gchar *text = (gchar*)gtk_entry_get_text(entry);
  if(!strlen(text)){
    popup(NULL,"Insira a quantidade do produto");
    return 1;
  }

  gtk_widget_grab_focus(cotac_prod_prc_entry[pos]);

  return 0;
}
