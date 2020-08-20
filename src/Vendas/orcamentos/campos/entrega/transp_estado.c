int orc_transp_estado_fun()
{
	orc_transp_estado = (gchar *)gtk_entry_get_text(GTK_ENTRY(orc_transp_estado_entry));
	if(strlen(orc_transp_estado)<=0)
	{
		if(orc_com_entrega == 0)
		{
			orc_transp_estado = malloc(MAX_NAME_LEN);
			strcpy(orc_transp_estado,"");
			gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
			gtk_widget_grab_focus(orc_transp_valor_frete_entry);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Por favor insira a estado para Entrega");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_estado_entry));
		return 1;
	}

	if(strlen(orc_transp_estado)>MAX_EST_LEN)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Nome da Cidade muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(orc_transp_estado_entry);
		return 1;
	}

	gtk_widget_grab_focus(orc_transp_valor_frete_entry);
	return 0;
}
