int complmnt_terc()
{
	complmt_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(complmt_ter_field));
	if(strlen(complmt_ter)<=0)
	{
			complmt_ter = malloc(sizeof(char*)*MAX_COMPLMNTO_LEN);
			strcpy(complmt_ter,"");
			return 0;
	}
	if(strlen(complmt_ter)>MAX_COMPLMNTO_LEN)
	{
		popup(NULL,"Complemento muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(complmt_ter_field);
		return 1;
	}
	gtk_widget_grab_focus(bairro_ter_field);
	return 0;
}
