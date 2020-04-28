int transp_cidadec()
{
	transp_cidade = (gchar *)gtk_entry_get_text(GTK_ENTRY(transp_cidade_entry));
	if(strlen(transp_cidade)<=0)
	{
		if(terceiros.criticar.entrega==0)
		{
			transp_cidade = malloc(sizeof(char*)*MAX_CID_LEN);
			strcpy(transp_cidade,"");
			gtk_widget_grab_focus(transp_estado_entry);
			return 0;
		}
		popup(NULL,"Por favor insira a cidade para Entrega");
		gtk_widget_grab_focus(GTK_WIDGET(transp_cidade_entry));
		return 1;		
	}
	if(strlen(transp_cidade)>MAX_CID_LEN)
	{
		popup(NULL,"Nome da Cidade muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(transp_cidade_entry);
		return 1;
	}
	else
	{
		gtk_widget_grab_focus(transp_estado_entry);
	}
	g_print("Cidade Transp: %s\n",transp_cidade);
	return 0;
}


