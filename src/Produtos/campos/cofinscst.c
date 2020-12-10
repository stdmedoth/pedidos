int prod_cofinscst_fun(){
  prod_cofinscst_gchar = (gchar*) gtk_combo_box_get_active_id (GTK_COMBO_BOX(prod_cofinscst_combo));

  prod_cofinsaliq_gchar = (gchar*) gtk_entry_get_text (GTK_ENTRY(prod_cofinsaliq_entry));
  if(!strlen(prod_cofinsaliq_gchar)){
    prod_cofinsaliq_gchar = strdup("0");
  }

  return 0;
}
