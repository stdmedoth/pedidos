int ped_cancelar(){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	char *ped_code;

	ped_code = (gchar*)gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));

	ped_infos.ped_code = atoi(ped_code);

	sprintf(query,"select * from pedidos where code = %i",ped_infos.ped_code);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar pedido");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"O pedido não existe");
		return 1;
	}
	ped_infos.status = atoi(row[7]);
	if(ped_infos.status == STATUS_PED_CAN){
		popup(NULL,"Aviso! O pedido já possui status cancelado");
	}

	if(strlen(ped_code)<=0)
	{
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do orcamento");
		return 1;
	}

	sprintf(query,"select b.parcelas_id from baixas_titulos as b inner join titulos as tit on b.parcelas_id = tit.code where tit.pedido = %i",
	ped_infos.ped_code);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar baixas");
		return 1;
	}
	if((row = mysql_fetch_row(res))){
		if(aviso_de_baixa_fin())
			return 1;
	}

	sprintf(query,"delete from faturamento where pedido = %i",ped_infos.ped_code);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao reverter faturamento");
		return 1;
	}
	sprintf(query,"delete from movimento_estoque where pedido = %i",ped_infos.ped_code);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao reverter estoque");
		return 1;
	}

	sprintf(query,"delete b from baixas_titulos as b inner join titulos as t on b.parcelas_id = t.code where t.pedido = %i",
	ped_infos.ped_code);
	if(enviar_query(query)){
		popup(NULL,"Não foi possivel deletar baixas de parcelas financeiro");
		return 1;
	}

	sprintf(query,"delete p from parcelas_tab as p inner join titulos as t on p.parcelas_id = t.code where t.pedido = %i",
	ped_infos.ped_code);

	if(enviar_query(query)){
		popup(NULL,"Não foi possivel deletar parcelas no financeiro");
		return 1;
	}

	sprintf(query,"delete from titulos where pedido = %i",
	ped_infos.ped_code);

	if(enviar_query(query)){
		popup(NULL,"Não foi possivel deletar título no financeiro");
		return 1;
	}

	sprintf(query,"update pedidos set status = 2 where code = '%i'",ped_infos.ped_code);
	if(enviar_query(query)!=0)
	{
		popup(NULL,"Erro ao inserir valor total");
		return 1;
	}

	popup(NULL,"Pedido cancelado com sucesso!");
	return 0;
}
