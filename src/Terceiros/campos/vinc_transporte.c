int vinc_transp(){

  if(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(vinc_transporte_flag))){
    gtk_entry_set_text(GTK_ENTRY(transp_codigo_entry),"");
    gtk_entry_set_text(GTK_ENTRY(transp_nome_entry),"");
    gtk_entry_set_text(GTK_ENTRY(transp_cnpj_entry),"");
    gtk_entry_set_text(GTK_ENTRY(transp_ie_entry),"");
    gtk_entry_set_text(GTK_ENTRY(transp_logradouro_entry),"");
    gtk_entry_set_text(GTK_ENTRY(transp_cidade_entry),"");
    gtk_entry_set_text(GTK_ENTRY(transp_estado_entry),"");
    gtk_entry_set_text(GTK_ENTRY(transp_cep_entry),"");
    ter_com_entrega = 0;
    gtk_widget_hide(ter_entrega_box);
  }else{
    ter_com_entrega = 1;
    gtk_widget_show(ter_entrega_box);
  }
  return 0;
}
