int orc_transp_codigo_fun()
{
	char code[10];
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	transp_verified=1;

	orc_transp_codigo = (gchar *) gtk_entry_get_text(GTK_ENTRY(orc_transp_codigo_entry));
	if(strlen(orc_transp_codigo)<=0)
	{
		gtk_entry_set_text(GTK_ENTRY(orc_transp_codigo_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_ie_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_logradouro_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cidade_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_estado_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),"");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_codigo_entry));

		orc_com_entrega = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
		return 0;
	}

	if( alterando_orc == 1 && alterando_transp == 0 ){
		gtk_entry_set_text(GTK_ENTRY(orc_transp_codigo_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_ie_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_logradouro_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cidade_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_estado_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),"");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_codigo_entry));

		orc_com_entrega = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
		return 0;
	}

	if(stoi(orc_transp_codigo)==-1)
	{
		gtk_entry_set_text(GTK_ENTRY(orc_transp_codigo_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_ie_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_logradouro_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cidade_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_estado_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),"");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_codigo_entry));

		if(strlen(orc_transp_codigo)>8)
		{
			g_print("Codigo terceiro muito grande %s\n",orc_transp_codigo);
			popup(NULL,"O código do terceiro excedeu o limite");
			return 1;
		}
		else
		{
			g_print("Codigo do terceiro incorreto %s\n",orc_transp_codigo);
			popup(NULL,"Codigo terceiro deve ser numérico");
			return 1;
		}
	}
	if(!atoi(orc_transp_codigo)){
		gtk_entry_set_text(GTK_ENTRY(orc_transp_codigo_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_logradouro_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cidade_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_estado_entry),"");
		gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),"");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_codigo_entry));
		orc_com_entrega = 0;
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
		return 0;
	}

	if(concluindo_orc == 0){
		sprintf(query,"select * from terceiros where code = %s",orc_transp_codigo);
		res = consultar(query);
		if(res==NULL)
		{
			popup(NULL,"Verifique query de transportador com suporte");
			return 1;
		}
		row = mysql_fetch_row(res);
		if(row==NULL)
		{
			popup(NULL,"Nenhum transportador para o código indicado");
			return 1;
		}
		if(row[RAZ_TER_COL])
			gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),row[RAZ_TER_COL]);

		if(row[DOC_TER_COL])
			gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),row[DOC_TER_COL]);

		if(row[IE_TER_COL])
			gtk_entry_set_text(GTK_ENTRY(orc_transp_ie_entry),row[IE_TER_COL]);
	}

	orc_com_entrega = 1;

	gtk_widget_grab_focus(orc_transp_nome_entry);
	return 0;
}
