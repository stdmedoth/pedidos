int altera_ter()
{
	char task[10];
	char query[MAX_QUERY_LEN];
	int pos=0;
	gchar *cod;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;
	alterando_ter=1;

	if(code_terc()!=0)
		return 0;

	sprintf(query,"select * from terceiros where code = '%i';",atoi(codigos_ter));
	g_print("query: %s\n",query);
	autologger(query);
	estado = consultar(query);
	g_print("verificando estado da alteracao\n");
	campo = mysql_fetch_row(estado);

	if(campo==NULL)
	{
		g_print("terceiro não existe para ser alterado\n");
		popup(NULL,"Terceiro não existe");
		cancelar_ter();
		return 1;
	}

	if(campo[COD_TER_NFE_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(code_ter_nfe_field),campo[COD_TER_NFE_COL]);

	if(campo[RAZ_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),campo[RAZ_TER_COL]);

	if(campo[DOC_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),campo[DOC_TER_COL]);

	gtk_combo_box_set_active (GTK_COMBO_BOX(doc_combo),atoi(campo[TDOC_TER_COL]));

	if(campo[IE_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(inscr_ter_field),campo[IE_TER_COL]);
	//campo[4] = tipoter string
	if(campo[TIPI_TER_COL]!=NULL)
	{
		if(atoi(campo[TIPI_TER_COL])==0)
		{
			gtk_combo_box_set_active (GTK_COMBO_BOX(type_ter_field),0);
		}
		if(atoi(campo[TIPI_TER_COL])==1)
		{
			gtk_combo_box_set_active (GTK_COMBO_BOX(type_ter_field),1);
		}
		if(atoi(campo[TIPI_TER_COL])==2)
		{
			gtk_combo_box_set_active (GTK_COMBO_BOX(type_ter_field),2);
		}
		if(atoi(campo[TIPI_TER_COL])==3)
		{
			gtk_combo_box_set_active (GTK_COMBO_BOX(type_ter_field),3);
		}
	}

	if(campo[CEP_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(cep_ter_field),campo[CEP_TER_COL]);

	if(campo[END_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),campo[END_TER_COL]);

	if(campo[CPLMNT_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(complmt_ter_field),campo[CPLMNT_TER_COL]);

	if(campo[BAIR_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(bairro_ter_field),campo[BAIR_TER_COL]);

	if(campo[CID_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(cidade_ter_field),campo[CID_TER_COL]);

	if(campo[UF_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(uf_ter_field),campo[UF_TER_COL]);

	if(campo[REND_TER_COL])
		gtk_entry_set_text(GTK_ENTRY(address_num_field),campo[REND_TER_COL]);

	if(campo[TRUA_TER_COL])
		gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),atoi(campo[TRUA_TER_COL]));

	//contatos func

	titulos_cadter.cliente = atoi(codigos_ter);
	titulos_update_widget(&titulos_cadter);

	contatos_ter = atoi(codigos_ter);
	GList *colunas = gtk_tree_view_get_columns(GTK_TREE_VIEW (contatos_treeview));
	for(GList *coluna = colunas; coluna; coluna = g_list_next(coluna)){
		gtk_tree_view_remove_column(GTK_TREE_VIEW (contatos_treeview),GTK_TREE_VIEW_COLUMN(coluna->data));
	}
	GtkTreeModel *items_model = create_items_model ();
	GtkTreeModel *numbers_model = create_numbers_model ();
	gtk_tree_view_set_model (GTK_TREE_VIEW (contatos_treeview),items_model);
	add_columns (GTK_TREE_VIEW (contatos_treeview), items_model, numbers_model);

	if(campo[TER_TRSP_COD_COL]){
		if(atoi(campo[TER_TRSP_COD_COL])!=0){
			ter_com_entrega = 1;
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(vinc_transporte_flag),TRUE);
			gtk_entry_set_text(GTK_ENTRY(transp_codigo_entry),campo[TER_TRSP_COD_COL]);

			if(campo[TER_TRSP_LOGR_COL])
				gtk_entry_set_text(GTK_ENTRY(transp_logradouro_entry),campo[TER_TRSP_LOGR_COL]);

			if(campo[TER_TRSP_NUM_COL])
				gtk_entry_set_text(GTK_ENTRY(transp_num_entry),campo[TER_TRSP_NUM_COL]);

			if(campo[TER_TRSP_CID_COL])
				gtk_entry_set_text(GTK_ENTRY(transp_cidade_entry),campo[TER_TRSP_CID_COL]);

			if(campo[TER_TRSP_BAIR_COL])
				gtk_entry_set_text(GTK_ENTRY(transp_estado_entry),campo[TER_TRSP_BAIR_COL]);

			if(campo[TER_TRSP_UF_COL])
				gtk_entry_set_text(GTK_ENTRY(transp_estado_entry),campo[TER_TRSP_UF_COL]);

			if(campo[TER_TRSP_CEP_COL])
				gtk_entry_set_text(GTK_ENTRY(transp_cep_entry),campo[TER_TRSP_CEP_COL]);

			if(campo[TER_TRSP_TEL_COL])
				gtk_entry_set_text(GTK_ENTRY(transp_telefone_entry),campo[TER_TRSP_TEL_COL]);
		}

	}

	gtk_widget_activate(transp_codigo_entry);



	if(campo[PRAZ_TER_COL]){
		if(atoi(campo[PRAZ_TER_COL])){
			gtk_entry_set_text(GTK_ENTRY(prazo_ter_field),campo[PRAZ_TER_COL]);
			gtk_widget_activate(prazo_ter_field);
		}else{
			gtk_entry_set_text(GTK_ENTRY(prazo_ter_field),"");
			gtk_widget_activate(prazo_ter_field);
		}
	}

	if(campo[FLAG_MIN_FRT_PAG_COL])
	{
		if(atoi(campo[FLAG_MIN_FRT_PAG_COL])==0)
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(frete_pago_flag),FALSE);
		else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(frete_pago_flag),TRUE);
	}

	if(campo[VLR_MIN_FRT_PAG_COL]){
		gtk_entry_set_text(GTK_ENTRY(frete_pago_entry),campo[VLR_MIN_FRT_PAG_COL]);

	}

	if(campo[OBS_TER_COL])
		observacoes_ter = strdup(campo[OBS_TER_COL]);
	else
		observacoes_ter = strdup("");

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_ter_field));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),observacoes_ter,strlen(observacoes_ter));

	gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);

	memset(query,0x0,strlen(query));

	gtk_widget_set_sensitive(GTK_WIDGET(code_ter_field),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(alterar_ter_buttom),FALSE);
	gtk_widget_set_sensitive(psq_ter_button,FALSE);
	gtk_label_set_text(GTK_LABEL(acao_atual2),"Alterando");
	return 0;

}
