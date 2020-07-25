int orc_transp_cidadec()
{
	orc_transp_cidade = (gchar *)gtk_entry_get_text(GTK_ENTRY(orc_transp_cidade_entry));
	if(strlen(orc_transp_cidade)<=0)
	{
		if(terceiros.criticar.entrega==0)
		{
			orc_transp_cidade = malloc(MAX_CID_LEN);
			strcpy(orc_transp_cidade,"");
			gtk_widget_grab_focus(orc_transp_estado_entry);
			return 0;
		}
		popup(NULL,"Por favor insira a cidade para Entrega");
		gtk_widget_grab_focus(GTK_WIDGET(orc_transp_cidade_entry));
		return 1;
	}
	if(strlen(orc_transp_cidade)>MAX_CID_LEN)
	{
		popup(NULL,"Nome da Cidade muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(orc_transp_cidade_entry);
		return 1;
	}
	else
	{
		gtk_widget_grab_focus(orc_transp_estado_entry);
	}
	g_print("Cidade Transp: %s\n",orc_transp_cidade);
	return 0;
}
