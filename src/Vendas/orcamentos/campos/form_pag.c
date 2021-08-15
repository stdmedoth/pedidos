int orc_form_pag_fun(){
  orc_form_pag_code = (gchar*)gtk_combo_box_get_active_id(GTK_COMBO_BOX(orc_form_pag_combo));
	if(!strlen(orc_form_pag_code)){
		popup(NULL,"Tipo de pagamento inválido");
		return 1;
	}

  orc_parcelas.forma_pagamento = get_forma_pagamento(atoi(orc_form_pag_code));
  if(!orc_parcelas.forma_pagamento){
    popup(NULL,"Não foi possível receber forma de pagamento");
    return 1;
  }

  if(orc_fields_from_orc_parcelas())
    return 1;
    
  orc_form_pag_changed = 1;
  return 0;
}
