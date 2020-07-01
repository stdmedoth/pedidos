int rec_fat_vist()
{
	int cont=0;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	orc_cond_pag_gchar = (gchar *)gtk_entry_get_text (GTK_ENTRY(orc_cond_pag_entry));
	if(strlen(orc_cond_pag_gchar)<=0){
		popup(NULL,"Insira o código do modelo de datas");
		return 1;
	}

	sprintf(query,"select * from pag_cond where code = %s",orc_cond_pag_gchar);
	if((res = consultar(query))==NULL){
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL){
		popup(NULL,"O modelo de datas escolhido não existe");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(orc_cond_pag_nome),row[1]);
	if(atoi(row[6])>1)
		tipo_pag = 1;
	else
		tipo_pag = 2;

	do{
		if(ativos[cont].id == 1)
			break;
		cont++;
	}
	while(cont < MAX_PROD_ORC);

	for(int cont=0;cont<MAX_PROD_ORC;cont++)
	{
		if(ativos[cont].id==1)
		{
			qnt_prod_orc(NULL,cont);
		}
	}

	if(ativos[cont].id == 1)
		gtk_widget_grab_focus(codigo_prod_orc_entry[cont]);

	return 1;
}
