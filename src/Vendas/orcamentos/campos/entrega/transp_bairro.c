int orc_transp_bairroc()
{
	orc_transp_bairro = (gchar *)gtk_entry_get_text(GTK_ENTRY(orc_transp_bairro_entry));
	if(strlen(orc_transp_bairro)<=0)
	{
		if(orc_com_entrega == 0)
		{
			orc_transp_bairro = malloc(MAX_BAIRRO_LEN);
			strcpy(orc_transp_bairro,"");
			gtk_widget_grab_focus(orc_transp_cidade_entry);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Por favor insira a bairro para Entrega");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_bairro_entry));
		return 1;
	}
	if(strlen(orc_transp_bairro)>MAX_BAIRRO_LEN)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Nome da bairro muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(orc_transp_bairro_entry);
		return 1;
	}
	else
	{
		gtk_widget_grab_focus(orc_transp_cidade_entry);
	}
	return 0;
}
