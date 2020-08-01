int orc_transp_nomec()
{

	orc_transp_nome = (gchar *) gtk_entry_get_text(GTK_ENTRY(orc_transp_nome_entry));
	if(strlen(orc_transp_nome)>MAX_RAZ_LEN)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Nome muito grande\nPor favor diminua");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_nome_entry));
		return 1;
	}
	if(strlen(orc_transp_nome)<=0)
	{
		if(orc_com_entrega == 0)
		{
			orc_transp_nome = malloc(MAX_CODE_LEN);
			strcpy(orc_transp_nome,"");
			gtk_widget_grab_focus(orc_transp_cnpj_entry);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Por favor insira um nome para a Transportadora");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_nome_entry));
		return 1;
	}
	else
	{
		gtk_widget_grab_focus(orc_transp_cnpj_entry);
	}
	return 0;
}
