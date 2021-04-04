int pag_fpg_fun(){
	pag_fpg_gchar = (gchar*) gtk_combo_box_get_active_id(GTK_COMBO_BOX(pag_fpg_combo));
	if(!strlen(pag_fpg_gchar)){
		popup(NULL,"Tipo de pagamento inválido");
		return 1;
	}
	return 0;
}