int relat_fix_vnd_quebra_fun(){

  relat_fix_vnd_quebra_flag =  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(relat_fix_vnd_quebra_check));

  if(relat_fix_vnd_quebra_flag)
    relat_fix_vnd_quebra_int = gtk_combo_box_get_active(GTK_COMBO_BOX(relat_fix_vnd_quebra_combo));
  else
    relat_fix_vnd_quebra_int = 0;

  return 0;
}
