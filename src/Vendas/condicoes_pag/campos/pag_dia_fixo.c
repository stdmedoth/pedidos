void pag_dia_fixo_fun(){
  pag_dia_fixo_int = (gint) gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pag_dia_fixo_check));

  if(pag_dia_fixo_int == 0)
    gtk_widget_set_sensitive(pag_init_spin,FALSE);
  else
    gtk_widget_set_sensitive(pag_init_spin,TRUE);

  return ;
}
