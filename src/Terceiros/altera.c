
int altera_ter()
{
	char task[10];
	char query[100];
	int pos=0;
	gchar *cod;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	cod= (gchar *)gtk_entry_get_text(GTK_ENTRY(code_ter_field));
	sprintf(query,"select * from terceiros where code = '%s';",cod);
	g_print("query: %s\n",query);
	autologger(query);
	estado = consultar(query);
	g_print("verificando estado da alteracao\n");
	campo = mysql_fetch_row(estado);
	
	if(campo==NULL)
	{
		g_print("terceiro não existe para ser alterado\n");
		popup(NULL,"Terceiro não existe");
		sprintf(task,"%i",tasker("terceiros"));
		gtk_entry_set_text(GTK_ENTRY(code_ter_field),task);
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),"");
		gtk_combo_box_set_active(GTK_COMBO_BOX(type_ter_field),0);
		gtk_entry_set_text(GTK_ENTRY(address_num_field),"");
		gtk_entry_set_text(GTK_ENTRY(cidade_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(telefone_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatot_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(celular_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatoc_ter_field),"");
		gtk_widget_grab_focus (GTK_WIDGET(code_ter_field));
		return 1;
	}
	
	if(campo[RAZ_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),campo[RAZ_TER_COL]);
	
	if(campo[DOC_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),campo[DOC_TER_COL]);
	
	if(atoi(campo[TDOC_TER_COL])==1)
	{
		gtk_combo_box_set_active (GTK_COMBO_BOX(doc_combo),1);
	}
	if(atoi(campo[TDOC_TER_COL])==2)
	{
		gtk_combo_box_set_active (GTK_COMBO_BOX(doc_combo),2);
	}
	if(atoi(campo[TDOC_TER_COL])==3)
	{
		gtk_combo_box_set_active (GTK_COMBO_BOX(doc_combo),3);
	}
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
	
	if(campo[CEP_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(cep_ter_field),campo[CEP_TER_COL]);
	
	if(campo[END_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),campo[END_TER_COL]);
	
	if(campo[CID_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(cidade_ter_field),campo[CID_TER_COL]);
	
	if(campo[UF_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(uf_ter_field),campo[UF_TER_COL]);
	
	if(campo[REND_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(address_num_field),campo[REND_TER_COL]);
		
	if(campo[TRUA_TER_COL]!=NULL)
		gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),atoi(campo[TRUA_TER_COL]));
	
	if(campo[TEL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(telefone_ter_field),campo[TEL_TER_COL]);
	
	if(campo[CTEL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(contatot_ter_field),campo[CTEL_TER_COL]);
	
	if(campo[CEL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(celular_ter_field),campo[CEL_TER_COL]);
	
	if(campo[CCEL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(contatoc_ter_field),campo[CCEL_TER_COL]);
	
	if(campo[EMAIl_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(email_ter_field),campo[EMAIl_TER_COL]);
	
	if(campo[CEMAIL_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(contatoe_ter_field),campo[CEMAIL_TER_COL]);
	
	if(campo[PRAZ_TER_COL]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(prazo_ter_field),campo[PRAZ_TER_COL]);
	
	if(campo[OBS_TER_COL]!=NULL)
		strcpy(observacoes_ter,campo[OBS_TER_COL]);
	else
		strcpy(observacoes_ter,"");

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(observacoes_ter_field));
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer),observacoes_ter,strlen(observacoes_ter));
	
	if(alterando_ter==1)
	{
		for(pos=0;pos<bloco_qnt;pos++)
			gtk_widget_destroy(precos_caixas[pos]);
	}
	rec_precos();
	
	gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),0);
	
	memset(query,0x0,strlen(query));
	alterando_ter=1;
	gtk_widget_set_sensitive(GTK_WIDGET(code_ter_field),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),TRUE);
	gtk_label_set_text(GTK_LABEL(acao_atual2),"Alterando");
	return 0;

}
