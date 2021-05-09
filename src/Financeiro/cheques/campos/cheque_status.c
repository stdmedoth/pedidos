int cheque_status_fun(){
	cheque_status_int = atoi(gtk_combo_box_get_active_id(GTK_COMBO_BOX(cheque_status_combo)));
	
	gtk_widget_grab_focus(cheque_tipo_combo);
	return 0;
}