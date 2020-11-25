int mkt_mail_setor_fun(){
  mkt_mail_setor_int = gtk_combo_box_get_active(GTK_COMBO_BOX(mkt_mail_setor_combo));
  gtk_widget_grab_focus(mkt_mail_corpo_view);
  return 0;
}
