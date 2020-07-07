int peso_prod()
{
	int critica=0;
	pesos_prod = (gchar*) gtk_entry_get_text(GTK_ENTRY(peso_prod_field));
	g_print("pesos_prod antes: %s\n",pesos_prod);
	if(strlen(pesos_prod)>MAX_PRECO_LEN)
	{
		popup(NULL,"Preço muito grande");
		gtk_widget_grab_focus(peso_prod_field);
		return 1;
	}

	if(strlen(pesos_prod)<=0)
	{
		if(produtos.criticar.peso==0)
		{
			pesos_prod = malloc(MAX_PRECO_LEN);
			strcpy(pesos_prod,"");

			critica = critica_real(pesos_prod, peso_prod_field);

			gtk_widget_grab_focus(fornecedor_prod_field);
			return 0;
		}

		popup(NULL,"Por favor, insira um Peso");
		gtk_widget_grab_focus(peso_prod_field);
		return 1;

	}
	else
	{
		critica = critica_real(pesos_prod, peso_prod_field);

		if(critica!=0)
		{
			gtk_widget_grab_focus(peso_prod_field);
			return 1;
		}

		gtk_widget_grab_focus(fornecedor_prod_field);
	}
	g_print("pesos_prod depois: %s\n",pesos_prod);
	return 0;
}
