int code_ter_nfe()
{
	codigos_ter_nfe = (gchar*) gtk_entry_get_text(GTK_ENTRY(code_ter_nfe_field));
	if(strlen(codigos_ter_nfe)<=0)
	{	
		strcpy(codigos_ter_nfe,"");
		gtk_widget_grab_focus(inscr_ter_field);
	}
	
	if(strlen(codigos_ter_nfe)>=MAX_CODE_LEN*2)
	{		
		popup(NULL,"O código está muito extenso\nConsulte suporte");
		gtk_widget_grab_focus(code_ter_nfe_field);
	}
	
	gtk_widget_grab_focus(inscr_ter_field);
	
	return 0;
}
