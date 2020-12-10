int mkt_cad_distrib_concluir_fun(){
  enum{
    ID,
    NOME,
    EMAIL,
    CELULAR,
    TELEFONE,
    N_COLS
  };
  mkt_cad_distrib_concluindo = 1;

  GtkTreeIter iter;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[ MAX_QUERY_LEN ];

  GtkTreeStore *model = (GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(distrib_pessoas_treeview));
  if(!model){
    popup(NULL,"TreeView sem modelo");
    return 1;
  }
  if(!gtk_tree_model_iter_children(GTK_TREE_MODEL(model), &iter, NULL)){
    popup(NULL,"Sem contatos a salvar");
    return 1;
  }

  if(mkt_cad_distrib_code_fun())
    return 1;

  if(mkt_cad_distrib_nome_fun())
    return 1;

  sprintf(query, "select * from distribuicoes where code = %s", distrib_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar existencia da distribuicao");
    return 1;
  }
  if(!(mysql_num_rows(res))){
    sprintf(query, "insert into distribuicoes(code, nome) values(%s, '%s')", distrib_code_gchar, distrib_nome_gchar);
    if(enviar_query(query)){
      popup(NULL,"Não foi possível criar distribuição");
      return 1;
    }
  }else{
    sprintf(query, "update distribuicoes set nome = '%s' where code = %s", distrib_nome_gchar, distrib_code_gchar);
    if(enviar_query(query)){
      popup(NULL,"Não foi possível atualizar distribuição");
      return 1;
    }
  }

  for(int cont=0;cont<MAX_MAILDISTRIB_CONTTS;cont++){
    if(mkt_cad_distrib_removidos[cont]){
      sprintf(query, "delete from PessoasDistribuicao where distribuicao = %s and pessoa = %i", distrib_code_gchar, mkt_cad_distrib_removidos[cont]);
      if((enviar_query(query))){
        popup(NULL,"Erro ao excluir contato");
        return 1;
      }
    }
  }

  char *id = malloc(MAX_CODE_LEN);
  while((1)){
    gtk_tree_model_get (GTK_TREE_MODEL(model), &iter,
      ID, &id, -1);

    sprintf(query, "select * from PessoasDistribuicao where distribuicao = %s and pessoa = %s", distrib_code_gchar, id);
    if(!(res = consultar(query))){
      popup(NULL,"Erro ao consultar existencia de contato na distribuição");
      return 1;
    }

    if(!(row = mysql_fetch_row(res))){
      sprintf(query, "insert into PessoasDistribuicao(distribuicao, pessoa) values(%s, %s)", distrib_code_gchar, id);
      if(enviar_query(query)){
        popup(NULL,"Não foi possível inserir contato na distribuiçãoo");
        return 1;
      }
    }

    if(!gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &iter))
      break;
  }
  popup(NULL,"Criado com sucesso");
  mkt_cad_distrib_cancelar_fun();
  return 0;
}
