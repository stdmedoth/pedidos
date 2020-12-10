int prod_icmscst_fun(){
  prod_icmscst_gchar = (gchar*) gtk_combo_box_get_active_id (GTK_COMBO_BOX(prod_icmscst_combo));

  if(critica_real(prod_icmscst_gchar,NULL)){

  }


  return 0;
}
