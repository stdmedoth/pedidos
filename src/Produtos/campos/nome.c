int name_prod()
{
	nomes_prod = malloc(51);
	nomes_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(name_field));
	if(strlen(nomes_prod)>50)
	{
		popup(NULL,"Nome inserido é muito grande");
		gtk_widget_grab_focus(GTK_WIDGET(name_field));
		nomes_prod_err=1;
		return 1;
	}
	else
	if(strlen(nomes_prod)<1)
	{
		popup(NULL,"Por favor, insira um Nome");
		gtk_widget_grab_focus(GTK_WIDGET(name_field));
		nomes_prod_err=1;
		return 1;		
	}
	else
	{
		nomes_prod_err=0;
		gtk_widget_grab_focus(price_field);
	}
	g_print("nome: %s\n",nomes_prod);
	
	return 0;
}
