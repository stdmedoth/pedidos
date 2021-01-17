int gerar_orc(){

	codigo_orc_gchar = (gchar *)gtk_entry_get_text(GTK_ENTRY(codigo_orc_entry));
	if(!strlen(codigo_orc_gchar)){
		popup(NULL,"Insira o código do orçamento");
		return 1;
	}

	struct _orc *orc = orc_get_orc(atoi(codigo_orc_gchar));
	if(!orc){
		file_logger("Não foi possível criar estrutura do orçamento! gerar_orc() -> orc_get_orc()");
		popup(NULL, "Não foi possível gerar o orçamento!");
		return 1;
	}

	orc_print_operation_fun(orc, GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG);

	return 0;
}
