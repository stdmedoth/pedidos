GtkWidget *titulos_get_widget(struct _titulo *titulos){

  enum{
    TIT_CODE_COL,
    TIT_CODEBG_COL,

    TIT_NOME_COL,
    TIT_NOMEBG_COL,

    TIT_PED_COL,
    TIT_PEDBG_COL,

    TIT_POS_COL,
    TIT_POSBG_COL,

    TIT_BANC_COL,
    TIT_BANCBG_COL,

    TIT_TIPO_COL,
    TIT_TIPOBG_COL,

    TIT_VLR_COL,
    TIT_VLRBG_COL,

    TIT_CRIACAO_COL,
    TIT_CRIACAOBG_COL,

    TIT_VENCI_COL,
    TIT_VENCIBG_COL,

    TIT_BAIXA_COL,
    TIT_BAIXABG_COL,

    TIT_VLRBAIXA_COL,
    TIT_VLRBAIXABG_COL,

    TIT_VLRABAIXAR_COL,
    TIT_VLRABAIXARBG_COL,
    N_COLUMNS
  };

    enum{
    TIT_CODE_ROW,
    TIT_NOME_ROW,
    TIT_PED_ROW,
    TIT_POS_ROW,
    TIT_BANC_ROW,
    TIT_TIPO_ROW,
    TIT_VLR_ROW,
    TIT_CRIACAO_ROW,
    TIT_VENCI_ROW,
    TIT_BAIXA_ROW,
    TIT_VLRBAIXA_ROW,
    TIT_VLRABAIXAR_ROW,
    N_ROWS
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
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING,
    G_TYPE_STRING,G_TYPE_STRING );

  GtkTreeIter iter;
  char query[MAX_QUERY_LEN];

  GtkTreeViewColumn *col_code = gtk_tree_view_column_new_with_attributes("Cód. Título", gtk_cell_renderer_text_new(),"text",TIT_CODE_COL, "background", TIT_CODEBG_COL,NULL);
  GtkTreeViewColumn *col_nome = gtk_tree_view_column_new_with_attributes("Cliente", gtk_cell_renderer_text_new(),"text", TIT_NOME_COL,"background", TIT_NOMEBG_COL, NULL);
  GtkTreeViewColumn *col_ped = gtk_tree_view_column_new_with_attributes("Nº Pedido", gtk_cell_renderer_text_new(),"text", TIT_PED_COL,"background", TIT_PEDBG_COL, NULL);
  GtkTreeViewColumn *col_posicao = gtk_tree_view_column_new_with_attributes("Parcela Nº", gtk_cell_renderer_text_new(),"text", TIT_POS_COL,"background", TIT_POSBG_COL, NULL);
  GtkTreeViewColumn *col_banco = gtk_tree_view_column_new_with_attributes("Banco", gtk_cell_renderer_text_new(),"text", TIT_BANC_COL,"background", TIT_BANCBG_COL, NULL);
  GtkTreeViewColumn *col_tipo = gtk_tree_view_column_new_with_attributes("Tipo", gtk_cell_renderer_text_new(),"text", TIT_TIPO_COL,"background", TIT_TIPOBG_COL, NULL);
  GtkTreeViewColumn *col_valor = gtk_tree_view_column_new_with_attributes("Valor", gtk_cell_renderer_text_new(),"text", TIT_VLR_COL,"background", TIT_VLRBG_COL, NULL);
  GtkTreeViewColumn *col_criacao = gtk_tree_view_column_new_with_attributes("Data Criação", gtk_cell_renderer_text_new(),"text", TIT_CRIACAO_COL,"background", TIT_CRIACAOBG_COL, NULL);
  GtkTreeViewColumn *col_vencimento = gtk_tree_view_column_new_with_attributes("Data Vencimento", gtk_cell_renderer_text_new(),"text", TIT_VENCI_COL,"background", TIT_VENCIBG_COL, NULL);
  GtkTreeViewColumn *col_baixa = gtk_tree_view_column_new_with_attributes("Data Baixa", gtk_cell_renderer_text_new(),"text", TIT_BAIXA_COL,"background", TIT_BAIXABG_COL, NULL);
  GtkTreeViewColumn *col_vlrbaixa = gtk_tree_view_column_new_with_attributes("Vlr Baixado", gtk_cell_renderer_text_new(),"text", TIT_VLRBAIXA_COL,"background", TIT_VLRBAIXABG_COL, NULL);
  GtkTreeViewColumn *col_vlrabaixar = gtk_tree_view_column_new_with_attributes("Vlr. a Baixar", gtk_cell_renderer_text_new(),"text", TIT_VLRABAIXAR_COL,"background", TIT_VLRABAIXARBG_COL, NULL);

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
  gtk_tree_view_insert_column(GTK_TREE_VIEW(treeview),col_vlrabaixar,TIT_VLRABAIXAR_COL);

  gtk_tree_view_set_reorderable(GTK_TREE_VIEW(treeview),TRUE);
  sprintf(query,"select tit.code, t.razao, tit.pedido, parc.posicao, bnc.nome,"
  " tit.tipo_titulo, parc.valor, DATE_FORMAT(parc.data_criacao,'%%d/%%m/%%Y'), DATE_FORMAT(parc.data_vencimento,'%%d/%%m/%%Y')"
  " from titulos as tit inner join parcelas_tab as parc inner join terceiros as t inner join bancos as bnc"
  " on tit.code = parc.parcelas_id and bnc.code = parc.banco and t.code = tit.cliente order by parc.data_vencimento limit 20");

  if((titulos->result  = consultar(query))){
    while((titulos->row = mysql_fetch_row(titulos->result))){
      char baixas_query[MAX_QUERY_LEN];

      MYSQL_RES *res;
      MYSQL_ROW row;

      char vlrprc[MAX_PRECO_LEN];
      sprintf(vlrprc,"R$ %.2f",atof(titulos->row[TIT_VLR_ROW]));


      enum{
        BAIXA_DT,
        BAIXA_VALOR
      };
      //consultar se há baixas para a parcela, caso não haja preecher com 'não baixado'
      sprintf(baixas_query,"select DATE_FORMAT(data_criacao,'%%d/%%m/%%Y'), valor from baixas_titulos where parcelas_id = %s and posicao = %s",
      titulos->row[TIT_CODE_ROW],
      titulos->row[TIT_POS_ROW]);
      int baixas_qnt=0;

      if((res = consultar(baixas_query))){
        while((row = mysql_fetch_row(res))){

          char vlrabxr[MAX_PRECO_LEN];
          char *tipo_tit = NULL;
          switch(atoi(titulos->row[TIT_TIPO_ROW])){
            case TP_TIT_REC:
              tipo_tit = strdup("A Receber");
              break;
            case TP_TIT_PAG:
              tipo_tit = strdup("A Pagar");
              break;

            default:
              tipo_tit = strdup("Não identificado");
          }

          gchar color[20];
          if( atof(titulos->row[TIT_VLR_ROW]) == atof(row[BAIXA_VALOR]) ){
            sprintf(color, "greenyellow");
          }else{
            sprintf(color, "yellow");
          }
          
          char vlrbx[MAX_PRECO_LEN];
          sprintf(vlrbx,"R$ %.2f",atof(row[BAIXA_VALOR]));
          sprintf(vlrabxr,"R$ %.2f", atof(titulos->row[TIT_VLR_ROW]) - atof(row[BAIXA_VALOR]));
          gtk_tree_store_append(modelo,&iter,NULL);
          gtk_tree_store_set(modelo,&iter,
            TIT_CODE_COL,titulos->row[TIT_CODE_ROW],
            TIT_CODEBG_COL, color,

            TIT_NOME_COL,titulos->row[TIT_NOME_ROW],
            TIT_NOMEBG_COL, color,

            TIT_PED_COL,titulos->row[TIT_PED_ROW],
            TIT_PEDBG_COL, color,

            TIT_POS_COL,titulos->row[TIT_POS_ROW],
            TIT_POSBG_COL, color,

            TIT_BANC_COL,titulos->row[TIT_BANC_ROW],
            TIT_BANCBG_COL, color,

            TIT_TIPO_COL,tipo_tit,
            TIT_TIPOBG_COL, color,

            TIT_VLR_COL,vlrprc,
            TIT_VLRBG_COL, color,

            TIT_CRIACAO_COL,titulos->row[TIT_CRIACAO_ROW],
            TIT_CRIACAOBG_COL, color,

            TIT_VENCI_COL,titulos->row[TIT_VENCI_ROW],
            TIT_VENCIBG_COL, color,

            TIT_BAIXA_COL,row[BAIXA_DT],
            TIT_BAIXABG_COL, color,

            TIT_VLRBAIXA_COL,vlrbx,
            TIT_VLRBAIXABG_COL, color,

            TIT_VLRABAIXAR_COL,vlrabxr,
            TIT_VLRABAIXARBG_COL, color,
            -1
          );

          baixas_qnt++;
        }
      }

      if(!baixas_qnt){
        char *tipo_tit = NULL;
        switch(atoi(titulos->row[TIT_TIPO_ROW])){
          case TP_TIT_REC:
            tipo_tit = strdup("A Receber");
            break;
          case TP_TIT_PAG:
            tipo_tit = strdup("A Pagar");
            break;

          default:
            tipo_tit = strdup("Não identificado");
        }

        gchar color[20];
        sprintf(color, "salmon");
        gtk_tree_store_append(modelo,&iter,NULL);
        gtk_tree_store_set(modelo,&iter,
          TIT_CODE_COL,titulos->row[TIT_CODE_ROW],
          TIT_CODEBG_COL, color,

          TIT_NOME_COL,titulos->row[TIT_NOME_ROW],
          TIT_NOMEBG_COL, color,

          TIT_PED_COL,titulos->row[TIT_PED_ROW],
          TIT_PEDBG_COL, color,

          TIT_POS_COL,titulos->row[TIT_POS_ROW],
          TIT_POSBG_COL, color,

          TIT_BANC_COL,titulos->row[TIT_BANC_ROW],
          TIT_BANCBG_COL, color,

          TIT_VLR_COL,vlrprc,
          TIT_VLRBG_COL, color,

          TIT_TIPO_COL,tipo_tit,
          TIT_TIPOBG_COL, color,

          TIT_CRIACAO_COL,titulos->row[TIT_CRIACAO_ROW],
          TIT_CRIACAOBG_COL, color,

          TIT_VENCI_COL,titulos->row[TIT_VENCI_ROW],
          TIT_VENCIBG_COL, color,

          TIT_BAIXA_COL,"Não baixado",
          TIT_BAIXABG_COL, color,

          TIT_VLRBAIXA_COL,"Não baixado",
          TIT_VLRBAIXABG_COL, color,

          TIT_VLRABAIXAR_COL,"Total",
          TIT_VLRABAIXARBG_COL, color,

          -1
        );
      }
    }
  }

  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview),GTK_TREE_MODEL(modelo));
  gtk_container_add(GTK_CONTAINER(scrollwnd),treeview);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollwnd), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_widget_set_size_request(scrollwnd,600,300);
  gtk_box_pack_start(GTK_BOX(box_titulos),scrollwnd,0,0,0);
  gtk_widget_set_size_request(box_titulos,600,300);
  gtk_widget_show_all(box_titulos);
  return box_titulos;
}
