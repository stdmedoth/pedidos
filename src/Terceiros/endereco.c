int address_terc()
{
	endereco_ter = malloc(51);
	endereco_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(address_ter_field));
	if(strlen(endereco_ter)<1)
	{
		popup(NULL,"Por favor insira o endereco do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(address_ter_field));
		endereco_ter_err = 1;
		return 1;		
	}
	if(strlen(endereco_ter)>50)
	{
		popup(NULL,"Endereco muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(address_ter_field);
		endereco_ter_err=1;
		return 1;
	}
	else
	{
		endereco_ter_err=0;
		if(tipo_ter==NULL)
		{
			gtk_widget_grab_focus(type_ter_field);
		}
		else
		{
			gtk_widget_grab_focus(concluir);
		}
	}
	g_print("endereco: %s\n",endereco_ter);
	return 0;
}
