int cad_rec_status_fun(){
  cad_rec_status_int = gtk_combo_box_get_active(GTK_COMBO_BOX(cad_rec_status_combo));

  return 0;
}
