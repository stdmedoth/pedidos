int orc_cheque_finan_code(){
	orc_cheque_code_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_code_entry));
	if(!strlen(orc_cheque_code_gchar)){

	}

	return 0;
}

int orc_cheque_finan_banco(){
	orc_cheque_banco_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_banco_entry));
	if(!strlen(orc_cheque_banco_gchar)){

	}
	return 0;
}


int orc_cheque_finan_conta(){
	orc_cheque_conta_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_conta_entry));
	if(!strlen(orc_cheque_conta_gchar)){

	}
	return 0;
}


int orc_cheque_finan_serie(){
	orc_cheque_serie_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_serie_entry));
	if(!strlen(orc_cheque_serie_gchar)){

	}
	return 0;
}


int orc_cheque_finan_numero(){
	orc_cheque_numero_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_numero_entry));
	if(!strlen(orc_cheque_numero_gchar)){

	}
	return 0;
}


int orc_cheque_finan_pagante(){
	orc_cheque_pagante_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_cheque_pagante_entry));
	if(!strlen(orc_cheque_pagante_gchar)){

	}
	return 0;
}

int orc_cheque_finan_emissao(){
	orc_cheque_emissao_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(orc_cheque_emissao_entry));
	if(!strlen(orc_cheque_emissao_gchar)){

	}
	return 0;
}


