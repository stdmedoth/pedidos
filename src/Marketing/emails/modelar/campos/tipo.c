int mkt_mail_tipo_fun(){
  mkt_mail_tipo_int = gtk_combo_box_get_active(GTK_COMBO_BOX(mkt_mail_tipo_combo));
  gtk_widget_grab_focus(mkt_mail_tipo_combo);
  return 0;
}
