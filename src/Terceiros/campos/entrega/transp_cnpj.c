int transp_cnpjc()
{
	transp_cnpj = (gchar *)gtk_entry_get_text(GTK_ENTRY(transp_cnpj_entry));
	
	if(strlen(transp_cnpj)<=0)
	{
		if(terceiros.criticar.transp_cnpj==0)
		{
			transp_cnpj = malloc(sizeof(char*)*CNPJ_S_LEN);
			strcpy(transp_cnpj,"");
			gtk_widget_grab_focus(transp_ie_entry);
			return 0;
		}
		popup(NULL,"Por favor insira o CNPJ da Transportadora");
		gtk_widget_grab_focus(GTK_WIDGET(transp_cnpj_entry));
		return 1;		
	}
	
	if(strlen(transp_cnpj)>CNPJ_S_LEN)
	{
		popup(NULL,"CNPJ muito grande");
		gtk_widget_grab_focus(transp_cnpj_entry);
		return 1;
	}
	gtk_widget_grab_focus(transp_ie_entry);
	g_print("transp_cnpj: %s\n",transp_cnpj);
	return 0;
}

