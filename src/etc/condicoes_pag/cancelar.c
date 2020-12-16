int pag_cancelar_fun(){

  char code[MAX_CODE_LEN];

  gtk_entry_set_text(GTK_ENTRY(pag_nome_entry),"");
  gtk_combo_box_set_active(GTK_COMBO_BOX(pag_tipo_combo),0);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pag_dia_fixo_check),0);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(pag_init_spin),1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(pag_parc_spin),1);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(pag_parc_qnt_spin),1);

  gtk_widget_set_sensitive(pag_init_spin,FALSE);
  gtk_widget_set_sensitive(pag_cod_entry,TRUE);
  gtk_widget_set_sensitive(pag_alterar_button,TRUE);
  gtk_widget_set_sensitive(pag_psq_cod_button,TRUE);

  pag_concluindo = 0;
  pag_alterando = 0;

  sprintf(code,"%i",tasker("pag_cond"));
  gtk_entry_set_text(GTK_ENTRY(pag_cod_entry),code);
  gtk_widget_grab_focus(pag_nome_entry);

  return 0;
}
