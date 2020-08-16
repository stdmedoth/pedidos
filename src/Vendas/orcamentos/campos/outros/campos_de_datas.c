GtkWidget *orc_campos_datas(){
  GtkWidget *box, *grid;
  GtkTreeIter iter1;
  GtkTreeViewColumn *coluna1, *coluna2, *coluna3;
  GtkCellRenderer *celula1, *celula2, *celula3;
  GtkWidget *orc_pag_datas_livres_parcqnt_frame, *orc_pag_datas_livres_parcqnt_fixed,*rest_parcqnt_box;
  GtkWidget *orc_pag_datas_livres_rest_frame, *orc_pag_datas_livres_rest_fixed;
  GtkWidget *orc_pag_datas_livres_scroll,
  *orc_pag_datas_livres_scroll_box;

  GtkWidget *orc_pag_datas_livres_label1,
  *orc_pag_datas_livres_label2,
  *orc_pag_datas_livres_box,
  *orc_pag_datas_livres_frame;

  GtkWidget *orc_pag_datas_livres_label2_fixed,
  *orc_pag_datas_livres_label1_fixed;

  orc_pag_datas_livres_entry1 = malloc(sizeof(GtkEntry*)*MAX_PARCELAS_QNT);
  orc_pag_datas_livres_entry2 = malloc(sizeof(GtkEntry*)*MAX_PARCELAS_QNT);

  orc_pag_datas_livres_parcqnt = gtk_spin_button_new_with_range(1,MAX_PARCELAS_QNT,1);
  gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_livres_parcqnt),5);
  orc_pag_datas_livres_parcqnt_frame = gtk_frame_new("Num. Parcelas:");
  orc_pag_datas_livres_parcqnt_fixed = gtk_fixed_new();

  rest_parcqnt_box = gtk_box_new(1,0);

  orc_pag_datas_livres_rest = gtk_entry_new();
  gtk_widget_set_sensitive(orc_pag_datas_livres_rest,FALSE);
  gtk_widget_set_name(orc_pag_datas_livres_rest,"entry_unsensetivate");
  gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_livres_rest),5);
  orc_pag_datas_livres_rest_frame = gtk_frame_new("Valor Restante:");
  orc_pag_datas_livres_rest_fixed = gtk_fixed_new();

  gtk_container_add(GTK_CONTAINER(orc_pag_datas_livres_parcqnt_frame),orc_pag_datas_livres_parcqnt);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_parcqnt_fixed),orc_pag_datas_livres_parcqnt_frame,10,20);

  gtk_container_add(GTK_CONTAINER(orc_pag_datas_livres_rest_frame),orc_pag_datas_livres_rest);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_rest_fixed),orc_pag_datas_livres_rest_frame,10,20);

  orc_pag_scrolled_box = gtk_box_new(1,0);
  orc_pag_scrolled = gtk_scrolled_window_new(NULL,NULL);
  grid = gtk_grid_new();
  box = gtk_box_new(1,0);
  orc_pag_datas = gtk_box_new(0,0);

  orc_pag_datas_entry = gtk_entry_new ();
  gtk_widget_set_sensitive(orc_pag_datas_entry,FALSE);
  gtk_widget_set_name(orc_pag_datas_entry,"entry_unsensetivate");
  gtk_entry_set_placeholder_text(GTK_ENTRY(orc_pag_datas_entry),"Insira Data Teste");
  orc_pag_psq_datas_button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(orc_pag_psq_datas_button),gtk_image_new_from_file(IMG_PESQ));

  orc_pag_psq_datas_box = gtk_box_new(0,0);
  gtk_box_pack_start(GTK_BOX(orc_pag_psq_datas_box),orc_pag_datas_entry,0,0,0);
  gtk_box_pack_start(GTK_BOX(orc_pag_psq_datas_box),orc_pag_psq_datas_button,0,0,0);

  orc_pag_datas_model = gtk_tree_store_new(3,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING);
  orc_pag_datas_tree = gtk_tree_view_new_with_model((GtkTreeModel*)orc_pag_datas_model);
  orc_pag_datas_fixed = gtk_fixed_new();
  orc_pag_datas_box = gtk_box_new(1,0);
  orc_pag_datas_frame = gtk_frame_new("Parcelas");

  orc_pag_datas_livres_qnt_entry = gtk_entry_new();
  orc_pag_datas_livres_label1 = gtk_label_new("Datas");
  orc_pag_datas_livres_label2 = gtk_label_new("Valor");
  orc_pag_datas_livres_label1_fixed = gtk_fixed_new();
  orc_pag_datas_livres_label2_fixed = gtk_fixed_new();
  orc_pag_datas_livres_grid = gtk_grid_new();
  orc_pag_datas_livres_box = gtk_box_new(0,0);
  gtk_widget_set_name(orc_pag_datas_livres_box,"caixa_frame");
  orc_pag_datas_livres_frame = gtk_frame_new("Datas Livres");
  orc_pag_datas_livres_fixed = gtk_fixed_new();
  orc_pag_datas_livres_scroll = gtk_scrolled_window_new(NULL,NULL);
  orc_pag_datas_livres_scroll_box = gtk_box_new(0,0);

  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_label1_fixed),orc_pag_datas_livres_label1,20,20);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_label2_fixed),orc_pag_datas_livres_label2,20,20);

  gtk_grid_attach(GTK_GRID(orc_pag_datas_livres_grid),orc_pag_datas_livres_label1_fixed,0,0,1,1);
  gtk_grid_attach(GTK_GRID(orc_pag_datas_livres_grid),orc_pag_datas_livres_label2_fixed,1,0,1,1);

  gtk_container_add(GTK_CONTAINER(orc_pag_datas_livres_scroll),orc_pag_datas_livres_grid);
  gtk_box_pack_start(GTK_BOX(orc_pag_datas_livres_scroll_box),orc_pag_datas_livres_scroll,0,0,0);

  gtk_box_pack_start(GTK_BOX(orc_pag_datas_livres_box),orc_pag_datas_livres_scroll_box,0,0,0);

  gtk_box_pack_start(GTK_BOX(rest_parcqnt_box),orc_pag_datas_livres_parcqnt_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(rest_parcqnt_box),orc_pag_datas_livres_rest_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(orc_pag_datas_livres_box),rest_parcqnt_box,0,0,0);

  gtk_widget_set_size_request(orc_pag_datas_livres_scroll,230,200);
  //gtk_widget_set_size_request(orc_pag_datas_livres_scroll_box,290,200);
  //gtk_widget_set_size_request(orc_pag_datas_livres_grid,200,200);

  gtk_container_add(GTK_CONTAINER(orc_pag_datas_livres_frame),orc_pag_datas_livres_box);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_fixed),orc_pag_datas_livres_frame,20,20);

  coluna1 = gtk_tree_view_column_new();
  celula1 = gtk_cell_renderer_text_new();
  coluna2 = gtk_tree_view_column_new();
  celula2 = gtk_cell_renderer_text_new();
  coluna3 = gtk_tree_view_column_new();
  celula3 = gtk_cell_renderer_text_new();

  gtk_tree_view_column_pack_start(coluna1,celula1,TRUE);
  gtk_tree_view_column_set_title(coluna1,"Parcela");
  gtk_tree_view_column_add_attribute(coluna1,celula1,"text",0);

  gtk_tree_view_column_pack_start(coluna2,celula2,TRUE);
  gtk_tree_view_column_set_title(coluna2,"Data");
  gtk_tree_view_column_add_attribute(coluna2,celula2,"text",1);

  gtk_tree_view_column_pack_start(coluna3,celula3,TRUE);
  gtk_tree_view_column_set_title(coluna3,"Valor");
  gtk_tree_view_column_add_attribute(coluna3,celula3,"text",2);

  gtk_tree_view_append_column(GTK_TREE_VIEW(orc_pag_datas_tree),coluna1);
  gtk_tree_view_column_set_visible(coluna1,TRUE);
  gtk_tree_view_append_column(GTK_TREE_VIEW(orc_pag_datas_tree),coluna2);
  gtk_tree_view_column_set_visible(coluna2,TRUE);
  gtk_tree_view_append_column(GTK_TREE_VIEW(orc_pag_datas_tree),coluna3);
  gtk_tree_view_column_set_visible(coluna3,TRUE);

  gtk_tree_store_append(orc_pag_datas_model,&iter1,NULL);
  gtk_tree_store_set(orc_pag_datas_model,&iter1,0,0,1,"Listar datas",2,"0.0",-1);

  gtk_box_pack_start(GTK_BOX(orc_pag_datas_box),orc_pag_psq_datas_box,0,0,5);
  gtk_box_pack_start(GTK_BOX(orc_pag_datas_box),orc_pag_datas_tree,0,0,5);
  gtk_container_add(GTK_CONTAINER(orc_pag_datas_frame),orc_pag_datas_box);
  gtk_box_pack_start(GTK_BOX(orc_pag_scrolled_box),orc_pag_datas_frame,0,0,5);
  gtk_container_add(GTK_CONTAINER(orc_pag_scrolled),orc_pag_scrolled_box);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_fixed),orc_pag_scrolled,20,20);

  gtk_box_pack_start(GTK_BOX(orc_pag_datas),orc_pag_datas_fixed,0,0,0);
  gtk_box_pack_start(GTK_BOX(orc_pag_datas),orc_pag_datas_livres_fixed,0,0,0);

  g_signal_connect(orc_pag_datas_livres_parcqnt,"activate",G_CALLBACK(orc_pag_datas_livres),NULL);
  g_signal_connect(orc_pag_datas_livres_parcqnt,"value-changed",G_CALLBACK(orc_pag_datas_livres),NULL);
  gtk_widget_set_size_request(orc_pag_scrolled,240,200);
  gtk_widget_set_size_request(orc_pag_scrolled_box,240,200);

  return orc_pag_datas;
}
