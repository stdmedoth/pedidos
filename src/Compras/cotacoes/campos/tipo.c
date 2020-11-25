int cotac_tipo_fun(){
  cotac_publica_int = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cotac_publica_check));
  cotacao_new->publica = cotac_publica_int;
  return 0;
}
