int ped_cancelar(){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	gchar *ped_code = (gchar*)gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));
	if(!strlen(ped_code)){
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do pedido");
		return 1;
	}

	struct _pedido *pedidoPtr = malloc(sizeof(struct _pedido));
	pedidoPtr->infos = malloc(sizeof(struct _ped_infos));
	pedidoPtr->infos->ped_code = atoi(ped_code);

	int ped_status = ped_get_status();
	
	if(ped_status == STATUS_PED_CAN){
		if(!PopupBinario("O pedido já está cancelado!", "Remova possíveis movimentos", "Abortar"))
			return 0;
	}

	sprintf(query,"select b.parcelas_id from baixas_titulos as b inner join titulos as tit on b.parcelas_id = tit.code where tit.pedido = %i",
	pedidoPtr->infos->ped_code);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar baixas");
		return 1;
	}
	if((row = mysql_fetch_row(res))){
		if(aviso_de_baixa_fin())
			return 1;
	}

	sprintf(query,"delete from faturamento where pedido = %i",pedidoPtr->infos->ped_code);
	if(enviar_query(query)!=0){
		popup(NULL,"Erro ao reverter faturamento");
		return 1;
	}

	sprintf(query,"delete from movimento_estoque where pedido = %i",pedidoPtr->infos->ped_code);
	if(enviar_query(query)!=0){
		popup(NULL,"Erro ao reverter estoque");
		return 1;
	}

	sprintf(query,"delete b from baixas_titulos as b inner join titulos as t on b.parcelas_id = t.code where t.pedido = %i",
	pedidoPtr->infos->ped_code);
	if(enviar_query(query)){
		popup(NULL,"Não foi possivel deletar baixas de parcelas financeiro");
		return 1;
	}

	sprintf(query,"delete p from parcelas_tab as p inner join titulos as t on p.parcelas_id = t.code where t.pedido = %i",
	pedidoPtr->infos->ped_code);

	if(enviar_query(query)){
		popup(NULL,"Não foi possivel deletar parcelas no financeiro");
		return 1;
	}

	sprintf(query,"delete from titulos where pedido = %i",
	pedidoPtr->infos->ped_code);

	if(enviar_query(query)){
		popup(NULL,"Não foi possivel deletar título no financeiro");
		return 1;
	}

	sprintf(query,"update pedidos set status = %i where code = '%i'",STATUS_PED_CAN,pedidoPtr->infos->ped_code);
	if(enviar_query(query)!=0){
		popup(NULL,"Erro ao inserir valor total");
		return 1;
	}

	popup(NULL,"Pedido cancelado com sucesso!");
	ped_get_status();
	return 0;
}
