int nome_prod()
{
	nomes_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(nome_prod_field));
	if(strlen(nomes_prod)>50)
	{
		popup(NULL,"Nome inserido é muito grande");
		gtk_widget_grab_focus(GTK_WIDGET(nome_prod_field));
		vet_erro[NOM_ERR] = 1; 
		return 1;
	}
	else
	if(strlen(nomes_prod)<=0&&criticar.nome!=0)
	{
		popup(NULL,"Por favor, insira um Nome");
		gtk_widget_grab_focus(GTK_WIDGET(nome_prod_field));
		vet_erro[NOM_ERR] = 1; 
		return 1;		
	}
	else
	{
		vet_erro[NOM_ERR] = 0; 
		gtk_widget_grab_focus(preco_prod_field);
	}
	g_print("nome: %s\n",nomes_prod);
	
	return 0;
}
