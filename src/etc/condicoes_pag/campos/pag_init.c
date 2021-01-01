int pag_init_fun(){

  pag_init_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(pag_init_spin));

  gtk_widget_grab_focus(pag_parc_spin);
  return 0;
}
