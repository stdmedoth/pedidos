int cad_bancos_cancelar_fun(){

  char task[MAX_CODE_LEN];
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_nome_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_conta_entry),"");
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_bancos_tipoconta_combo),0);
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_agencia_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_usuario_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_doc_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_saldoini_entry),"");
  cad_bancos_alterando = 0;
  cad_bancos_concluindo = 0;
  gtk_widget_grab_focus(cad_bancos_nome_entry);
  sprintf(task,"%i",tasker("bancos"));
  gtk_entry_set_text(GTK_ENTRY(cad_bancos_code_entry),task);
  return 0;
}
