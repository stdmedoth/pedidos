int orig_preco_prod_orc(GtkWidget *widget,int posicao){

	if(!produto_inserido[posicao]){
		gtk_widget_grab_focus(codigo_prod_orc_entry[posicao]);
		return 1;
	}

	orig_preco_prod_orc_gchar = (gchar*) gtk_combo_box_get_active_id(GTK_COMBO_BOX(orig_preco_prod_orc_combo[posicao]));

	if(!orig_preco_prod_orc_gchar || !strlen(orig_preco_prod_orc_gchar)){
		popup(NULL,"Origem do Preço não existente");
		file_logger("Id do preco inexistente em orig_preco_prod_orc() -> gtk_combo_box_get_active_id()");
		return 1;
	}

	valor_orig[posicao] = VLR_ORIG_DEFAULT;

	if(!strcmp(orig_preco_prod_orc_gchar, ORC_ORIGPRC_NUL)){
		valor_orig[posicao] = VLR_ORIG_NUL;
	}

	if(!strcmp(orig_preco_prod_orc_gchar, ORC_ORIGPRC_CLI)){
		valor_orig[posicao] = VLR_ORIG_CLI;
	}

	if(!strcmp(orig_preco_prod_orc_gchar, ORC_ORIGPRC_PROD)){
		valor_orig[posicao] = VLR_ORIG_PROD;
	}

	if(!strcmp(orig_preco_prod_orc_gchar, ORC_ORIGPRC_OPER)){
		valor_orig[posicao] = VLR_ORIG_OPER;
	}

	g_print("id char: %s\nid int: %i\n", orig_preco_prod_orc_gchar, valor_orig[posicao]);
	gtk_widget_grab_focus(preco_prod_orc_entry[posicao]);

	return 0;
}
