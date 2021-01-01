void ter_consulta_contrib(){

	struct _terc_infos contrib;

	contrib.doc = NULL;
	contrib.razao = NULL;
	contrib.ie = NULL;
	contrib.cep = NULL;

	gchar *cnpj = (gchar*)gtk_entry_get_text(GTK_ENTRY(doc_ter_field));
	if(!strlen(cnpj)){
		popup(NULL,"Insira o cnpj");
		return ;
	}
	
	if(!(cnpj = format_only_num(cnpj))){
		popup(NULL,"Não foi possível formatar cnpj");
		return ;
	}
	contrib.doc = strdup(cnpj);

	if(consulta_contrib_wnd(&contrib)){
		return ;
	}

	if(contrib.razao)
		gtk_entry_set_text(GTK_ENTRY(name_ter_field), contrib.razao);
	else{
		popup(NULL,"Não foi possível receber o nome");
	}

	if(contrib.doc){
		gtk_combo_box_set_active(GTK_COMBO_BOX(doc_combo),1);
		gtk_entry_set_text(GTK_ENTRY(doc_ter_field), contrib.doc);
	}else{
		popup(NULL,"Não foi possível receber o documento");
	}

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

}
