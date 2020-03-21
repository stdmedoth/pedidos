int price_prod()
{
	int critica;
	preco_prod = malloc(51);
	preco_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(price_field));
	if(strlen(preco_prod)>50)
	{
		popup(NULL,"Preço muito grande");
		gtk_widget_grab_focus(price_field);
		preco_prod_err=1;
		return 1;
	}
	else
	if(strlen(preco_prod)<1)
	{	
		popup(NULL,"Por favor, insira um Preço");
		gtk_widget_grab_focus(price_field);
		preco_prod_err=1;
		return 1;
	}
	else
	{
		critica = critica_preco(preco_prod,price_field);
		if(critica!=0)
		{
			gtk_widget_grab_focus(price_field);
			preco_prod_err=1;
			return 1;
		}
		preco_prod_err=0;
		gtk_widget_grab_focus(supp_field);
	}
	g_print("preco: %s\n",preco_prod);
	return 0;
}
