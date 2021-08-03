int conclui_ter(GtkWidget* nome, gpointer *botao)
{
	int err;
	char query[MAX_QUERY_LEN+INSERT_QUERY];
	concluindo_ter = 1;
	if(code_terc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(code_ter_field);
		return 1;
	}

	if(code_ter_nfe()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(code_ter_nfe_field);
		return 1;
	}

	if(name_terc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(name_ter_field);
		return 1;
	}

	if(ter_nome_fantasia_fun()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(ter_nome_fantasia_entry);
		return 1;
	}

	if(escolha_doc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(doc_combo);
		return 1;
	}
	if(strlen(doc_ter)){
		doc_ter = format_only_num(strdup(doc_ter));
	}


	if(inscr_terc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(inscr_ter_field);
		return 1;
	}

	if(escolha_tipo_ter()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(type_ter_field);
		return 1;
	}

	if(ter_cliente_desde()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(ter_cliente_desde_entry);
		return 1;
	}

	if(cep_terc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(cep_ter_field);
		return 1;
	}

	if(address_terc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(address_ter_field);
		return 1;
	}
	if(bairro_terc()!=0){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(bairro_ter_field);
		return 1;
	}
	if(cidade_terc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(cidade_ter_field);
		return 1;
	}

	if( uf_terc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(uf_ter_field);
		return 1;
	}

	if(numrua()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(address_num_field);
		return 1;
	}
	if(complmnt_terc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(complmt_ter_field);
		return 1;
	}

	vinc_transp();
	if(transp_codigo_fun()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_codigo_entry);
		return 1;

	}
	if(transp_cepc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_cep_entry);
		return 1;
	}
	if(transp_logr_fun()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_logradouro_entry);
		return 1;
	}
	if(transp_num_fun()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_num_entry);
		return 1;
	}
	if(transp_bairroc()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_bairro_entry);
		return 1;
	}
	if(transp_cidadec()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_cidade_entry);
		return 1;
	}
	if(transp_estado_fun()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_estado_entry);
		return 1;
	}
	if(transp_obs_fun()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_obs_entry);
		return 1;
	}
	if(rec_vlr_frete()!=0){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),3);
		gtk_widget_grab_focus(frete_pago_entry);
	}
	if(prazo_fun()!=0){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),3);
		gtk_widget_grab_focus(prazo_ter_field);
		return 1;
	}
	if(obs()!=0){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(observacoes_ter_field);
		return 1;
	}

	g_print("iniciando concluir_ter()\n");

	if(alterando_ter==0)
	{
		sprintf(query,CAD_QUERY_TER,CAD_QUERY_TER_VAR);
	}
	else
	{
		sprintf(query,UPDATE_QUERY_TER,UPDATE_QUERY_TER_VAR);
	}

	if(stoi(codigos_ter)==-1)
	{
		if(strlen(codigos_ter)>8)
		{
			g_print("Codigo terceiro muito grande %s\n",codigos_ter);
			autologger("Codigo terceiro muito grande %s");
			popup(NULL,"O código do terceiro deve ser menor\n");
			return -1;
		}
		else
		{
			g_print("Codigo do terceiro incorreto %s\n",codigos_ter);
			popup(NULL,"Codigo terceiro deve ser numérico\nPor favor corrija");
			gtk_widget_grab_focus(GTK_WIDGET(code_ter_field));
			return 1;
		}
	}
	g_print("%s\n",query);
	autologger(query);

	err = enviar_query(query);
	if(err!=0)
	{
		autologger("Query para tabela terceiros");
		autologger(query);
		return 1;
	}

	if(contatos_update()){
		concluindo_ter = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
		return 1;
	}

	gtk_widget_set_sensitive(GTK_WIDGET(code_ter_field),TRUE);
	cancelar_ter();
	popup(NULL,"Concluido");
	printf("finalizando conclui_ter()\n");

//	gtk_widget_grab_focus (GTK_WIDGET(name_ter_field));
	return 0;
}
