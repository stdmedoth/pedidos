int est_said_qnt_fun(){
	char query[MAX_QUERY_LEN];
	MYSQL_RES *res;
	MYSQL_ROW row;

	if(est_said_produto_fun())
		return 1;

	if(est_said_est_fun())
		return 1;

	est_said_qnt_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(est_said_qnt_entry));
	if(strlen(est_said_qnt_gchar)<=0){
		popup(NULL,"Insira a quantidade de saída");
		gtk_widget_grab_focus(est_said_qnt_entry);
		return 1;
	}

	if(critica_real(est_said_qnt_gchar,est_said_qnt_entry))
		return 1;

	sprintf(query,"select SUM(entradas) - SUM(saidas) - %.2f from movimento_estoque where produto = %i and estoque = %i",
	atof(est_said_qnt_gchar),
	atoi(est_said_prod_gchar),
	est_said_est_int);

	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar saldo do produto");
		return 1;
	}
	float saldo = -atof(est_said_qnt_gchar);
	if((row = mysql_fetch_row(res))){
		if(row[0])
			saldo = atof(row[0]);

		if(saldo < 0){
			popup(NULL,"Produto ficará com saldo negativo");
			return 1;
		}
	}

	sprintf(query,"select saldo_min from saldo_min where produto = %i and estoque = %i",
	atoi(est_said_prod_gchar),
	est_said_est_int);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar saldo do produto");
		return 1;
	}
	if(!concluindo_mov_said_est && !alterando_mov_said_est && !mov_said_est_limit){
		float saldo_min=0;
		if((row = mysql_fetch_row(res))){
			saldo_min = atof(row[0]);
			if(saldo < saldo_min){
				popup(NULL,"O produto atingirá o saldo mínimo");
			}
		}
		mov_said_est_limit=1;
	}


	gtk_widget_grab_focus(est_said_confirma_button);
	return 0;
}
