int ped_enviar(){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *orc_path = malloc(MAX_PATH_LEN);
	char *nome_cliente = malloc(MAX_NAME_LEN);
	char *email_cliente = malloc(MAX_EMAIL_LEN);
	char *query = malloc(MAX_QUERY_LEN);

	if(strlen(gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)))<=0)
	{
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do orcamento");
		return 1;
	}

	ped_infos.ped_code = atoi(gtk_entry_get_text(GTK_ENTRY(ped_cod_entry)));

	sprintf(orc_path,"%simp%i.pdf",ORC_PATH,ped_infos.ped_code);

	if(ped_get_status() == STATUS_PED_CAN){
		if(!PopupBinario("O pedido está cancelado, Ainda deseja enviar?", "Sim, enviar mesmo assim", "Desistir."))
			return 0;
	}

	sprintf(query,"select cliente from pedidos where code = %i",ped_infos.ped_code);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao buscar Informações do cliente");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"O pedido não existe.");
		return 1;
	}

	if(row[0])
		ped_infos.cliente_code = atoi(row[0]);

	sprintf(query,"select nome, email from contatos where terceiro = %i",ped_infos.cliente_code);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao buscar Informações do cliente");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Sem Informações do cliente");
		return 1;
	}

	if(row[0])
		strcpy(nome_cliente,row[0]);

	if(row[1])
	strcpy(email_cliente,row[1]);


	if(!fopen(orc_path,"r")){
		sprintf(orc_path,"%simp%i.html",ORC_PATH,ped_infos.ped_code);
		if( PopupBinario("O orcamento ainda não foi gerado em PDF, deseja gerar?","Sim, Gerar o PDF", "Não desejo enviar o email")
		&& !gerar_orcs_html( ped_infos.ped_code )
		&& !desenhar_pdf(orc_path))
			if(enviar_email_orcamento(nome_cliente,email_cliente,orc_path))
				return 1;
	}else{
		if(enviar_email_orcamento(nome_cliente,email_cliente,orc_path))
			return 1;
	}
	popup(NULL,"Processo concluído");
	return 0;
}
