int code_terc(){
	char code[10];
	char task[8];
	MYSQL_RES *vetor;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	codigos_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(code_ter_field));

	if(strlen(codigos_ter)<=0){
		g_print("Codigo terceiro deve ser inserido\n");
		popup(NULL,"Por favor, insira um Código para o terceiro!");
		gtk_widget_grab_focus(GTK_WIDGET(code_ter_field));
		return 1;
	}

	sprintf(query,"select code from terceiros where code = '%s'",codigos_ter);
	if(!(vetor = consultar(query))){
		popup(NULL,"Erro ao consultar terceiro");
		return 1;
	}
	if(alterando_ter==0){
		if((row = mysql_fetch_row(vetor))){
			altera_ter();
		}
	}
	gtk_widget_grab_focus(GTK_WIDGET(doc_ter_field));

	return 0;
}
