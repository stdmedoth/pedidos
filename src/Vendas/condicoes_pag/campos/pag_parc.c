int pag_parc_fun(){

  pag_parc_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(pag_parc_spin));

  gtk_widget_grab_focus(pag_parc_qnt_spin);
  return 0;
}
