
int titulos_update_widget(struct _titulo *titulos){

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

  sprintf(query, "select tit.code, t.razao, tit.pedido, parc.posicao, IFNULL(bnc.nome, 'Sem Banco'), tit.tipo_titulo, parc.valor, DATE_FORMAT(parc.data_criacao,'%%d/%%m/%%Y'), DATE_FORMAT(parc.data_vencimento,'%%d/%%m/%%Y') from titulos as tit inner join parcelas_tab as parc inner join terceiros as t on tit.code = parc.parcelas_id and t.code = tit.cliente left join bancos as bnc ON bnc.code = parc.banco where tit.cliente = %i order by parc.data_vencimento",titulos->cliente);

  if((titulos->result  = consultar(query))){
    while((titulos->row = mysql_fetch_row(titulos->result))){
      char baixas_query[MAX_QUERY_LEN];
      MYSQL_RES *res;
      MYSQL_ROW row;

      enum{
        BAIXA_DT,
        BAIXA_VALOR
      };
      //consultar se há baixas para a parcela, caso não haja
      sprintf(baixas_query,"select DATE_FORMAT(data_criacao,'%%d/%%m/%%Y'), valor from baixas_titulos where parcelas_id = %s and posicao = %s order by data_criacao",
      titulos->row[TIT_CODE_ROW],
      titulos->row[TIT_POS_ROW]);
      int baixas_qnt=0;

      char vlrprc[MAX_PRECO_LEN];
      sprintf(vlrprc,"R$ %.2f",atof(titulos->row[TIT_VLR_ROW]));
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

      if((res = consultar(baixas_query))){
        while((row = mysql_fetch_row(res))){

          char vlrbx[MAX_PRECO_LEN];
          char vlrabxr[MAX_PRECO_LEN];
          sprintf(vlrbx,"R$ %.2f",atof(row[BAIXA_VALOR]));
          sprintf(vlrabxr,"R$ %.2f", atof(titulos->row[TIT_VLR_ROW]) - atof(row[BAIXA_VALOR]));

          gchar color[20];
          if( atof(titulos->row[TIT_VLR_ROW]) == atof(row[BAIXA_VALOR]) ){
            sprintf(color, "greenyellow");
          }else{
            sprintf(color, "yellow");
          }

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
  return 0;
}
