int cancela_orc()
{
	char code[MAX_CODE_LEN];
	GtkTextBuffer *buffer;

	cont=1;
	while(cont<MAX_PROD_ORC)
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
		ativos[cont].id = 0;
		excluidos[cont].id = 1;
		cont++;
	}

	sprintf(code,"%i",tasker("orcamentos"));
	gtk_entry_set_text(GTK_ENTRY(codigo_orc_entry),code);
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_name_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_end_entry),"");
	gtk_entry_set_text(GTK_ENTRY(cliente_orc_tel_entry),"");
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_orc));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),"",-1);

	gtk_widget_set_size_request(prod_scroll_window,1100,400);
	gtk_widget_set_size_request(prod_scroll_box,1100,400);

	gtk_widget_set_size_request(prod_scroll_window,1100,400);
	gtk_widget_set_size_request(prod_scroll_box,1100,400);

	alerta_obs = 0;
	tipo_pag = 0;
	cont=0;
	itens_qnt = 1;
	ativos_qnt=1;
	rec_altera_qnt=1;
	alterando_orc=0;
	concluindo_orc=0;

	adicionar_linha_orc();

	gtk_widget_set_sensitive(alterar_orc_button,TRUE);
	gtk_widget_set_sensitive(codigo_orc_frame,TRUE);
	return 0;
}
