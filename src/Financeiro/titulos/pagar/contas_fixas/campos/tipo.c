int cad_conta_fixa_tipo(){

  conta_fix_tipo_int = gtk_combo_box_get_active(GTK_COMBO_BOX(conta_fix_int_combo));

  if(conta_fix_tipo_int == CONTA_FIXA_NULO && conta_fix_tipo_int >= CONTA_FIXA_TQNT){
    popup(NULL,"Escolha um tipo de intervalo");
    return 1;
  }

  gtk_widget_grab_focus(conta_fix_int_combo);
  return 0;
}
