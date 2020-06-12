int transp_estado_fun()
{
	transp_estado = (gchar *)gtk_entry_get_text(GTK_ENTRY(transp_estado_entry));
	if(strlen(transp_estado)<=0)
	{
		if(terceiros.criticar.entrega==0)
		{
			transp_estado = malloc(MAX_EST_LEN);
			strcpy(transp_estado,"");
			gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),3);
			gtk_widget_grab_focus(prazo_ter_field);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		popup(NULL,"Por favor insira a estado para Entrega");
		gtk_widget_grab_focus(GTK_WIDGET(transp_estado_entry));
		return 1;		
	}
	if(strlen(transp_estado)>MAX_EST_LEN)
	{
		popup(NULL,"Nome da Cidade muito grande\nPor favor use abreviações");
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),2);
		gtk_widget_grab_focus(transp_estado_entry);
		return 1;
	}
	gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),3);
	gtk_widget_grab_focus(prazo_ter_field);
	g_print("Cidade Transp: %s\n",transp_estado);
	return 0;	
}
