int ped_enviar(){
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *orc_path = malloc(MAX_PATH_LEN);
	char *nome_cliente = malloc(MAX_NAME_LEN);
	char *email_cliente = malloc(MAX_EMAIL_LEN);
	char *query = malloc(MAX_QUERY_LEN);

	gchar *ped_code = (gchar*)gtk_entry_get_text(GTK_ENTRY(ped_cod_entry));
	if(!strlen(ped_code)){
		gtk_widget_grab_focus(ped_cod_entry);
		popup(NULL,"Insira o código do pedido");
		return 1;
	}

	if(!cad_emp_exists_emails()){
		popup(NULL,"Não há email configurado para envio de emails");
		return 1;
	}

	struct _pedido *pedidoPtr = malloc( sizeof(struct _pedido) );
	pedidoPtr->infos = malloc( sizeof(struct _ped_infos) );
	pedidoPtr->infos->ped_code = atoi(ped_code);

	int status = ped_get_status();
	if(status == -1){
		return 1;
	}
	if( status == STATUS_PED_CAN  ){
		if(!PopupBinario("O pedido está cancelado, Ainda deseja enviar?", "Sim, enviar mesmo assim", "Desistir."))
			return 1;
	}

	enum{
		CLIENTE
	};

	sprintf(query,"select cliente from pedidos where code = %i",pedidoPtr->infos->ped_code);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao buscar Informações do cliente");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"O pedido não existe.");
		return 1;
	}

	if(row[CLIENTE])
		pedidoPtr->infos->cliente_code = atoi(row[CLIENTE]);


	enum{
		NOME,
		EMAIL
	};

	sprintf(query,"select nome, email from contatos where terceiro = %i",pedidoPtr->infos->cliente_code);
	if(!(res = consultar(query))){
		popup(NULL,"Erro ao buscar Informações do cliente");
		return 1;
	}
	if(!(row = mysql_fetch_row(res))){
		popup(NULL,"Cliente sem sem contatos");
		return 1;
	}

	if(row[NOME])
		strcpy(nome_cliente,row[NOME]);

	if(row[EMAIL])
		strcpy(email_cliente,row[EMAIL]);


	if(!fopen(orc_path,"r")){
		sprintf(orc_path,"%simp%i.html",ORC_PATH,pedidoPtr->infos->ped_code);
		if( PopupBinario("O orcamento ainda não foi gerado em PDF, deseja gerar?","Sim, Gerar o PDF", "Não desejo enviar o email")
		&& !gerar_orcs_html( pedidoPtr->infos->ped_code )
		&& !desenhar_pdf(orc_path) )
			if(enviar_email_orcamento(nome_cliente,email_cliente,orc_path))
				return 1;
	}else{
		if(enviar_email_orcamento(nome_cliente,email_cliente,orc_path))
			return 1;
	}
	popup(NULL,"Processo concluído");
	return 0;
}
