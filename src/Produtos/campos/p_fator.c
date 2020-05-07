int preco_faturado_prod()
{
	precos_faturado_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(preco_faturado_prod_field));
	if(strlen(precos_faturado_prod)>MAX_MRC_LEN)
	{
		popup(NULL,"Fator inserida é muito grande");
		gtk_widget_grab_focus(GTK_WIDGET(preco_faturado_prod_field));
		return 1;
	}
	else
	if(strlen(precos_faturado_prod)<=0)
	{
		if(produtos.criticar.fator==0)
		{
			gtk_widget_grab_focus(GTK_WIDGET(peso_prod_field));
			return 0; 
		}
		popup(NULL,"Por favor, insira uma fator");
		gtk_widget_grab_focus(GTK_WIDGET(preco_faturado_prod_field));
		return 1;		
	}
	else
	{
		gtk_widget_grab_focus(peso_prod_field);
	}
	g_print("fator: %s\n",precos_faturado_prod);
	
	return 0;
}

