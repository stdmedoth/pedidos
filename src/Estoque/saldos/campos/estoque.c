int est_sald_est(){
	if(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(est_sld_est_combo)))
		est_sld_prod_est_int = atoi(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(est_sld_est_combo)));
	else{
		popup(NULL,"Escolha o estoque");
		return 1;
	}

	if(!est_sld_prod_est_int){
		popup(NULL,"Escolha o estoque");
		return 1;
	}
	return 0;
}
