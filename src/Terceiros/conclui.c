int conclui_ter(GtkWidget* nome, gpointer *botao)
{
	int err;

	char *query;
	concluindo_ter = 1;
	if(code_terc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(code_ter_field);
		return 1;
	}
	if(code_ter_nfe()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(code_ter_nfe_field);
		return 1;
	}
	if(name_terc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(name_ter_field);
		return 1;
	}
	if(escolha_doc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(doc_combo);
		return 1;
	}
	if(inscr_terc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(inscr_ter_field);
		return 1;
	}
	if(escolha_tipo_ter()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(type_ter_field);
		return 1;
	}
	if(cep_terc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(cep_ter_field);
		return 1;
	}
	if(address_terc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(address_ter_field);
		return 1;
	}
	if(bairro_terc()!=0){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(bairro_ter_field);
		return 1;
	}
	if(cidade_terc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(cidade_ter_field);
		return 1;
	}

	if( uf_terc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(uf_ter_field);
		return 1;
	}

	if(numrua()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(address_num_field);
		return 1;
	}
	if(cel()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
		gtk_widget_grab_focus(celular_ter_field);
		return 1;
	}
	if(tel()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
		gtk_widget_grab_focus(telefone_ter_field);
		return 1;
	}

	if(contc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
		gtk_widget_grab_focus(contatoc_ter_field);
		return 1;
	}
	if(contt()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
		gtk_widget_grab_focus(contatot_ter_field);
		return 1;
	}
	if(email_fun()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
		gtk_widget_grab_focus(email_ter_field);
		return 1;
	}
	if(contato_email()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),1);
		gtk_widget_grab_focus(contatoe_ter_field);
		return 1;
	}
	if(transp_codigo_fun()){
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_codigo_entry);
		return 1;

	}

	if(transp_cepc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_cep_entry);
		return 1;
	}

	if(transp_logr_fun()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_logradouro_entry);
		return 1;
	}

	if(transp_num_fun()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_num_entry);
		return 1;
	}

	if(transp_bairroc()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_bairro_entry);
		return 1;
	}
	if(transp_cidadec()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_cidade_entry);
		return 1;
	}

	if(transp_estado_fun()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_estado_entry);
		return 1;
	}
	if(rec_vlr_frete()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),3);
		gtk_widget_grab_focus(frete_pago_entry);
	}
	if(prazo_fun()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),3);
		gtk_widget_grab_focus(prazo_ter_field);
		return 1;
	}
	if(obs()!=0)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
		gtk_widget_grab_focus(observacoes_ter_field);
		return 1;
	}

	g_print("alocando memoria para query %i\n",(int)(QUERY_LEN+INSERT_QUERY));
	query = malloc((int)(QUERY_LEN+INSERT_QUERY));
	if(query==NULL)
	{
			popup(NULL,"Erro de memoria");
			autologger("Erro de memoria");
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
		g_print("Query para tabela terceiros\n");
		autologger("Query para tabela terceiros");
		g_print("codigo do erro %i\n",err);
		g_print("%s\n\n",query);
		autologger(query);
		return 1;
	}

	g_print("Query para tabela terceiros\n");
	g_print("Query envida com sucesso\n");

	gtk_widget_set_sensitive(GTK_WIDGET(code_ter_field),TRUE);
	cancelar_ter();
	popup(NULL,"Concluido");
	printf("finalizando conclui_ter()\n");

//	gtk_widget_grab_focus (GTK_WIDGET(name_ter_field));
	return 0;
}
