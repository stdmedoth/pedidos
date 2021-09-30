static int cancela_orc()
{
	char code[MAX_CODE_LEN];
	GtkTextBuffer *buffer;
	cancelando_orc = 1;
	for(int cont=1;cont<MAX_PROD_ORC;cont++)
	{
		if(ativos[cont].id){
			tirar_linha(cont);
		}

		id_vetor[cont] = 0;
		ativos[cont].id = 0;
		valor_orig[cont] = 0;
		excluidos[cont].id = 0;
		aviso_estoque[cont] = 0;
		preco_alterado[cont] = 0;
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

	gtk_combo_box_set_active(GTK_COMBO_BOX(orc_form_pag_combo), 0);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_transp_frete_pago_button), FALSE);
	gtk_widget_set_sensitive(orc_transp_valor_frete_entry,TRUE);
	gtk_widget_set_sensitive(orc_transp_desconto_frete_entry,TRUE);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(	orc_transp_obs_entry));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),"",-1);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_orc));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),"",-1);

	gtk_widget_set_size_request(prod_scroll_window,1100,400);
	gtk_widget_set_size_request(prod_scroll_box,1100,400);

	gtk_widget_set_size_request(prod_scroll_window,1100,400);
	gtk_widget_set_size_request(prod_scroll_box,1100,400);

	pag_cond = 0;
	tipo_pag = 0;
	itens_qnt = 1;
	alerta_obs = 0;
	ativos_qnt = 1;
	orc_contem_ped = 0;
	rec_altera_qnt = 1;
	transp_verified = 0;
	orc_com_entrega = 0;

	pag_cond = 0;
	tipo_pag = 0;
	alerta_obs = 0;
	copiando_orc=0;
	concluindo_orc=0;
	copiando_orc = 0;
	alterando_orc = 0;
	alterando_orc = 0;
	excluindo_orc = 0;
	concluindo_orc = 0;
	orc_pag_cond_fp = 0;
	recebendo_prod_orc=0;
	orc_form_pag_changed = 0;
	orc_pag_cond_activated=0;
	orc_transp_frete_pago_int=0;
	orc_transp_frete_pago_mudado=0;

	orc_valores.valor_prds = 0;
	orc_valores.valor_prds_desc = 0;
	orc_valores.valor_frete = 0;
	orc_valores.desconto_frete = 0;
	orc_valores.desconto_total = 0;
	orc_valores.valor_total = 0;

	adicionar_linha_orc();
	orc_prod_saldos_clean();
	orc_pag_sem_finan();
	gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),0);

	gtk_widget_set_sensitive(concluir_orc_button,TRUE);
	gtk_widget_set_sensitive(alterar_orc_button,TRUE);
	gtk_widget_set_sensitive(codigo_orc_entry,TRUE);
	gtk_widget_set_sensitive(pesquisa_orc,TRUE);
	gtk_widget_set_sensitive(concluir_orc_button, TRUE);
	gtk_widget_set_sensitive(pedido_orc_button, TRUE);
	gtk_widget_set_sensitive(copia_orc_button,TRUE);
	gtk_widget_set_sensitive(gerar_orc_button,FALSE);

	//gtk_widget_set_sensitive(orc_prods_grid, TRUE);
	gtk_widget_grab_focus(pesquisa_ter);

	orc_srv_transp_cancelar_fun();
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(orc_flag_entrega_check), FALSE);
	orc_flag_entrega();

	cancelando_orc = 0;

	return 0;
}
