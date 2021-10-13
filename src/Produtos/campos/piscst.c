int prod_piscst_fun(){

  prod_piscst_gchar = (gchar*) gtk_combo_box_get_active_id (GTK_COMBO_BOX(prod_piscst_combo));
  if(!prod_piscst_gchar || !strlen(prod_piscst_gchar)){
    prod_piscst_gchar = strdup("NULL");
  }
  prod_pisaliq_gchar = (gchar*) gtk_entry_get_text (GTK_ENTRY(prod_pisaliq_entry));
  if(!strlen(prod_pisaliq_gchar)){
    prod_pisaliq_gchar = strdup("0");
  }


  return 0;
}
