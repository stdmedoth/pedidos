int orc_srv_transp_cancelar_fun(){

  char trsp_code[12];
  sprintf(trsp_code,"%i",tasker("servico_transporte"));
  gtk_entry_set_text(GTK_ENTRY(orc_srv_transp_entry),trsp_code);
  gtk_entry_set_text(GTK_ENTRY(orc_transp_codigo_entry),"");
  gtk_entry_set_text(GTK_ENTRY(orc_transp_nome_entry),"");
  gtk_entry_set_text(GTK_ENTRY(orc_transp_cnpj_entry),"");
  gtk_entry_set_text(GTK_ENTRY(orc_transp_ie_entry),"");
  gtk_entry_set_text(GTK_ENTRY(orc_transp_logradouro_entry),"");
  gtk_entry_set_text(GTK_ENTRY(orc_transp_bairro_entry),"");
  gtk_entry_set_text(GTK_ENTRY(orc_transp_num_entry),"");
  gtk_entry_set_text(GTK_ENTRY(orc_transp_cidade_entry),"");
  gtk_entry_set_text(GTK_ENTRY(orc_transp_estado_entry),"");
  gtk_entry_set_text(GTK_ENTRY(orc_transp_cep_entry),"");
  gtk_widget_grab_focus(GTK_WIDGET(orc_transp_codigo_entry));
  orc_com_entrega = 0;
  alterando_transp = 0;

  return 0;
}
