int altera_und()
{
	char task[10];
	char query[MAX_QUERY_LEN];
	gchar *codigo;
	MYSQL_RES *estado;
	MYSQL_ROW campo;
	codigo = malloc(MAX_CODE_LEN);
	codigo = (gchar *)gtk_entry_get_text(GTK_ENTRY(code_und_field));
	sprintf(query,"select * from unidades where code = '%s';",codigo);
	g_print("query: %s\n",query);
	autologger(query);
	if(!(estado = consultar(query))){
		return 1;
	}

	if(!(campo = mysql_fetch_row(estado))){
		popup(NULL,"Unidade não existe para ser alterada");
		und_cancelar_fun();
		return 1;
	}

	alterando_und=1;
	gtk_entry_set_text(GTK_ENTRY(name_und_field),campo[1]);
	gtk_entry_set_text(GTK_ENTRY(sigla_und_field),campo[2]);
	gtk_entry_set_text(GTK_ENTRY(mult_und_field),campo[3]);
	gtk_combo_box_set_active(GTK_COMBO_BOX(medida_und_combo_box),atoi(campo[4]));

	gtk_widget_set_sensitive(code_und_field,FALSE);
	gtk_widget_set_sensitive(und_alterar_button,FALSE);
	gtk_widget_set_sensitive(psq_cad_und_button,FALSE);

	autologger(query);

	return 0;
}
