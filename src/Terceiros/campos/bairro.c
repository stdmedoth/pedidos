int bairro_terc()
{
	bairro_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(bairro_ter_field));

	if(strlen(bairro_ter)<=0)
	{
		if(terceiros.criticar.bairro==0)
		{
			bairro_ter = malloc(sizeof(char*)*MAX_CID_LEN);
			strcpy(bairro_ter,"");
			gtk_widget_grab_focus(uf_ter_field);
			return 0;
		}
		popup(NULL,"Por favor insira o bairro do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(bairro_ter_field));
		return 1;
	}

	if(strlen(bairro_ter)>MAX_CID_LEN)
	{
		popup(NULL,"Nome da bairro muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(bairro_ter_field);
		return 1;
	}
	else
	{
		gtk_widget_grab_focus(uf_ter_field);
	}
	g_print("bairro: %s\n",bairro_ter);
	return 0;
}
