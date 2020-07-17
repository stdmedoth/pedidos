int prazo_fun()
{
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	prazo_ter = (gchar*) gtk_entry_get_text(GTK_ENTRY(prazo_ter_field));

	if(strlen(prazo_ter)<=0)
	{
		if(terceiros.criticar.prazo==0)
		{
			prazo_ter = malloc(sizeof(gchar*));
			strcpy(prazo_ter,"");
			if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(frete_pago_flag)))
				gtk_widget_grab_focus(frete_pago_entry);
			else
				gtk_widget_grab_focus(prod_ter_field);
			return 0;
		}
		gtk_notebook_set_current_page(GTK_NOTEBOOK(ter_notebook),3);
		popup(NULL,"Insira uma data para o prazo do cliente");
		return 1;
	}

	sprintf(query,"select * from pag_cond where code = %i",atoi(prazo_ter));
	if((res = consultar(query))==NULL){
		return 1;
	}
	if((row = mysql_fetch_row(res))==NULL){
		popup(NULL,"O modelo de datas escolhido não existe");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(campo_nome_cond_ter),row[1]);

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(frete_pago_flag)))
		gtk_widget_grab_focus(frete_pago_entry);
	else
		gtk_widget_grab_focus(prod_ter_field);
	return 0;
}
