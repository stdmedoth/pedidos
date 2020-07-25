GtkWidget *orc_campos_datas(){
  GtkWidget *box, *grid;
  GtkTreeIter iter1;
  GtkWidget *orc_scrolled,*orc_scrolled_box,*orc_pag_datas_fixed;
  GtkTreeViewColumn *coluna1, *coluna2, *coluna3;
  GtkCellRenderer *celula1, *celula2, *celula3;

  orc_scrolled_box = gtk_box_new(1,0);
  orc_scrolled = gtk_scrolled_window_new(NULL,NULL);
  grid = gtk_grid_new();
  box = gtk_box_new(1,0);

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
  gtk_box_pack_start(GTK_BOX(orc_scrolled_box),orc_pag_datas_frame,0,0,5);
  gtk_container_add(GTK_CONTAINER(orc_scrolled),orc_scrolled_box);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_fixed),orc_scrolled,20,20);

  gtk_widget_set_size_request(orc_scrolled,220,200);
  gtk_widget_set_size_request(orc_scrolled_box,220,200);

  return orc_pag_datas_fixed;
}
