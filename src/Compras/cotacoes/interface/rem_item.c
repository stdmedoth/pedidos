int cotac_rem_item(GtkWidget *widget, int pos){

  if(cotac_get_participante())
    return 1;

  int cod = atoi(cotac_partc_gchar);

  g_print("Removendo %i\n",pos);
  int qnt = cotac_get_itens_qnt(cod);
  if(qnt<=1)
    return 1;
  if(cotac_ativo[pos]){
    cotac_ativo[pos] = 0;
    gtk_widget_destroy(cotac_prod_frames[cod][pos]);
    g_print("Removido %i\n",pos);
  }

  return 1;
}
