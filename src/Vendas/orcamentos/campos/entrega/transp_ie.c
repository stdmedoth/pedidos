int orc_transp_ie_fun()
{
	orc_transp_ie = (gchar *)gtk_entry_get_text(GTK_ENTRY(orc_transp_ie_entry));

	if(strlen(orc_transp_ie)<=0)
	{
		if(orc_com_entrega == 0)
		{
			orc_transp_ie = malloc(MAX_INSC_LEN);
			strcpy(orc_transp_ie,"");
			gtk_widget_grab_focus(orc_transp_cep_entry);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Por favor insira a Inscrição da Transportadora");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_ie_entry));
		return 1;
	}

	if(strlen(orc_transp_ie)>MAX_INSC_LEN)
	{
		gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);
		popup(NULL,"Inscrição muito grande");
		gtk_widget_grab_focus(orc_transp_ie_entry);
		return 1;
	}

	gtk_widget_grab_focus(orc_transp_cep_entry);
	g_print("inscr: %s\n",orc_transp_ie);
	return 0;
}
