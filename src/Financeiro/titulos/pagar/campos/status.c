int cad_pag_status_fun(){
  cad_pag_status_int = gtk_combo_box_get_active(GTK_COMBO_BOX(cad_pag_status_combo));

  return 0;
}
