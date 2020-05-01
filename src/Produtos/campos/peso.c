int peso_prod()
{
	int critica=0;
	pesos_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(peso_prod_field));
	if(strlen(pesos_prod)>50)
	{
		popup(NULL,"Preço muito grande");
		gtk_widget_grab_focus(peso_prod_field);
		vet_erro[PES_ERR] = 1;
		return 1;
	}
	else
	if(strlen(pesos_prod)<=0)
	{
		if(produtos.criticar.peso==0)
		{
			critica = critica_real(pesos_prod, peso_prod_field);
			gtk_widget_grab_focus(unidade_prod_field);
			return 0;
		}	
		popup(NULL,"Por favor, insira um Peso");
		gtk_widget_grab_focus(peso_prod_field);
		vet_erro[PES_ERR] = 1;
		return 1;
	}
	else
	{
		critica = critica_real(pesos_prod, peso_prod_field);
		if(critica!=0)
		{
			gtk_widget_grab_focus(peso_prod_field);
			vet_erro[PES_ERR] = 1;
			return 1;
		}
		vet_erro[PES_ERR] = 0;
		gtk_widget_grab_focus(unidade_prod_field);
	}
	g_print("peso: %s\n",pesos_prod);
	return 0;
}
