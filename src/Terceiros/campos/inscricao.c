int inscr_terc()
{
	inscr_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(inscr_ter_field));
	if(strlen(inscr_ter)<=0)
	{
		if(terceiros.criticar.inscricao==0)
		{
			inscr_ter = malloc(sizeof(char*)*MAX_CID_LEN);
			strcpy(inscr_ter,"");
			gtk_widget_grab_focus(name_ter_field);
			return 0;
		}
		popup(NULL,"Por favor insira a Inscrição do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(inscr_ter_field));
		return 1;
	}
	if(strlen(inscr_ter)>MAX_INSC_LEN)
	{
		popup(NULL,"Inscrição muito grande");
		gtk_widget_grab_focus(inscr_ter_field);
		return 1;
	}


	gtk_widget_grab_focus(name_ter_field);
	g_print("inscr: %s\n",inscr_ter);
	return 0;
}
