int operacao_orc_orc(){

  operacao_orc_int = gtk_combo_box_get_active(GTK_COMBO_BOX(operacao_orc_combo));

  if(operacao_orc_int == VENDA || operacao_orc_int == DEV_COMPRA)
    sinal_operacao_int = '-';
  else
  if(operacao_orc_int == DEV_VENDA || operacao_orc_int == COMPRA)
    sinal_operacao_int = '+';
  else
    popup(NULL,"erro ao buscar operação atual");

  return 0;
}
