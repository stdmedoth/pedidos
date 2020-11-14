int cotat_itens_prc_fun(GtkEntry *entry, int pos){

  if(cotac_get_participante())
    return 1;

  int cod = cotac_get_participante_index(atoi(cotac_partc_gchar));

  gchar *text = (gchar*)gtk_entry_get_text(entry);
  if(!text || !strlen(text)){
    popup(NULL,"Insira o valor do produto");
    return 1;
  }

  if(critica_real(text,GTK_WIDGET(entry)))
    return 1;

  cotacao_new->cotacao_itens[cod][pos].valor = atof(text);

  g_print("valor no spin %i : gchar %s - float %.2f\n", pos, text, cotacao_new->cotacao_itens[cod][pos].valor);

  if(cotac_ativo[cod][pos+1])
    gtk_widget_grab_focus(cotac_prod_cod_entry[cod][pos+1]);
  else
    gtk_widget_grab_focus(cotac_add_button[cod]);
  return 0;

}
