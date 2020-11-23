int pdv_psq_item_fun(){

  gtk_label_set_text(GTK_LABEL(pdv_acaoatual_label), "Pesquisando Item");

  gchar *value = (gchar*)gtk_entry_get_text(GTK_ENTRY(pdv_codprod_entry));
  pdv_prod_antes_psq = strdup(value);
  gchar *formulacao = malloc(strlen(pdv_prod_antes_psq));
  sprintf(formulacao, "%s",pdv_prod_antes_psq);
  gtk_label_set_text(GTK_LABEL(pdv_prodcod_label), formulacao);
  pdv_venda_atual->operacao_atual = PDV_PSQ_ITEM_OPER;
  if(!psq_prod( NULL , GTK_ENTRY(pdv_codprod_entry))){
    return 1;
  }

  return 0;
}
