GtkWidget *mkt_menu_get_icon_view(){

	int N_COLUMNS=3;
	GtkTreeIter iter;
	GtkWidget *icon_view = gtk_icon_view_new();
	GtkTreeStore *modelo = gtk_tree_store_new(N_COLUMNS,G_TYPE_STRING,GDK_TYPE_PIXBUF,G_TYPE_INT);

	gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,
		0,janelas_nomes[REG_CAD_EST],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(ESTO_IMG))),
    2,REG_CAD_PROD,-1);

  gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,
		0,janelas_nomes[REG_ENTS],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(ADD_SALDO))),
    2,REG_ENTS,-1);

	gtk_tree_store_append(modelo,&iter,NULL);
	gtk_tree_store_set(modelo,
		&iter,
		0,janelas_nomes[REG_SAIDS],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(REM_SALDO))),
		2,REG_SAIDS,-1);

	gtk_tree_store_append(modelo,&iter,NULL);
  gtk_tree_store_set(modelo,
    &iter,
		0,janelas_nomes[REG_SALD],
		1,gtk_image_get_pixbuf(GTK_IMAGE(gtk_image_new_from_file(SALD_IMG))),
    2,REG_SALD,-1);

  gtk_icon_view_set_model(GTK_ICON_VIEW(icon_view),GTK_TREE_MODEL(modelo));

	gtk_icon_view_set_columns (GTK_ICON_VIEW(icon_view),3);
	gtk_icon_view_set_text_column(GTK_ICON_VIEW(icon_view),0);
	gtk_icon_view_set_pixbuf_column(GTK_ICON_VIEW(icon_view),1);
	gtk_icon_view_set_selection_mode(GTK_ICON_VIEW(icon_view),GTK_SELECTION_SINGLE);
	gtk_icon_view_set_margin(GTK_ICON_VIEW(icon_view),20);
	gtk_icon_view_set_activate_on_single_click(GTK_ICON_VIEW(icon_view),TRUE);
	
  g_signal_connect(icon_view,"item-activated",G_CALLBACK(icon_view_select), modelo);
	g_signal_connect(icon_view,"item-activated",G_CALLBACK(menu_icon_view_select), janelas_gerenciadas.vetor_janelas[REG_MENU_WND].janela_pointer);

	return icon_view;
}
