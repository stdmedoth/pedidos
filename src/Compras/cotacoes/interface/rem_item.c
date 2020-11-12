int cotac_rem_item(GtkWidget *widget, int pos){

  g_print("Removendo %i\n",pos);
  int qnt = cotac_get_itens_qnt();
  if(qnt<=1)
    return 1;
  if(cotac_ativo[pos]){
    cotac_ativo[pos] = 0;
    gtk_widget_destroy(cotac_prod_frames[pos]);
    g_print("Removido %i\n",pos);
  }

  return 1;
}
