int prod_precos_vltfat_fun(){

  prod_prc_vlrfat_gchar = (gchar *)gtk_entry_get_text(GTK_ENTRY(prod_prc_vlrfat_entry));

  if(strlen(prod_prc_vlrfat_gchar)<=0){
    popup(NULL,"Insira o preço");
    gtk_widget_grab_focus(prod_prc_vlrfat_entry);
    return 1;
  }

  if(critica_real(prod_prc_vlrfat_gchar, prod_prc_vlrfat_entry)){
    gtk_widget_grab_focus(prod_prc_vlrfat_entry);
    return 1;
  }

  gtk_widget_grab_focus(prod_prc_vlrvist_entry);
  return 0;
}
