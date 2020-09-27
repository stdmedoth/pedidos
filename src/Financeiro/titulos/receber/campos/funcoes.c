MYSQL_RES *titulos_get_pendentes(struct _titulo *titulos){
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos where status = %i",STAT_PENDENTE);
  if((titulos->result = consultar(query))){
    return NULL;
  }

  return titulos->result;
}

MYSQL_RES *titulos_get_baixados(struct _titulo *titulos){
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos where status = %i",STAT_QUITADO);
  if((titulos->result = consultar(query))){
    return NULL;
  }

  return titulos->result;
}

MYSQL_RES *titulos_get_todos(struct _titulo *titulos){
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos");
  if((titulos->result = consultar(query))){
    return NULL;
  }
  return titulos->result;
}

MYSQL_RES *titulos_por_cliente(struct _titulo *titulos){
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos where cliente = %i",titulos->cliente);
  if((titulos->result = consultar(query))){
    return NULL;
  }
  return titulos->result;
}

MYSQL_RES *titulos_por_cliente_status(struct _titulo *titulos){

  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos where cliente = %i",titulos->cliente);
  if((titulos->result = consultar(query))){
    return NULL;
  }
  return titulos->result;
}

GtkWidget *titulos_get_widget(struct _titulo *titulos){

  enum{
    TIT_CODE_COL,
    TIT_NOME_COL,
    TIT_PED_COL,
    TIT_POS_COL,
    TIT_BANC_COL,
    TIT_TIPO_COL,
    TIT_VLR_COL,
    TIT_CRIACAO_COL,
    TIT_VENCI_COL,
    TIT_BAIXA_COL,
    TIT_VLRBAIXA_COL,
    N_COLUMNS
  };

  GtkWidget *box_titulos = gtk_box_new(0,0);
  GtkWidget *scrollwnd = gtk_scrolled_window_new(NULL,NULL);
  GtkWidget *treeview = gtk_tree_view_new();
  titulos->treeview = GTK_TREE_VIEW(treeview);
  GtkTreeStore *modelo = gtk_tree_store_new(N_COLUMNS,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING
  );

  GtkTreeIter iter;
  char query[MAX_QUERY_LEN];

  GtkTreeViewColumn *col_code = gtk_tree_view_column_new_with_attributes("Título", gtk_cell_renderer_text_new(),"text", TIT_CODE_COL, NULL);
  GtkTreeViewColumn *col_nome = gtk_tree_view_column_new_with_attributes("Cliente", gtk_cell_renderer_text_new(),"text", TIT_NOME_COL, NULL);
  GtkTreeViewColumn *col_ped = gtk_tree_view_column_new_with_attributes("Pedido", gtk_cell_renderer_text_new(),"text", TIT_PED_COL, NULL);
  GtkTreeViewColumn *col_posicao = gtk_tree_view_column_new_with_attributes("Parcela", gtk_cell_renderer_text_new(),"text", TIT_POS_COL, NULL);
  GtkTreeViewColumn *col_banco = gtk_tree_view_column_new_with_attributes("Banco", gtk_cell_renderer_text_new(),"text", TIT_BANC_COL, NULL);
  GtkTreeViewColumn *col_tipo = gtk_tree_view_column_new_with_attributes("Tipo", gtk_cell_renderer_text_new(),"text", TIT_TIPO_COL, NULL);
  GtkTreeViewColumn *col_valor = gtk_tree_view_column_new_with_attributes("Valor", gtk_cell_renderer_text_new(),"text", TIT_VLR_COL, NULL);
  GtkTreeViewColumn *col_criacao = gtk_tree_view_column_new_with_attributes("Data Criação", gtk_cell_renderer_text_new(),"text", TIT_CRIACAO_COL, NULL);
  GtkTreeViewColumn *col_vencimento = gtk_tree_view_column_new_with_attributes("Data Vencimento", gtk_cell_renderer_text_new(),"text", TIT_VENCI_COL, NULL);
  GtkTreeViewColumn *col_baixa = gtk_tree_view_column_new_with_attributes("Data Baixa", gtk_cell_renderer_text_new(),"text", TIT_BAIXA_COL, NULL);
  GtkTreeViewColumn *col_vlrbaixa = gtk_tree_view_column_new_with_attributes("Vlr Baixado", gtk_cell_renderer_text_new(),"text", TIT_VLRBAIXA_COL, NULL);

  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_code,TIT_CODE_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_nome,TIT_NOME_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_ped,TIT_PED_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_posicao,TIT_POS_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_banco,TIT_BANC_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_tipo,TIT_TIPO_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_valor,TIT_VLR_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_criacao,TIT_CRIACAO_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_vencimento,TIT_VENCI_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_baixa,TIT_BAIXA_COL);
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_vlrbaixa,TIT_VLRBAIXA_COL);

  sprintf(query,"select tit.code, t.razao, tit.pedido, parc.posicao, bnc.nome,"
  " tit.tipo_titulo, parc.valor, parc.data_criacao, parc.data_vencimento"
  " from titulos as tit inner join parcelas_tab as parc inner join bancos as bnc inner join terceiros as t"
  " on tit.code = parc.parcelas_id and bnc.code = parc.banco and t.code = tit.cliente");

  if((titulos->result  = consultar(query))){
    while((titulos->row = mysql_fetch_row(titulos->result))){
      char baixas_query[MAX_QUERY_LEN];
      MYSQL_RES *res;
      MYSQL_ROW row;
      //consultar se há baixas para a parcela, caso não haja
      sprintf(baixas_query,"select data_criacao, valor from baixas_titulos where parcelas_id = %s and posicao = %s",
      titulos->row[TIT_CODE_COL],
      titulos->row[TIT_POS_COL]);
      int baixas_qnt=0;

      if((res = consultar(baixas_query))){
        while((row = mysql_fetch_row(res))){
          gtk_tree_store_append(modelo,&iter,NULL);
          gtk_tree_store_set(modelo,&iter,
            TIT_CODE_COL,titulos->row[TIT_CODE_COL],
            TIT_NOME_COL,titulos->row[TIT_NOME_COL],
            TIT_PED_COL,titulos->row[TIT_PED_COL],
            TIT_POS_COL,titulos->row[TIT_POS_COL],
            TIT_BANC_COL,titulos->row[TIT_BANC_COL],
            TIT_TIPO_COL,titulos->row[TIT_TIPO_COL],
            TIT_VLR_COL,titulos->row[TIT_VLR_COL],
            TIT_CRIACAO_COL,titulos->row[TIT_CRIACAO_COL],
            TIT_VENCI_COL,titulos->row[TIT_VENCI_COL],
            TIT_BAIXA_COL,row[0],
            TIT_VLRBAIXA_COL,row[1],
            -1
          );
          baixas_qnt++;
        }
      }

      if(!baixas_qnt){
        gtk_tree_store_append(modelo,&iter,NULL);
        gtk_tree_store_set(modelo,&iter,
          TIT_CODE_COL,titulos->row[TIT_CODE_COL],
          TIT_NOME_COL,titulos->row[TIT_NOME_COL],
          TIT_PED_COL,titulos->row[TIT_PED_COL],
          TIT_POS_COL,titulos->row[TIT_POS_COL],
          TIT_BANC_COL,titulos->row[TIT_BANC_COL],
          TIT_VLR_COL,titulos->row[TIT_VLR_COL],
          TIT_TIPO_COL,titulos->row[TIT_TIPO_COL],
          TIT_CRIACAO_COL,titulos->row[TIT_CRIACAO_COL],
          TIT_VENCI_COL,titulos->row[TIT_VENCI_COL],
          TIT_BAIXA_COL,"Não baixado",
          TIT_VLRBAIXA_COL,"Não baixado",
          -1
        );
      }
    }
  }

  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));
  gtk_container_add(GTK_CONTAINER(scrollwnd),treeview);
  gtk_widget_set_size_request(scrollwnd,600,300);
  gtk_box_pack_start(GTK_BOX(box_titulos),scrollwnd,0,0,0);
  gtk_widget_set_size_request(box_titulos,600,300);
  gtk_widget_show_all(box_titulos);
  return box_titulos;
}


int titulos_update_widget(struct _titulo *titulos){

  enum{
    TIT_CODE_COL,
    TIT_NOME_COL,
    TIT_PED_COL,
    TIT_POS_COL,
    TIT_BANC_COL,
    TIT_TIPO_COL,
    TIT_VLR_COL,
    TIT_CRIACAO_COL,
    TIT_VENCI_COL,
    TIT_BAIXA_COL,
    TIT_VLRBAIXA_COL,
    N_COLUMNS
  };

  GtkTreeStore *treestore	=	GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(titulos->treeview)));
  g_object_ref(G_OBJECT(treestore));
  gtk_tree_view_set_model(GTK_TREE_VIEW(titulos->treeview),NULL);
  gtk_tree_store_clear(treestore);
  gtk_tree_view_set_model(GTK_TREE_VIEW(titulos->treeview),GTK_TREE_MODEL(treestore));

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  GtkTreeIter iter;
  GtkTreeStore *modelo = (GtkTreeStore*) gtk_tree_view_get_model(titulos->treeview);

  sprintf(query,"select tit.code, t.razao, tit.pedido, parc.posicao, bnc.nome,"
  " tit.tipo_titulo, parc.valor, parc.data_criacao, parc.data_vencimento"
  " from titulos as tit inner join parcelas_tab as parc inner join bancos as bnc inner join terceiros as t"
  " on tit.code = parc.parcelas_id and bnc.code = parc.banco and t.code = tit.cliente where tit.cliente = %i",titulos->cliente);

  if((titulos->result  = consultar(query))){
    while((titulos->row = mysql_fetch_row(titulos->result))){
      char baixas_query[MAX_QUERY_LEN];
      MYSQL_RES *res;
      MYSQL_ROW row;
      //consultar se há baixas para a parcela, caso não haja
      sprintf(baixas_query,"select data_criacao, valor from baixas_titulos where parcelas_id = %s and posicao = %s",
      titulos->row[TIT_CODE_COL],
      titulos->row[TIT_POS_COL]);
      int baixas_qnt=0;

      if((res = consultar(baixas_query))){
        while((row = mysql_fetch_row(res))){
          gtk_tree_store_append(modelo,&iter,NULL);
          gtk_tree_store_set(modelo,&iter,
            TIT_CODE_COL,titulos->row[TIT_CODE_COL],
            TIT_NOME_COL,titulos->row[TIT_NOME_COL],
            TIT_PED_COL,titulos->row[TIT_PED_COL],
            TIT_POS_COL,titulos->row[TIT_POS_COL],
            TIT_BANC_COL,titulos->row[TIT_BANC_COL],
            TIT_TIPO_COL,titulos->row[TIT_TIPO_COL],
            TIT_VLR_COL,titulos->row[TIT_VLR_COL],
            TIT_CRIACAO_COL,titulos->row[TIT_CRIACAO_COL],
            TIT_VENCI_COL,titulos->row[TIT_VENCI_COL],
            TIT_BAIXA_COL,row[0],
            TIT_VLRBAIXA_COL,row[1],
            -1
          );
          baixas_qnt++;
        }
      }

      if(!baixas_qnt){
        gtk_tree_store_append(modelo,&iter,NULL);
        gtk_tree_store_set(modelo,&iter,
          TIT_CODE_COL,titulos->row[TIT_CODE_COL],
          TIT_NOME_COL,titulos->row[TIT_NOME_COL],
          TIT_PED_COL,titulos->row[TIT_PED_COL],
          TIT_POS_COL,titulos->row[TIT_POS_COL],
          TIT_BANC_COL,titulos->row[TIT_BANC_COL],
          TIT_VLR_COL,titulos->row[TIT_VLR_COL],
          TIT_TIPO_COL,titulos->row[TIT_TIPO_COL],
          TIT_CRIACAO_COL,titulos->row[TIT_CRIACAO_COL],
          TIT_VENCI_COL,titulos->row[TIT_VENCI_COL],
          TIT_BAIXA_COL,"Não baixado",
          TIT_VLRBAIXA_COL,"Não baixado",
          -1
        );
      }
    }
  }
  return 0;
}
