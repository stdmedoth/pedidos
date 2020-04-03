int address_terc()
{
	endereco_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(address_ter_field));
	if(strlen(endereco_ter)<=0&&criticar.endereco!=0)
	{
		popup(NULL,"Por favor insira o endereco do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(address_ter_field));
		vet_erro[END_ERR] = 1;
		return 1;		
	}
	if(strlen(endereco_ter)>MAX_ADR_LEN)
	{
		popup(NULL,"Endereco muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(address_ter_field);
		vet_erro[END_ERR]=1;
		return 1;
	}
	else
	{
		vet_erro[END_ERR]=0;
		if((strlen(tipo_ter))<=0)
		{
			gtk_widget_grab_focus(type_ter_field);
		}
		else
		{
			gtk_widget_grab_focus(celular_ter_field);
		}
	}
	g_print("endereco: %s\n",endereco_ter);
	return 0;
}
