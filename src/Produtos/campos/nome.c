int nome_prod()
{
	nomes_prod = (gchar *) gtk_entry_get_text(GTK_ENTRY(nome_prod_field));

	if(strlen(nomes_prod)>=MAX_NAME_LEN){
		popup(NULL,"Nome inserido ultrapassa limite");
		gtk_widget_grab_focus(GTK_WIDGET(nome_prod_field));
		return 1;
	}

	if(strlen(nomes_prod)<=0){
		popup(NULL,"Insira um Nome");
		gtk_widget_grab_focus(GTK_WIDGET(nome_prod_field));
		return 1;
	}else{
		gtk_widget_grab_focus(peso_prod_field);
	}

	g_print("nome: %s\n",nomes_prod);

	return 0;
}
