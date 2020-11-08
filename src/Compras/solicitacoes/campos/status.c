int req_prod_status_fun(){
  req_prod_status_int = gtk_combo_box_get_active(GTK_COMBO_BOX(req_prod_status_combo));

  return 0;
}
