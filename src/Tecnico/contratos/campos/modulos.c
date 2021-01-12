int cntrats_modulos_fun(){

  contrato_modulos[CONTRATOS_CAD_MOD] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cntrats_cadastro_check));
  contrato_modulos[CONTRATOS_CMP_MOD] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cntrats_compras_check));
  contrato_modulos[CONTRATOS_FAT_MOD] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cntrats_faturamento_check));
  contrato_modulos[CONTRATOS_EST_MOD] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cntrats_estoque_check));
  contrato_modulos[CONTRATOS_FIN_MOD] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cntrats_financeiro_check));
  contrato_modulos[CONTRATOS_MARKT_MOD] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cntrats_marketing_check));
  contrato_modulos[CONTRATOS_REL_MOD] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cntrats_relatorios_check));
  
  return 0;
}
