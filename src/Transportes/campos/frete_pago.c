int trsp_cad_frtpag_fun(){

  trsp_cad_frtpag_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(trsp_cad_frtpag_check));
  if(trsp_cad_frtpag_gint){
    gtk_widget_set_sensitive(trsp_cad_vlrfrt_entry, FALSE);
    gtk_widget_set_sensitive(trsp_cad_descfrt_entry, FALSE);
  }else{
    gtk_widget_set_sensitive(trsp_cad_vlrfrt_entry, TRUE);
    gtk_widget_set_sensitive(trsp_cad_descfrt_entry, TRUE);
  }

  return 0;
}
