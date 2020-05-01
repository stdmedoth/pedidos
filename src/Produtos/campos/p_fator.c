int fator_prod()
{
	fatores_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(fator_prod_field));
	if(strlen(fatores_prod)>MAX_MRC_LEN)
	{
		popup(NULL,"Fator inserida é muito grande");
		gtk_widget_grab_focus(GTK_WIDGET(fator_prod_field));
		vet_erro[MRC_ERR] = 1; 
		return 1;
	}
	else
	if(strlen(fatores_prod)<=0)
	{
		if(produtos.criticar.fator==0)
		{
			gtk_widget_grab_focus(GTK_WIDGET(observacao_prod_field));
			vet_erro[MRC_ERR] = 0;
			return 0; 
		}
		popup(NULL,"Por favor, insira uma fator");
		gtk_widget_grab_focus(GTK_WIDGET(fator_prod_field));
		vet_erro[MRC_ERR] = 1;
		return 1;		
	}
	else
	{
		vet_erro[MRC_ERR] = 0; 
		gtk_widget_grab_focus(observacao_prod_field);
	}
	g_print("fator: %s\n",fatores_prod);
	
	return 0;
}

