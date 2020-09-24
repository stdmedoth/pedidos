int transp_logr_fun()
{
	transp_logradouro = (gchar *)gtk_entry_get_text(GTK_ENTRY(transp_logradouro_entry));
	if(strlen(transp_logradouro)<=0)
	{
		if(terceiros.criticar.entrega==0)
		{
			transp_logradouro = malloc(MAX_LOGR_LEN);
			strcpy(transp_logradouro,"");
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
			gtk_widget_grab_focus(transp_num_entry);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		popup(NULL,"Por favor insira a logradouro para Entrega");
		gtk_widget_grab_focus(GTK_WIDGET(transp_logradouro_entry));
		return 1;
	}
	if(strlen(transp_logradouro)>MAX_LOGR_LEN)
	{
		popup(NULL,"Nome da Cidade muito grande\nPor favor use abreviações");
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_logradouro_entry);
		return 1;
	}
	gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
	gtk_widget_grab_focus(transp_num_entry);
	g_print("Cidade Transp: %s\n",transp_logradouro);
	return 0;
}
