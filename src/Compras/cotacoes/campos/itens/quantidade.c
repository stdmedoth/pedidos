int cotat_itens_qnt_fun(GtkEntry *entry, int pos){

  if(cotac_get_participante())
    return 1;

  int cod = cotac_get_participante_index(atoi(cotac_partc_gchar));

  gchar *text = (gchar*)gtk_entry_get_text(entry);

  if(!text || !strlen(text)){
    popup(NULL,"Insira a quantidade do produto");
    return 1;
  }

  if(critica_real(text,GTK_WIDGET(entry)))
    return 1;

  cotacao_new->cotacao_itens[cod][pos].quantidade = atof(text);

  gtk_widget_grab_focus(cotac_prod_prc_entry[cod][pos]);

  return 0;
}
