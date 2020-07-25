int address_terc()
{
	endereco_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(address_ter_field));
	if(strlen(endereco_ter)<=0)
	{
		if(terceiros.criticar.endereco==0)
		{
			endereco_ter = malloc(sizeof(char*)*MAX_ADR_LEN);
			strcpy(endereco_ter,"");
			gtk_widget_grab_focus(bairro_ter_field);
			return 0;
		}
		popup(NULL,"Por favor insira o endereco do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(address_ter_field));
		return 1;
	}

	if(strlen(endereco_ter)>MAX_ADR_LEN)
	{
		popup(NULL,"Endereco muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(address_ter_field);
		return 1;
	}

	gtk_widget_grab_focus(bairro_ter_field);

	g_print("endereco: %s\n",endereco_ter);
	return 0;
}
