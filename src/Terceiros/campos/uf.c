int uf_terc()
{
	uf_ter = (gchar *)gtk_entry_get_text(GTK_ENTRY(uf_ter_field));
	if(strlen(uf_ter)<=0)
	{
		if(terceiros.criticar.uf==0)
		{
			uf_ter = malloc(sizeof(char*)*MAX_UF_LEN);
			strcpy(uf_ter,"");
			return 0;
		}
		popup(NULL,"Por favor insira a uf do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(uf_ter_field));
		return 1;
	}
	if(strlen(uf_ter)>MAX_UF_LEN)
	{
		popup(NULL,"UF muito grande\nPor favor use sigla");
		gtk_widget_grab_focus(uf_ter_field);
		return 1;
	}

	if(escolha_tipo_ter()!=0)
		return 1;

	return 0;
}
