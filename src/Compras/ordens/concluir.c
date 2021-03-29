int ordem_cmp_concluir_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;
  enum {
    ID_COLUMN,
    PROD_NOME_COLUMN,
    PROD_QNT_COLUMN,
    PROD_VLR_COLUMN,
    N_COLUMNS
  };

  ordem_cmp_concluindo = 1;

  if(ordem_cmp_code_fun()){
    return 1;
  }
  if(ordem_cmp_fornecedor_fun()){
    return 1;
  }
  if(ordem_cmp_dtemissao_fun()){
    return 1;
  }
  if(ordem_cmp_dtentrega_fun()){
    return 1;
  }
  if(ordem_cmp_condpag_fun()){
    return 1;
  }
  if(ordem_cmp_status_fun()){
    return 1;
  }

  sprintf(query, "select * from ordens_compra where code = %s",ordem_cmp_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar existencia da cotação");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    sprintf(query, "insert into ordens_compra(code, fornecedor, dtemissao, dtentrega, condpag, status) values( %s, %s, STR_TO_DATE('%s','%%d/%%m/%%Y'), STR_TO_DATE('%s','%%d/%%m/%%Y'), %s ,%i)",
      ordem_cmp_code_gchar,
      ordem_cmp_forncode_gchar,
      ordem_cmp_dtemissao_gchar,
      ordem_cmp_dtentrega_gchar,
      ordem_cmp_condpag_gchar,
      ordem_cmp_status_int);
  }else{
    sprintf(query, "update ordens_compra set fornecedor = %s, dtemissao = STR_TO_DATE('%s','%%d/%%m/%%Y'), dtentrega = STR_TO_DATE('%s','%%d/%%m/%%Y'), condpag = %s, status = %i where code = %s",
      ordem_cmp_forncode_gchar,
      ordem_cmp_dtemissao_gchar,
      ordem_cmp_dtentrega_gchar,
      ordem_cmp_condpag_gchar,
      ordem_cmp_status_int,
      ordem_cmp_code_gchar);
  }
  if(enviar_query(query)){
    popup(NULL,"Não foi possível criar ordem de compra");
    return 1;
  }

  GtkTreeIter iter;
  gchar *id = malloc(12);
  GtkTreeStore *model = (GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(ordem_cmp_ordreq_treeview));
  if(!model){
    popup(NULL,"TreeView sem modelo");
    return 1;
  }
  if(!gtk_tree_model_iter_children(GTK_TREE_MODEL(model), &iter, NULL)){
    popup(NULL,"Sem materiais a comprar");
    return 1;
  }

  for(int cont=0;cont<ordem_cmp_excluido_pos;cont++){
    if(ordem_cmp_excluidos[cont]){
      sprintf(query, "delete from itens_ordens_compra where ordem_id = %s and itens_cotacao = %i", ordem_cmp_code_gchar, ordem_cmp_excluidos[cont]);
      if(enviar_query(query)){
        popup(NULL,"Não foi possível excluir item");
        return 1;
      }
    }
  }

  while((1)){
    gtk_tree_model_get (GTK_TREE_MODEL(model), &iter,
      ID_COLUMN, &id, -1);

    sprintf(query, "select * from itens_ordens_compra where ordem_id = %s and itens_cotacao = %s", ordem_cmp_code_gchar, id);
    if(!(res = consultar(query))){
      popup(NULL,"Erro ao consultar existencia do item na cotação");
      return 1;
    }

    if(!(row = mysql_fetch_row(res))){
      sprintf(query, "insert into itens_ordens_compra(ordem_id, itens_cotacao) values(%s, %s)", ordem_cmp_code_gchar, id);
      if(enviar_query(query)){
        popup(NULL,"Não foi possível inserir item na ordem de compra");
        return 1;
      }
    }

    if(!gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &iter))
      break;
  }

  popup(NULL, "Ordem de compra criada com sucesso");
  ordem_cmp_cancelar_fun();
  return 0;
}
