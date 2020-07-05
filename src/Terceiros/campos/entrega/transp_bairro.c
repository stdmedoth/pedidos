int transp_bairroc()
{
	transp_bairro = (gchar *)gtk_entry_get_text(GTK_ENTRY(transp_bairro_entry));
	if(strlen(transp_bairro)<=0)
	{
		if(terceiros.criticar.entrega==0)
		{
			transp_bairro = malloc(MAX_BAIRRO_LEN);
			strcpy(transp_bairro,"");
			gtk_widget_grab_focus(transp_cidade_entry);
			return 0;
		}

		popup(NULL,"Por favor insira a bairro para Entrega");
		gtk_widget_grab_focus(GTK_WIDGET(transp_bairro_entry));
		return 1;
	}
	if(strlen(transp_bairro)>MAX_BAIRRO_LEN)
	{
		popup(NULL,"Nome da bairro muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(transp_bairro_entry);
		return 1;
	}
	else
	{
		gtk_widget_grab_focus(transp_cidade_entry);
	}
	g_print("bairro Transp: %s\n",transp_bairro);
	return 0;
}
