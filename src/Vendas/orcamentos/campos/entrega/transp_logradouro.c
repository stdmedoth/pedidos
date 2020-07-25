int orc_transp_logr_fun()
{
	orc_transp_logradouro = (gchar *)gtk_entry_get_text(GTK_ENTRY(orc_transp_logradouro_entry));
	if(strlen(orc_transp_logradouro)<=0)
	{
		if(terceiros.criticar.entrega==0)
		{
			orc_transp_logradouro = malloc(MAX_LOGR_LEN);
			strcpy(orc_transp_logradouro,"");
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
			gtk_widget_grab_focus(orc_transp_num_entry);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		popup(NULL,"Por favor insira a logradouro para Entrega");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_logradouro_entry));
		return 1;
	}
	if(strlen(orc_transp_logradouro)>MAX_LOGR_LEN)
	{
		popup(NULL,"Nome da Cidade muito grande\nPor favor use abreviações");
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(orc_transp_logradouro_entry);
		return 1;
	}
	gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
	gtk_widget_grab_focus(orc_transp_num_entry);
	g_print("Cidade Transp: %s\n",orc_transp_logradouro);
	return 0;
}
