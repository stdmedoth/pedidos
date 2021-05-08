int cheque_pgnt_fun(){
	cheque_pgntcode_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(cheque_pgntcode_entry));
	if(!strlen(cheque_pgntcode_gchar)){
		popup(NULL,"O pagador deve ser inserido");
		return 1;
	}

	struct _terc_infos *pagador = terceiros_get_simp_terceiro(atoi(cheque_pgntcode_gchar));
	if(!pagador){
		popup(NULL,"Não foi possível carregar pagador");
		return 1;
	}
	gtk_entry_set_text(GTK_ENTRY(cheque_pgntnome_entry), pagador->razao);
	gtk_widget_grab_focus(cheque_dtemissao_entry);
	return 0;
}