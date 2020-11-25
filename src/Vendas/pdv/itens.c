GtkWidget *get_pdv_itens_container(){
  GtkWidget *container = gtk_box_new(1,0);

  enum{
    COLUMN0,
    COLUMN1,
    COLUMN2,
    COLUMN3,
    COLUMN4,
    COLUMN5,
    N_COLUMNS
  };

  pdv_venda_atual->cupom_atual = malloc(sizeof(struct _CFe));
  pdv_venda_atual->cupom_atual->det = malloc(sizeof(struct _cfe_det));
  pdv_venda_atual->cupom_atual->xml = xmlNewDoc((xmlChar*)"1.0");
  pdv_venda_atual->cupom_atual->det->produtos = malloc(sizeof(struct _cfe_produto )*MAX_CUPOM_ITENS);
  pdv_venda_atual->cupom_atual->det->impostos = malloc(sizeof(struct _cfe_imposto )*MAX_CUPOM_ITENS);

  GtkTreeViewColumn *coluna1,
  *coluna2,
  *coluna3,
  *coluna4,
  *coluna5,
  *coluna6;

  GtkCellRenderer *celula1,
  *celula2,
  *celula3,
  *celula4,
  *celula5,
  *celula6;

  GtkWidget *scrollwindow;
	GtkTreeStore *modelo;
	GtkTreeIter colunas, campos;
  coluna1 = gtk_tree_view_column_new();
  celula1 = gtk_cell_renderer_text_new();
  coluna2 = gtk_tree_view_column_new();
  celula2 = gtk_cell_renderer_text_new();
  coluna3 = gtk_tree_view_column_new();
  celula3 = gtk_cell_renderer_text_new();
  coluna4 = gtk_tree_view_column_new();
  celula4 = gtk_cell_renderer_text_new();
  coluna5 = gtk_tree_view_column_new();
  celula5 = gtk_cell_renderer_text_new();
  coluna6 = gtk_tree_view_column_new();
  celula6 = gtk_cell_renderer_text_new();


  pdv_itens_treeview = gtk_tree_view_new();
  gtk_tree_view_set_enable_tree_lines(GTK_TREE_VIEW(pdv_itens_treeview),TRUE);
  gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(pdv_itens_treeview),30);
  gtk_tree_view_set_enable_search(GTK_TREE_VIEW(pdv_itens_treeview),TRUE);
  gtk_tree_view_set_search_entry(GTK_TREE_VIEW(pdv_itens_treeview),NULL);

  scrollwindow = gtk_scrolled_window_new(NULL,NULL);
  gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
  gtk_tree_view_column_set_title(coluna1,"Código");
  gtk_tree_view_column_set_spacing(coluna1,5);
  gtk_tree_view_column_set_visible(coluna1,FALSE);
  gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);

  gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
  gtk_tree_view_column_set_title(coluna2,"Nome");
  gtk_tree_view_column_set_spacing(coluna2,5);
  gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);

  gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
  gtk_tree_view_column_set_title(coluna3,"Qnt.");
  gtk_tree_view_column_set_spacing(coluna3,5);
  gtk_tree_view_column_add_attribute(coluna3,celula3,"text",2);

  gtk_tree_view_column_pack_start(coluna4,celula4,TRUE);
  gtk_tree_view_column_set_title(coluna4,"Vlr. Unit.");
  gtk_tree_view_column_set_spacing(coluna4,5);
  gtk_tree_view_column_add_attribute(coluna4,celula4,"text",3);

  gtk_tree_view_column_pack_start(coluna5,celula5,TRUE);
  gtk_tree_view_column_set_title(coluna5,"Desc..");
  gtk_tree_view_column_set_spacing(coluna5,5);
  gtk_tree_view_column_add_attribute(coluna5,celula5,"text",4);

  gtk_tree_view_column_pack_start(coluna6,celula6,TRUE);
  gtk_tree_view_column_set_title(coluna6,"Total");
  gtk_tree_view_column_set_spacing(coluna6,5);
  gtk_tree_view_column_add_attribute(coluna6,celula6,"text",5);

  gtk_tree_view_append_column(GTK_TREE_VIEW(pdv_itens_treeview),coluna1);
  gtk_tree_view_append_column(GTK_TREE_VIEW(pdv_itens_treeview),coluna2);
  gtk_tree_view_append_column(GTK_TREE_VIEW(pdv_itens_treeview),coluna3);
  gtk_tree_view_append_column(GTK_TREE_VIEW(pdv_itens_treeview),coluna4);
  gtk_tree_view_append_column(GTK_TREE_VIEW(pdv_itens_treeview),coluna5);
  gtk_tree_view_append_column(GTK_TREE_VIEW(pdv_itens_treeview),coluna6);
  gtk_tree_view_set_enable_search(GTK_TREE_VIEW(pdv_itens_treeview),TRUE);
  gtk_tree_view_set_search_column(GTK_TREE_VIEW(pdv_itens_treeview),1);
  modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(pdv_itens_treeview),GTK_TREE_MODEL(modelo));

  gtk_container_add(GTK_CONTAINER(scrollwindow), pdv_itens_treeview);
  gtk_widget_set_size_request(scrollwindow,700,360);
  gtk_widget_set_size_request(container,700,360);
  gtk_widget_set_size_request(pdv_itens_treeview,700,360);

  gtk_container_add(GTK_CONTAINER(container), scrollwindow);
  return container;
}
