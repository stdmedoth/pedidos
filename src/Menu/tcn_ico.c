GtkWidget *tcn_menu_get_icon_view(){

	int N_COLUMNS=3;
	GtkTreeIter iter;
	GtkWidget *icon_view = gtk_icon_view_new();
	GtkTreeStore *modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,GDK_TYPE_PIXBUF,G_TYPE_INT);

	gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,
		0,janelas_nomes[REG_CAD_EMPRESA],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(CAD_EMP_IMG))),
    2,REG_CAD_EMPRESA,-1);

  gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,
		0,janelas_nomes[REG_CAD_CNTRATS],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(CAD_CONTR_IMG))),
    2,REG_CAD_CNTRATS,-1);

	gtk_tree_store_append(modelo,&iter,NULL);
	gtk_tree_store_set(modelo,
		&iter,
		0,janelas_nomes[REG_TNCLOG_WND],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(CAD_LOGS_IMG))),
		2,REG_TNCLOG_WND,-1);

	gtk_tree_store_append(modelo,&iter,NULL);
	gtk_tree_store_set(modelo,
		&iter,
		0,janelas_nomes[REG_BACKUP_WND],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(CAD_LOGS_IMG))),
		2,REG_BACKUP_WND,-1);

	

  gtk_icon_view_set_model(GTK_ICON_VIEW(icon_view),GTK_TREE_MODEL(modelo));

	gtk_icon_view_set_columns (GTK_ICON_VIEW(icon_view),3);
  gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view),0);
  gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view),1);
	gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(icon_view),GTK_SELECTION_BROWSE);
	gtk_icon_view_set_margin(GTK_ICON_VIEW(icon_view),10);
	//gtk_icon_view_set_activate_on_single_click(GTK_ICON_VIEW(icon_view),TRUE);
	
  g_signal_connect(icon_view,"item-activated",G_CALLBACK(icon_view_select_caller), modelo);
	g_signal_connect(icon_view,"item-activated",G_CALLBACK(menu_icon_view_select), janelas_gerenciadas.vetor_janelas[REG_MENU_WND].janela_pointer);

	return icon_view;
}
