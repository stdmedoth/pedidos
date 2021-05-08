int cheque_dtemissao_fun(){
	cheque_dtemissao_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cheque_dtemissao_entry));
	if(!strlen(cheque_dtemissao_gchar)){
		popup(NULL,"A data de emissão deve ser inserida");
		return 1;
	}
	gchar *formatado;
	if(!(formatado = formatar_data(cheque_dtemissao_gchar))){
	gtk_widget_grab_focus(cheque_dtemissao_entry);
	return 1;
	}
	cheque_dtemissao_gchar = strdup(formatado);
	gtk_entry_set_text(GTK_ENTRY(cheque_dtemissao_entry),formatado);


	gtk_widget_grab_focus(cheque_valor_entry);
	return 0;
}