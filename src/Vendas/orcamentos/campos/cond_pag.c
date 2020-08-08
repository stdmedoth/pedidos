int rec_fat_vist()
{
	int cont=0;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char data_atual[42];
	strcpy(data_atual,data_sys);

	orc_pag_cond_gchar = (gchar *)gtk_entry_get_text (GTK_ENTRY(orc_pag_cond_entry));
	if(strlen(orc_pag_cond_gchar)<=0){
		popup(NULL,"Insira o código do modelo de datas");
		return 1;
	}

	sprintf(query,"select * from pag_cond where code = %s",orc_pag_cond_gchar);
	if((res = consultar(query))==NULL){
		return 1;
	}

	if((row = mysql_fetch_row(res))==NULL){
		popup(NULL,"O modelo de datas escolhido não existe");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(orc_pag_cond_nome),row[1]);

	if(atoi(row[6])>1)
		tipo_pag = 1;
	else
		tipo_pag = 2;

	orc_pag_tipo_int = atoi(row[2]);

	gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_entry),data_atual);

	orc_pag_dia_fixo_int = atoi(row[3]);
	if(orc_pag_dia_fixo_int==1)
		orc_pag_init_int = atoi(row[4]);
	else
		orc_pag_init_int = atoi(dia_sys);

	orc_pag_parc_int = atoi(row[5]);

	orc_pag_parc_qnt_int = atoi(row[6]);

	for(int cont=1;cont<=MAX_PROD_ORC;cont++)
	{
		if(ativos[cont].id==1)
		{
			if(ha_prods()){
				codigo_prod_orc(NULL,cont);
				qnt_prod_orc(NULL,cont);
			}
		}
	}

	pag_cond = atoi(orc_pag_cond_gchar);
	orc_parcelas.pagcond_code = pag_cond;
	orc_pag_cond_activated=1;

	for(int cont=1;cont<=MAX_PROD_ORC;cont++){
		if(ativos[cont].id == 1){
			gtk_widget_grab_focus(codigo_prod_orc_entry[cont]);
			break;
		}
	}
	orc_pag_datas_fun();
	gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),0);
	return 0;
}
