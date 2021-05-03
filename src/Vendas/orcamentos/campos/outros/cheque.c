#include "cheque_campos.c"

int orc_concluir_cheque(){
	if(orc_pag_cond_fp == FP_TIPO_CHEQUE){

		char query[MAX_QUERY_LEN];
		MYSQL_RES *res;
		MYSQL_ROW row;

		if( orc_cheque_finan() ){
			gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
			return 1;
		}
		sprintf(query, "select * from orcs_cheques where orcamento = %s", codigo_orc_gchar);
		if(!(res = consultar(query))){
			popup(NULL,"Não foi possível consultar cheque");
			return 1;
		}

		if(!(row = mysql_fetch_row(res))){
			sprintf(query,
				"insert into cheque(code, banco, conta, serie, numero, pagante, data_emissao, valor) VALUES(%s, %s, '%s', '%s', '%s', %s, STR_TO_DATE('%s', '%%d/%%m/%%Y'), %s)", 
					orc_cheque_code_gchar,
					orc_cheque_banco_gchar,
					orc_cheque_conta_gchar,
					orc_cheque_serie_gchar,
					orc_cheque_numero_gchar,
					orc_cheque_pagante_gchar,
					orc_cheque_emissao_gchar,
					orc_cheque_valor_gchar);
			if(enviar_query(query)){
				popup(NULL,"Não foi possível cadastrar cheque para o pagamento");
				return 1;
			}
			sprintf(query, "insert into orcs_cheques(orcamento, cheque) values(%s, %s)",
				codigo_orc_gchar,
				orc_cheque_code_gchar);

			if(enviar_query(query)){
				popup(NULL,"Não foi possível vincular cheque ao orcamento");
				return 1;
			}

		}else{
			orc_cheque_code_gchar = strdup(row[ORC_CHEQUE_CHQ_COL]);
			sprintf(query,
				"update cheque set banco = %s, conta = '%s', serie = '%s', numero = '%s', pagante = %s, data_emissao = STR_TO_DATE('%s', '%%d/%%m/%%Y'), valor = %s where code = %s",
					orc_cheque_banco_gchar,
					orc_cheque_conta_gchar,
					orc_cheque_serie_gchar,
					orc_cheque_numero_gchar,
					orc_cheque_pagante_gchar,
					orc_cheque_emissao_gchar,
					orc_cheque_valor_gchar,
					orc_cheque_code_gchar);

			if(enviar_query(query)){
				popup(NULL,"Não foi possível atualizar dados do cheque");
				return 1;
			}
		}
	
	}

	return 0;
}

int orc_cheque_finan(){
	
	if(orc_cheque_finan_code())
		return 1;
	if(orc_cheque_finan_banco())
		return 1;
	if(orc_cheque_finan_conta())
		return 1;
	if(orc_cheque_finan_serie())
		return 1;
	if(orc_cheque_finan_numero())
		return 1;
	if(orc_cheque_finan_pagante())
		return 1;
	if(orc_cheque_finan_emissao())
		return 1;
	
	return 0;
}

GtkWidget *orc_cheque_get_widget(){
	GtkWidget *box, *fixed, *frame;

	box = gtk_box_new(0,0);
	fixed = gtk_fixed_new();
	frame = gtk_frame_new("Cheque para pagamento");

	GtkWidget *orc_cheque_code_frame = gtk_frame_new("Código");
	GtkWidget *orc_cheque_banco_frame = gtk_frame_new("Banco");
	GtkWidget *orc_cheque_serie_frame = gtk_frame_new("Série");
	GtkWidget *orc_cheque_conta_frame = gtk_frame_new("Conta");
	GtkWidget *orc_cheque_numero_frame = gtk_frame_new("Número");
	GtkWidget *orc_cheque_pagante_frame = gtk_frame_new("Pagante");
	GtkWidget *orc_cheque_emissao_frame = gtk_frame_new("Emitido Em");

	orc_cheque_code_entry = gtk_entry_new();
	orc_cheque_banco_entry = gtk_entry_new();
	orc_cheque_serie_entry = gtk_entry_new();
	orc_cheque_conta_entry = gtk_entry_new();
	orc_cheque_numero_entry = gtk_entry_new();
	orc_cheque_pagante_entry = gtk_entry_new();
	orc_cheque_emissao_entry = gtk_entry_new();

	gtk_container_add(GTK_CONTAINER(orc_cheque_code_frame), orc_cheque_code_entry);
	gtk_container_add(GTK_CONTAINER(orc_cheque_banco_frame), orc_cheque_banco_entry);
	gtk_container_add(GTK_CONTAINER(orc_cheque_serie_frame), orc_cheque_serie_entry);
	gtk_container_add(GTK_CONTAINER(orc_cheque_conta_frame), orc_cheque_conta_entry);
	gtk_container_add(GTK_CONTAINER(orc_cheque_numero_frame), orc_cheque_numero_entry);
	gtk_container_add(GTK_CONTAINER(orc_cheque_pagante_frame), orc_cheque_pagante_entry);
	gtk_container_add(GTK_CONTAINER(orc_cheque_emissao_frame), orc_cheque_emissao_entry);

	gtk_box_pack_start(GTK_BOX(box), orc_cheque_code_frame ,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), orc_cheque_banco_frame ,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), orc_cheque_serie_frame ,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), orc_cheque_numero_frame ,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), orc_cheque_pagante_frame ,0,0,5);
	gtk_box_pack_start(GTK_BOX(box), orc_cheque_emissao_frame ,0,0,5);
	
	gtk_fixed_put(GTK_FIXED(fixed), box, 5, 5);
	gtk_container_add(GTK_CONTAINER(frame), fixed);
	return frame;
}