int prazo_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	prazo_ter = (gchar*) gtk_entry_get_text(GTK_ENTRY(prazo_ter_field));

	if(strlen(prazo_ter)<=0){		
		prazo_ter = strdup("NULL");
		gtk_entry_set_text(GTK_ENTRY(prazo_ter_field),"");
		gtk_entry_set_text(GTK_ENTRY(campo_nome_cond_ter),"");
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(frete_pago_flag)))
			gtk_widget_grab_focus(frete_pago_entry);
		else
			gtk_widget_grab_focus(prod_ter_field);
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),4);
		return 0;
	}

	struct _condpag *condpag = cond_pag_get(atoi(prazo_ter));
	if(!condpag){
		popup(NULL,"Não foi possível encontrar pagamento escolhido");
		return 1;
	}
	
	gtk_entry_set_text(GTK_ENTRY(campo_nome_cond_ter),condpag->nome);

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(frete_pago_flag)))
		gtk_widget_grab_focus(frete_pago_entry);
	else
		gtk_widget_grab_focus(prod_ter_field);
	return 0;
}
