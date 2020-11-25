int cotac_status_fun(){
  cotac_status_int = gtk_combo_box_get_active(GTK_COMBO_BOX(cotac_status_combo));
  cotacao_new->status = cotac_status_int;
  return 0;
}
