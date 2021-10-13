int prod_icmscst_fun(){
  prod_icmscst_gchar = (gchar*) gtk_combo_box_get_active_id (GTK_COMBO_BOX(prod_icmscst_combo));
  if(!prod_icmscst_gchar || !strlen(prod_icmscst_gchar)){
    prod_icmscst_gchar = strdup("NULL");
  }

  if(critica_real(prod_icmscst_gchar,NULL)){
    return 1;
  }


  return 0;
}
