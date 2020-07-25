int orc_transp_cnpjc()
{
	orc_transp_cnpj = (gchar *)gtk_entry_get_text(GTK_ENTRY(orc_transp_cnpj_entry));
	if(strlen(orc_transp_cnpj)<=0)
	{
		if(terceiros.criticar.entrega==0)
		{
			orc_transp_logradouro = malloc(MAX_LOGR_LEN);
			strcpy(orc_transp_logradouro,"");
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
			gtk_widget_grab_focus(orc_transp_ie_entry);
			return 0;
		}
		popup(NULL,"Por favor insira o CNPJ da Transportadora");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_cnpj_entry));
		return 1;
	}

	if(strlen(orc_transp_cnpj)>CNPJ_S_LEN)
	{
		popup(NULL,"CNPJ muito grande");
		gtk_widget_grab_focus(orc_transp_cnpj_entry);
		return 1;
	}
	gtk_widget_grab_focus(orc_transp_ie_entry);
	g_print("orc_transp_cnpj: %s\n",orc_transp_cnpj);
	return 0;
}
