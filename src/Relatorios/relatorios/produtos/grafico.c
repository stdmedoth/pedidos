int relat_prod_grafico_fun(){

  GtkWidget *janela_grafico = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *treeview, *scroll, *box;

  gtk_widget_set_name(janela_grafico,"graf_prodrelat");
	gtk_window_set_position(GTK_WINDOW(janela_grafico),3);
	gtk_window_set_resizable(GTK_WINDOW(janela_grafico),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela_grafico),"Relatório de Produtos");
	gtk_window_set_icon_name(GTK_WINDOW(janela_grafico),"system-software-install");
	gtk_window_set_transient_for(GTK_WINDOW(janela_grafico),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela_grafico), 10);

  MYSQL_RES *res1,*res2;
	MYSQL_ROW row1,row2;
  char query[MAX_QUERY_LEN];
  int *tipos_colunas = NULL, list_qnt=0;

  enum{
    ROW_NAME,
    ROW_TIPO
  };
  sprintf(query,"select b.nome, b.tipo_dado from criador_relat as a inner join relat_tab_campos as b on a.campos = b.code where a.code = %s", relat_prod_codigo_gchar);
  if( !(res1 = consultar(query)) ){
    popup(NULL,"Não foi possivel receber colunas do relatorio");
    relat_prod_gerando=0;
    return 1;
  }
  int num_rows = mysql_num_rows(res1);
  if(!num_rows){
    popup(NULL,"Não há colunas para o relatório");
    relat_prod_gerando=0;
    return 1;
  }

  GtkTreeViewColumn *coluna[num_rows];
  GtkCellRenderer *celula[num_rows];
  GtkTreeIter colunas, campos;
  GtkTreeStore *model;

  treeview = gtk_tree_view_new();
  box = gtk_box_new(0,0);
  scroll = gtk_scrolled_window_new(NULL,NULL);

  gtk_container_add(GTK_CONTAINER(scroll), treeview);
  gtk_box_pack_start(GTK_BOX(box), scroll,0,0,0);
  gtk_container_add(GTK_CONTAINER(janela_grafico), box);

  gtk_widget_set_size_request(treeview, 800, 300);
  gtk_widget_set_size_request(scroll, 800, 300);
  gtk_widget_set_size_request(box, 800, 300);

  tipos_colunas = malloc( num_rows * sizeof(int) );

  enum{
    NONE,
    TEXTO,
    NUM_INT,
    NUM_REAL,
    REAIS,
    DATA
  };

  GType gtipos[num_rows];
  int cont =0;
  while((row1 = mysql_fetch_row(res1))){

    if( cont >= num_rows )
      break;

    coluna[cont] = gtk_tree_view_column_new();
    celula[cont] = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(coluna[cont],celula[cont],TRUE);
    gtk_tree_view_column_set_title(coluna[cont],row1[ROW_NAME]);
    gtk_tree_view_column_add_attribute(coluna[cont],celula[cont],"text",cont);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),coluna[cont]);

    /*switch (atoi(row1[1])) {
      case TEXTO:
        tipos[cont] = G_TYPE_STRING;
        break;
      case NUM_INT:

        break;
      case NUM_REAL:

        break;
      case REAIS:

        break;
      case DATA:

        break;
    }*/
    gtipos[cont] = G_TYPE_STRING;
    tipos_colunas[cont] = atoi(row1[ROW_TIPO]);
    g_print("valor tipo coluna row: %i\n",tipos_colunas[cont]);

    cont++;

  }
  model = (GtkTreeStore *) gtk_tree_store_newv(num_rows, gtipos);

  gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), (GtkTreeModel *) model);

  if( !(res2 = consultar(relat_prod_query_gchar)) ){
    popup(NULL,"Erro ao receber dados do relatorio");
    relat_prod_gerando=0;
    return 1;
  }
  while((row2 = mysql_fetch_row(res2))){
    cont = 0;
    gtk_tree_store_append(model,&campos,NULL);
    while(cont < num_rows){
      gchar msg[strlen(row2[cont]) + 10];

      if(tipos_colunas[cont] == TEXTO)//texto
        sprintf(msg,"%s",row2[cont]);
      else
      if(tipos_colunas[cont] == NUM_INT)//inteiro - corrigir para TEXTO
        sprintf(msg,"%i",atoi(row2[cont]));
      else
      if(tipos_colunas[cont] == NUM_REAL)//float
        sprintf(msg,"%.2f",atof(row2[cont]));
      else
      if(tipos_colunas[cont] == REAIS)//dinheiro
        sprintf(msg,"R$ %.2f",atof(row2[cont]));
      else
      if(tipos_colunas[cont] == DATA)//data
        sprintf(msg,"%s",row2[cont]);
      else{
        g_print("valor tipo coluna: %i\n", tipos_colunas[cont]);
        popup(NULL,"Não foi possivel receber tipo de dados! verifique!");
        return 1;
      }

      gtk_tree_store_set(model,&campos,
      cont,msg,
      -1);
      cont++;
      list_qnt++;
    }
  }
  if(!list_qnt){
    popup(NULL,"Nenhum listagem gerada");
    relat_prod_gerando=0;
    return 0;
  }

  gtk_widget_show_all(janela_grafico);
  return 0;
}
