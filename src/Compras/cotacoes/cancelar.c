int cotacao_cancelar_fun(){

  char task[12];
  sprintf(task,"%i",tasker("cotacoes"));
  gtk_entry_set_text(GTK_ENTRY(cotac_code_entry),task);
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(cotac_descricao_view));
  gtk_text_buffer_set_text(buffer,"",0);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cotac_status_combo),0);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cotac_publica_check),FALSE);
  gtk_entry_set_text(GTK_ENTRY(cotac_partc_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cotac_data_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cotac_validade_entry),"");
  gtk_combo_box_set_active(GTK_COMBO_BOX(cotac_partc_combo),0);

  cotac_alterando = 0;
  cotac_concluindo = 0;


  return 0;
}
