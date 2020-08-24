int cad_bancos_tipoconta_fun(){

  cad_bancos_tipoconta_int = gtk_combo_box_get_active(GTK_COMBO_BOX(cad_bancos_tipoconta_combo));


  gtk_widget_grab_focus(cad_bancos_usuario_entry);
  return 0;
}
