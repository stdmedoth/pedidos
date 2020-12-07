int mkt_mail_cancelar_fun(){
  GtkTextIter inicio, fim;
  GtkTextBuffer *buffer;
  char task[20];
  sprintf(task,"%i", tasker("emails_model"));

  mkt_email_concluindo = 0;
  mkt_email_alterando = 0;
  mkt_email_visualizando = 0;
  gtk_button_set_label(GTK_BUTTON(mkt_mail_concluir_button),"Concluir");
  gtk_entry_set_text(GTK_ENTRY(mkt_mail_code_entry), task);
  gtk_entry_set_text(GTK_ENTRY(mkt_mail_nome_entry), "");
  gtk_entry_set_text(GTK_ENTRY(mkt_mail_assunto_entry), "");
  gtk_combo_box_set_active(GTK_COMBO_BOX(mkt_mail_tipo_combo), 0);
  gtk_combo_box_set_active(GTK_COMBO_BOX(mkt_mail_setor_combo), 0);
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_header_view));
  gtk_text_buffer_set_text(buffer, "", 0);
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_corpo_view));
  gtk_text_buffer_set_text(buffer, "", 0);
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(mkt_mail_footer_view));
  gtk_text_buffer_set_text(buffer, "", 0);

  return 0;
}
