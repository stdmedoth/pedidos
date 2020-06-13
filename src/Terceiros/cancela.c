void cancelar_ter()
{
	char *code;
	GtkTextBuffer *buffer;
	GtkTextIter inicio,fim;
	code = malloc(10);
	gtk_label_set_text(GTK_LABEL(acao_atual2),"Cadastrando");
	concluindo_ter = 0;
	alterando_ter=0;
	code[0] = '\0';
	sprintf(code,"%i",tasker("terceiros"));

	//terceiros
	gtk_entry_set_text(GTK_ENTRY(code_ter_field),code);
	gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(inscr_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(cep_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
	gtk_combo_box_set_active(GTK_COMBO_BOX(type_ter_field),0);
	gtk_entry_set_text(GTK_ENTRY(cidade_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(address_num_field),"");
	gtk_entry_set_text(GTK_ENTRY(uf_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(doc_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(celular_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(contatoc_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(telefone_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(contatot_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(email_ter_field),"");
	gtk_entry_set_text(GTK_ENTRY(contatoe_ter_field),"");

	//entrega
	gtk_entry_set_text(GTK_ENTRY(transp_codigo_entry),"");
	gtk_entry_set_text(GTK_ENTRY(transp_nome_entry),"");
	gtk_entry_set_text(GTK_ENTRY(transp_cnpj_entry),"");
	gtk_entry_set_text(GTK_ENTRY(transp_ie_entry),"");
	gtk_entry_set_text(GTK_ENTRY(transp_num_entry),"");
	gtk_entry_set_text(GTK_ENTRY(transp_logradouro_entry),"");
	gtk_entry_set_text(GTK_ENTRY(transp_cidade_entry),"");
	gtk_entry_set_text(GTK_ENTRY(transp_estado_entry),"");
	gtk_entry_set_text(GTK_ENTRY(transp_cep_entry),"");
	gtk_entry_set_text(GTK_ENTRY(transp_telefone_entry),"");

	gtk_entry_set_text(GTK_ENTRY(frete_pago_entry),"");
	gtk_entry_set_text(GTK_ENTRY(prazo_ter_field),"");

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_ter_field));
	gtk_text_buffer_get_start_iter (buffer,&inicio);
	gtk_text_buffer_get_end_iter (buffer,&fim);
	gtk_text_buffer_delete (buffer,&inicio,&fim);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(transp_obs_entry));
	gtk_text_buffer_get_start_iter (buffer,&inicio);
	gtk_text_buffer_get_end_iter (buffer,&fim);
	gtk_text_buffer_delete (buffer,&inicio,&fim);

	gtk_widget_set_sensitive(GTK_WIDGET(code_ter_field),TRUE);
	gtk_widget_set_sensitive(GTK_WIDGET(alterar_ter_buttom),TRUE);
	gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
}
