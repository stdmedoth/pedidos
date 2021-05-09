int cheque_tipo_fun(){
	cheque_tipo_int = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(cheque_tipo_combo)));
	
	gtk_widget_grab_focus(cheque_concluir_button);
	return 0;
}