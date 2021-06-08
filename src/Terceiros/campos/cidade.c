int cidade_terc()
{

	cidade_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(cidade_ter_field));
	if(strlen(cidade_ter)<=0)
	{
		if(terceiros.criticar.cidade==0)
		{
			cidade_ter = malloc(sizeof(char*)*MAX_CID_LEN);
			strcpy(cidade_ter,"");
			gtk_widget_grab_focus(uf_ter_field);
			return 0;
		}
		popup(NULL,"Por favor insira a cidade do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(cidade_ter_field));
		return 1;
	}
	if(strlen(cidade_ter)>MAX_CID_LEN)
	{
		popup(NULL,"Nome da Cidade muito grande\nPor favor use abreviações");
		gtk_widget_grab_focus(cidade_ter_field);
		return 1;
	}
	else
	{
		gtk_widget_grab_focus(uf_ter_field);
	}
	ter_cep_cidade_alterado = 1;
	g_print("cidade: %s\n",cidade_ter);
	return 0;
}
