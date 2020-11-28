int cntrats_cancelar_fun(){

  char task[12];
  sprintf(task, "%i", tasker("contratos"));
  gtk_entry_set_text(GTK_ENTRY(cntrats_code_entry), task);
  gtk_entry_set_text(GTK_ENTRY(cntrats_vencimento_entry), "");
  cntrats_concluindo=0;
  cntrats_alterando=0;

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_cadastro_check), FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_compras_check), FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_faturamento_check), FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_estoque_check), FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_financeiro_check), FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_marketing_check), FALSE);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cntrats_relatorios_check), FALSE);

  gtk_widget_grab_focus(cntrats_code_entry);

  return 0;
}
