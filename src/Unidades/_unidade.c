int multiplo_und()
{
	unidade_prod = malloc(51);
	unidade_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(und_field));
	if(strlen(nomes_prod)>50)
	{
		popup(NULL,"Unidade inserida é muito grande");
		gtk_widget_grab_focus(GTK_WIDGET(und_field));
		unidade_prod_err=1;
		return 1;
	}
	else
	if(strlen(unidade_prod)<1)
	{
		popup(NULL,"Por favor, insira uma Unidade");
		gtk_widget_grab_focus(GTK_WIDGET(und_field));
		unidade_prod_err=1;
		return 1;		
	}
	else
	{
		unidade_prod_err=0;
		gtk_widget_grab_focus(concluir);
	}
	g_print("nome: %s\n",unidade_prod);
	
	return 0;
}
