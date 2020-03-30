int name_terc()
{
	nomes_ter = malloc(51);
	nomes_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(name_ter_field));
	if(strlen(nomes_ter)>50)
	{
		popup(NULL,"Nome muito grande\nPor favor diminua");
		gtk_widget_grab_focus(GTK_WIDGET(name_ter_field));
		nomes_ter_err=1;
		return 1;
	}
	if(strlen(nomes_ter)<1)
	{
		popup(NULL,"Por favor insira um nome para o terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(name_ter_field));
		nomes_ter_err=1;
		return 1;
	}
	if(strlen(nomes_ter)<1)
	{
		popup(NULL,"Por favor insira o nome do terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(name_ter_field));
		nomes_ter_err=1;
		return 1;
	
	}
	else
	{
		nomes_ter_err=0;
		gtk_widget_grab_focus(address_ter_field);
	}
	g_print("nome: %s\n",nomes_ter);
	return 0;
}
