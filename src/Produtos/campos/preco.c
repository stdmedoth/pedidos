int preco_prod()
{
	int critica=0;
	precos_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(preco_prod_field));
	if(strlen(precos_prod)>MAX_PRECO_LEN)
	{
		popup(NULL,"Preço muito grande");
		gtk_widget_grab_focus(preco_prod_field);
		return 1;
	}
	
	sprintf(precos_prod,"%.2f",atof(precos_prod));
	
	if(strlen(precos_prod)<=0)
	{	
		if(produtos.criticar.preco==0)
		{
			critica = critica_real(precos_prod, preco_prod_field);
			if(critica!=0)
			{
				gtk_widget_grab_focus(preco_prod_field);
				return 1;
			}
			gtk_entry_set_text(GTK_ENTRY(preco_prod_field),precos_prod);
			gtk_widget_grab_focus(preco_faturado_prod_field);
			return 0;
		}
		popup(NULL,"Por favor, insira um Preço");
		gtk_widget_grab_focus(preco_prod_field);
		return 1;
	}
	critica = critica_real(precos_prod, preco_prod_field);
	gtk_entry_set_text(GTK_ENTRY(preco_prod_field),precos_prod);
	if(critica!=0)
	{
		gtk_widget_grab_focus(preco_prod_field);
		return 1;
	}
	
	gtk_widget_grab_focus(preco_faturado_prod_field);
	g_print("preco: %s\n",precos_prod);
	return 0;

}
