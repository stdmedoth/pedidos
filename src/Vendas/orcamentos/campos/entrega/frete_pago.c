int orc_transp_frete_pago_fun(){

  orc_transp_frete_pago_int = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(orc_transp_frete_pago_button));

  orc_transp_frete_pago_mudado = 1;
  if(orc_transp_frete_pago_int){
    gtk_widget_set_sensitive(orc_transp_valor_frete_entry,FALSE);
    gtk_widget_set_sensitive(orc_transp_desconto_frete_entry,FALSE);
  }else{
    gtk_widget_set_sensitive(orc_transp_valor_frete_entry,TRUE);
    gtk_widget_set_sensitive(orc_transp_desconto_frete_entry,TRUE);
  }
  orc_transp_valor_frete();
  orc_transp_desconto_frete();
  gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),1);

  return 0;
}
