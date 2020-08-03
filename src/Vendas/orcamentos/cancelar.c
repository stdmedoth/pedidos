static int cancela_orc()
{
	char code[MAX_CODE_LEN];
	GtkTextBuffer *buffer;

	cont=1;
	for(int cont=1;cont<=MAX_PROD_ORC;cont++)
	{
		if(ativos[cont].id==1)
		{
			tirar_linha(cont);
		}

		preco_alterado[cont] = 0;
		aviso_estoque[cont] = 0;
		valor_orig[cont] = 0;
		id_vetor[cont] = 0;
		produto_inserido[cont] = 0;
	}

	gtk_grid_remove_column(GTK_GRID(orc_prods_grid),0);

	sprintf(code,"%i",tasker("orcamentos"));
	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),code);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_name_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_end_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_tel_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_pag_cond_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_pag_cond_nome),"");

	gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_ie_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_codigo_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_num_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_logradouro_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_bairro_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_cidade_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_estado_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),"");
	gtk_entry_set_text(GTK_ENTRY(orc_transp_telefone_entry),"");

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(	orc_transp_obs_entry));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),"",-1);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_orc));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),"",-1);

	gtk_widget_set_size_request(prod_scroll_window,1100,400);
	gtk_widget_set_size_request(prod_scroll_box,1100,400);

	gtk_widget_set_size_request(prod_scroll_window,1100,400);
	gtk_widget_set_size_request(prod_scroll_box,1100,400);

	cont=1;
	itens_qnt = 1;
	ativos_qnt = 1;
	rec_altera_qnt = 1;


	pag_cond = 0;
	tipo_pag = 0;
	alerta_obs = 0;
	copiando_orc = 0;
	alterando_orc = 0;
	concluindo_orc = 0;
	excluindo_orc = 0;
	orc_pag_cond_activated=0;
	recebendo_prod_orc=0;

	adicionar_linha_orc();

	gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),0);
	gtk_widget_set_sensitive(concluir_orc_button,TRUE);
	gtk_widget_set_sensitive(alterar_orc_button,TRUE);
	gtk_widget_set_sensitive(codigo_orc_entry,TRUE);
	gtk_widget_set_sensitive(pesquisa_orc,TRUE);
	gtk_widget_set_sensitive(copia_orc_button,TRUE);
	return 0;
}
