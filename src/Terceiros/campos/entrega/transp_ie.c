int transp_ie_fun()
{
	transp_ie = (gchar *)gtk_entry_get_text(GTK_ENTRY(transp_ie_entry));
	if(strlen(transp_ie)<=0)
	{
		if(terceiros.criticar.inscricao==0)
		{
			transp_ie = malloc(sizeof(char*)*MAX_CID_LEN);
			strcpy(transp_ie,"");
			gtk_widget_grab_focus(transp_cep_entry);
			return 0;
		}
		popup(NULL,"Por favor insira a Inscrição da Transportadora");
		gtk_widget_grab_focus(GTK_WIDGET(transp_ie_entry));
		return 1;		
	}
	if(strlen(transp_ie)>MAX_INSC_LEN)
	{
		popup(NULL,"Inscrição muito grande");
		gtk_widget_grab_focus(transp_ie_entry);
		return 1;
	}
	for(int cont=0;cont<strlen(transp_ie);cont++)
	{
			if(!isdigit(transp_ie[cont]))
			{
				popup(NULL,"Inscrição deve ser numérica");
				gtk_widget_grab_focus(transp_ie_entry);
				return 1;
			}
	}	
	gtk_widget_grab_focus(transp_cep_entry);
	g_print("inscr: %s\n",transp_ie);
	return 0;
}

