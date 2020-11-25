int cotac_rem_item(GtkWidget *widget, int pos){

  char query[MAX_QUERY_LEN];

  if(cotac_get_participante())
    return 1;

  int cod = cotac_get_participante_index(atoi(cotac_partc_gchar));

  g_print("Removendo %i\n",pos);
  int qnt = cotac_get_itens_qnt(cod);
  if(!qnt)
    return 1;

  if(cotac_ativo[cod][pos]){
    sprintf(query,"delete from itens_cotacoes where cotacoes_id = %i and item_index = %i",
    cotacao_new->code,
    pos);
    if(enviar_query(query)){
      popup(NULL,"Não foi possivel atualizar cotação");
      return 1;
    }
    cotac_ativo[cod][pos] = 0;
    cotac_produto_inserido[cod][pos] = 0;
    gtk_widget_destroy(cotac_prod_frames[cod][pos]);
    g_print("Removido %i\n",pos);
  }

  return 1;
}
