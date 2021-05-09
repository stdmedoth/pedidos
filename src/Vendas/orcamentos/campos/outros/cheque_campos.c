int orc_cheque_finan_code(){
	orc_cheque_code_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_code_entry));
	if(!strlen(orc_cheque_code_gchar)){
		popup(NULL,"Código cheque não inserido");
		return 1;
	}
	
	struct _cheque *cheque = cheque_get_simple_cheque(atoi(orc_cheque_code_gchar)); 
	if(cheque){
		gtk_entry_set_text(GTK_ENTRY(orc_cheque_conta_entry), cheque->conta);
		gtk_entry_set_text(GTK_ENTRY(orc_cheque_banco_entry), inttochar(cheque->banco->code));
		gtk_widget_activate(orc_cheque_banco_entry);
		gtk_entry_set_text(GTK_ENTRY(orc_cheque_serie_entry), cheque->serie);
		gtk_entry_set_text(GTK_ENTRY(orc_cheque_numero_entry), cheque->numero);
		gtk_entry_set_text(GTK_ENTRY(orc_cheque_pagante_entry), inttochar(cheque->pagante->code));
		gtk_widget_activate(orc_cheque_pagante_entry);
		gtk_entry_set_text(GTK_ENTRY(orc_cheque_emissao_entry), cheque->data_emissao);
	}
	gtk_widget_grab_focus(orc_cheque_banco_entry);
	return 0;
}

int orc_cheque_finan_banco(){
	orc_cheque_banco_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_banco_entry));
	if(!strlen(orc_cheque_banco_gchar)){
		popup(NULL,"Banco do cheque não inserido");
		return 1;
	}
	struct _banco *banco = get_banco(atoi(orc_cheque_banco_gchar));
	if(!banco){
		popup(NULL,"Não foi possível receber banco do cheque");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(orc_cheque_nomebanco_entry), banco->nome);
	gtk_widget_grab_focus(orc_cheque_serie_entry);
	return 0;
}

int orc_cheque_finan_serie(){
	orc_cheque_serie_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_serie_entry));
	if(!strlen(orc_cheque_serie_gchar)){
			popup(NULL,"Série do cheque não inserido");
		return 1;
	}
	gtk_widget_grab_focus(orc_cheque_conta_entry);
	return 0;
}

int orc_cheque_finan_conta(){
	orc_cheque_conta_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_conta_entry));
	if(!strlen(orc_cheque_conta_gchar)){
		popup(NULL,"Conta do cheque não inserido");
		return 1;
	}
	gtk_widget_grab_focus(orc_cheque_numero_entry);
	return 0;
}


int orc_cheque_finan_numero(){
	orc_cheque_numero_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_numero_entry));
	if(!strlen(orc_cheque_numero_gchar)){
		popup(NULL,"Número do cheque não inserido");
		return 1;
	}
	gtk_widget_grab_focus(orc_cheque_pagante_entry);
	return 0;
}


int orc_cheque_finan_pagante(){
	orc_cheque_pagante_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_pagante_entry));
	if(!strlen(orc_cheque_pagante_gchar)){
		popup(NULL,"Pagante do cheque não inserido");
		return 1;
	}

	struct _terc_infos *pagante = terceiros_get_simp_terceiro(atoi(orc_cheque_pagante_gchar));
	if(!pagante){
		popup(NULL,"Não foi possível buscar pagante do cheque");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(orc_cheque_nomepagante_entry), pagante->razao);
	gtk_widget_grab_focus(orc_cheque_emissao_entry);
	return 0;
}

int orc_cheque_finan_emissao(){
	orc_cheque_emissao_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(orc_cheque_emissao_entry));
	if(!strlen(orc_cheque_emissao_gchar)){
		popup(NULL,"Data de Emissão do cheque não inserido");
		return 1;
	}
	gchar *formatado = NULL;
	if(!(formatado = formatar_data(orc_cheque_emissao_gchar))){
    	gtk_widget_grab_focus(orc_cheque_emissao_entry);
    	return 1;
  	}
	  gtk_entry_set_text(GTK_ENTRY(orc_cheque_emissao_entry),formatado);

	return 0;
}


