int marca_prod()
{
	marcas_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(marca_prod_field));
	if(strlen(marcas_prod)>MAX_MRC_LEN)
	{
		popup(NULL,"Marca inserida é muito grande");
		gtk_widget_grab_focus(GTK_WIDGET(marca_prod_field));
		vet_erro[MRC_ERR] = 1; 
		return 1;
	}
	else
	if(strlen(marcas_prod)<=0)
	{
		if(produtos.criticar.marca==0)
		{
			gtk_widget_grab_focus(GTK_WIDGET(observacao_prod_field));
			vet_erro[MRC_ERR] = 0;
			return 0; 
		}
		popup(NULL,"Por favor, insira uma marca");
		gtk_widget_grab_focus(GTK_WIDGET(marca_prod_field));
		vet_erro[MRC_ERR] = 1;
		return 1;		
	}
	else
	{
		vet_erro[MRC_ERR] = 0; 
		gtk_widget_grab_focus(observacao_prod_field);
	}
	g_print("marca: %s\n",marcas_prod);
	
	return 0;
}

