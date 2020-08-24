int trsp_cad_alterar_fun(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

	trsp_cad_alterando = 1;
	trsp_cad_rec_alteracao = 1;

	if(trsp_cad_code_fun())
		return 1;

	sprintf(query,"select transportador,cliente,cep_inicio,cep_entrega,num_entrega,orcamento,vlr_frete,valor_desconto_frete,observacoes_entrega from servico_transporte where code = %s",trsp_cad_code_gchar);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível alterar");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"O serviço não existe para ser alterado");
		return 1;
	}

	gtk_entry_set_text(GTK_ENTRY(trsp_cad_trspcode_entry),row[0]);
	gtk_widget_activate(trsp_cad_trspcode_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_clicode_entry),row[1]);
	gtk_widget_activate(trsp_cad_clicode_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_cepini_entry),row[2]);
	gtk_widget_activate(trsp_cad_cepini_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_cepentr_entry),row[3]);
	gtk_widget_activate(trsp_cad_cepentr_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_nument_entry),row[4]);
	gtk_widget_activate(trsp_cad_nument_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_orc_entry),row[5]);
	gtk_widget_activate(trsp_cad_orc_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_vlrfrt_entry),row[6]);
	gtk_widget_activate(trsp_cad_vlrfrt_entry);
	gtk_entry_set_text(GTK_ENTRY(trsp_cad_descfrt_entry),row[7]);
	gtk_widget_activate(trsp_cad_descfrt_entry);

	trsp_cad_rec_alteracao = 0;

	return 0;
}
