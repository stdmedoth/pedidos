int cad_rec_cancelar_fun(){
  char task_code[MAX_CODE_LEN];

  cad_rec_alterando=0;
  cad_rec_concluindo=0;
  gtk_entry_set_text(GTK_ENTRY(cad_rec_cli_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_rec_cli_nome_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_rec_ped_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_rec_bnc_nome_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_rec_valor_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_rec_datacriacao_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_rec_datavencimento_entry),"");
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_rec_status_combo),0);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(cad_rec_parcela_spin),0);

  sprintf(task_code,"%i",tasker("titulos"));
  gtk_entry_set_text(GTK_ENTRY(cad_rec_code_entry),task_code);
  gtk_widget_grab_focus(cad_rec_cli_entry);
  return 0;
}
