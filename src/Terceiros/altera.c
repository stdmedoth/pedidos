
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
		gtk_entry_set_text(GTK_ENTRY(type_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(address_num_field),"");
		gtk_entry_set_text(GTK_ENTRY(cidade_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(telefone_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatot_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(celular_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(contatoc_ter_field),"");
		gtk_widget_grab_focus (GTK_WIDGET(code_ter_field));
		return 1;
	}
	
	if(campo[1]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(name_ter_field),campo[1]);
	
	if(campo[2]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field),campo[2]);
	
	if(strcmp(campo[3],"1")==0)
	{
		gtk_combo_box_set_active (GTK_COMBO_BOX(doc_combo),1);
	}
	if(strcmp(campo[3],"2")==0)
	{
		gtk_combo_box_set_active (GTK_COMBO_BOX(doc_combo),2);
	}
	
	if(campo[4]!=NULL)
	{
		gtk_entry_set_text(GTK_ENTRY(type_ter_field),campo[4]);
		strcpy(tipo_ter,campo[4]);
	}
	
	if(campo[5]!=NULL)
	{
		if(strcmp(campo[5],"1")==0)
		{
			g_print("cliente\n");
		}
		if(strcmp(campo[5],"2")==0)
		{
			g_print("fornecedor\n");
		}
	}
	
	if(campo[6]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(cep_ter_field),campo[6]);
	
	if(campo[7]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(address_ter_field),campo[7]);
	
	if(campo[8]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(address_num_field),campo[8]);
		
	if(campo[9]!=NULL)
		gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),atoi(campo[9]));
	
	if(campo[10]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(telefone_ter_field),campo[10]);
	
	if(campo[11]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(contatot_ter_field),campo[11]);
	
	if(campo[12]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(celular_ter_field),campo[12]);
	
	if(campo[13]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(contatoc_ter_field),campo[13]);
	
	if(campo[14]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(email_ter_field),campo[14]);
	
	if(campo[15]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(contatoe_ter_field),campo[15]);
	
	if(campo[16]!=NULL)
		gtk_entry_set_text(GTK_ENTRY(prazo_ter_field),campo[16]);
	
	if(campo[17]!=NULL)
		strcpy(observacoes_ter,campo[17]);
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
	/*
	 * email
	 * contato
	 * obs*/
	memset(query,0x0,strlen(query));
	alterando_ter=1;
	gtk_widget_set_sensitive(GTK_WIDGET(botao_mais),TRUE);
	gtk_label_set_text(GTK_LABEL(acao_atual2),"Alterando");
	return 0;
}
