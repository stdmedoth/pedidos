int cntrats_ativo_fun(){
  tracelogger_set_func_name("cntrats_ativo_fun");
  cntrats_ativo_gint = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cntrats_ativo_check));

  return 0;
}
