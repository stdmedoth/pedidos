int preco_prod()
{
	int critica;
	precos_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(preco_prod_field));
	if(strlen(precos_prod)>MAX_PRECO_LEN)
	{
		popup(NULL,"Preço muito grande");
		gtk_widget_grab_focus(preco_prod_field);
		vet_erro[PRC_ERR] = 1;
		return 1;
	}
	else
	if(strlen(precos_prod)<=0&&criticar.preco!=0)
	{	
		popup(NULL,"Por favor, insira um Preço");
		gtk_widget_grab_focus(preco_prod_field);
		vet_erro[PRC_ERR] = 1;
		return 1;
	}
	else
	{
		critica = critica_real(precos_prod, preco_prod_field);
		if(critica!=0)
		{
			gtk_widget_grab_focus(preco_prod_field);
			vet_erro[PRC_ERR] = 1;
			return 1;
		}
		vet_erro[PRC_ERR] = 0;
		gtk_widget_grab_focus(peso_prod_field);
		g_print("preco: %s\n",precos_prod);
	}
	
	return 0;
}