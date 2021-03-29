int ordem_cmp_gerar(){

  if(ordem_cmp_code_fun())
    return 1;

  gchar *codebackup = strdup(ordem_cmp_code_gchar);
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  sprintf(query, "select * from ordens_compra where code = %s",ordem_cmp_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar existencia da cotação");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    if(!ordem_cmp_concluir_fun()){
      gtk_entry_set_text(GTK_ENTRY(ordem_cmp_code_entry), codebackup);
      gtk_widget_activate(ordem_cmp_code_entry);
    }
  }

  struct _ord_cmp *ordem = ordem_cmp_get(atoi(ordem_cmp_code_gchar));
  if(!ordem){
    popup(NULL,"Não foi possível receber informações da ordem");
    return 1;
  }

  if(gera_doc_ordcmp(ordem)){
    popup(NULL,"Erro ao gerar ordem de compra");
    return 1;
  }

  if(ordem->status == ORDCMP_N_GERADO){
    sprintf(query, "update ordens_compra set status = %i where code = %s",
      ORDCMP_N_ENVIADO,
      ordem_cmp_code_gchar);

    if(enviar_query(query)){
      popup(NULL,"Não foi atualizar status da ordem de compra");
      return 1;
    }
  }

  imp_opc = PDF_IMP;
  if(iniciar_impressao(ORD_CMP_PDF_FILE))
    return 1;

  popup(NULL,"Ordem de compra gerada com sucesso");
  return 0;
}
