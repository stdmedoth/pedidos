int cad_conta_fixa_intervalo(){

  gchar *formatado;
  conta_fix_int_int = gtk_spin_button_get_value(GTK_SPIN_BUTTON(conta_fix_int_entry));

  gtk_widget_grab_focus(conta_fix_valor_entry);
  return 0;
}
