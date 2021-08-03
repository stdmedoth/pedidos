void ter_consulta_contrib(){

	struct _terc_infos contrib;

	contrib.doc = NULL;
	contrib.razao = NULL;
	contrib.ie = NULL;
	contrib.cep = NULL;
	contrib.cep = NULL;
	contrib.xLgr = NULL;
	contrib.c_nro = NULL;
	contrib.xBairro = NULL;
	contrib.xMun = NULL;

	gchar *cnpj = (gchar*)gtk_entry_get_text(GTK_ENTRY(doc_ter_field));
	if(!strlen(cnpj)){
		popup(NULL,"Insira o cnpj");
		return ;
	}

	gchar *formated_cnpj;
	formated_cnpj = strdup(format_only_num(cnpj));
	contrib.doc = strdup(formated_cnpj);

	if(consulta_contrib(formated_cnpj, &contrib)){
		return ;
	}

	if(contrib.razao)
		gtk_entry_set_text(GTK_ENTRY(name_ter_field), contrib.razao);
	else{
		popup(NULL,"Não foi possível receber o nome");
	}

	if(contrib.nomes_fantasia)
		gtk_entry_set_text(GTK_ENTRY(ter_nome_fantasia_entry), contrib.nomes_fantasia);
	else{
		popup(NULL,"Não foi possível receber o nome fantasia");
	}

	//if(contrib.doc){
	//	gtk_combo_box_set_active(GTK_COMBO_BOX(doc_combo),1);
	//	gtk_entry_set_text(GTK_ENTRY(doc_ter_field), contrib.doc);
	//}else{
	//	popup(NULL,"Não foi possível receber o documento");
	//}

	if(contrib.ie){
		gtk_entry_set_text(GTK_ENTRY(inscr_ter_field), contrib.ie);
	}else{
		popup(NULL,"Não foi possível receber a inscrição estadual");
	}

	if(contrib.cep){
		gtk_entry_set_text(GTK_ENTRY(cep_ter_field), contrib.cep);
		gtk_widget_activate(cep_ter_field);
	}else{
		popup(NULL,"Não foi possível receber o cep");
	}

	if(contrib.xLgr){
		gtk_entry_set_text(GTK_ENTRY(address_ter_field), contrib.xLgr);
		gtk_widget_activate(address_ter_field);
	}else{
		popup(NULL,"Não foi possível receber o logradouro");
	}
	if(contrib.c_nro){
		gtk_entry_set_text(GTK_ENTRY(address_num_field), contrib.c_nro);
		gtk_widget_activate(address_num_field);
	}else{
		popup(NULL,"Não foi possível receber o numero");
	}

	if(contrib.xBairro){
		gtk_entry_set_text(GTK_ENTRY(bairro_ter_field), contrib.xBairro);
		gtk_widget_activate(bairro_ter_field);
	}else{
		popup(NULL,"Não foi possível receber o bairro");
	}

	if(contrib.xMun){
		gtk_entry_set_text(GTK_ENTRY(cidade_ter_field), contrib.xMun);
		gtk_widget_activate(cidade_ter_field);
	}else{
		popup(NULL,"Não foi possível receber o Município");
	}

	if(contrib.UF){
		gtk_entry_set_text(GTK_ENTRY(uf_ter_field), contrib.UF);
	}else{
		popup(NULL,"Não foi possível receber a UF");
	}

	for(int cont=0;cont<contrib.contatos_qnt; cont++){
		contato_add_item_filled(&contrib.contatos[cont]);
	}


}
