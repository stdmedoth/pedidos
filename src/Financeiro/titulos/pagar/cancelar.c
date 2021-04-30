int cad_pag_cancelar_fun(){
  char task_code[MAX_CODE_LEN];

  cad_pag_alterando=0;
  cad_pag_concluindo=0;
  gtk_entry_set_text(GTK_ENTRY(cad_pag_forn_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_pag_forn_nome_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_pag_ped_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_pag_valor_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_pag_datacriacao_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_pag_datavencimento_entry),"");
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_pag_status_combo),0);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(cad_pag_parcela_spin),0);

  sprintf(task_code,"%i",tasker("titulos"));
  gtk_entry_set_text(GTK_ENTRY(cad_pag_code_entry),task_code);
  gtk_widget_grab_focus(cad_pag_forn_entry);
  return 0;
}
