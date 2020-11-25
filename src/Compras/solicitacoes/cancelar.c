int req_prod_cancelar_fun(){

  char task_code[12];
  sprintf(task_code,"%i",tasker("prod_requisicoes"));
  gtk_entry_set_text(GTK_ENTRY(req_prod_code_entry),task_code);
  gtk_entry_set_text(GTK_ENTRY(req_prod_prod_entry),"");
  gtk_entry_set_text(GTK_ENTRY(req_prod_prodnome_entry),"");
  GtkTextIter inicio, fim;
  GtkTextBuffer * buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(req_prod_descr_text));
  gtk_text_buffer_get_bounds(buffer, &inicio, &fim);
  gtk_text_buffer_set_text(buffer,"",0);
  gtk_entry_set_text(GTK_ENTRY(req_prod_qnt_spin),"1");
  gtk_combo_box_set_active(GTK_COMBO_BOX(req_prod_prori_combo),0);
  gtk_entry_set_text(GTK_ENTRY(req_prod_data_entry),"");
  gtk_entry_set_text(GTK_ENTRY(req_prod_dtevent_entry),"");
  gtk_combo_box_set_active(GTK_COMBO_BOX(req_prod_status_combo),0);

  gtk_widget_grab_focus(req_prod_prod_entry);
  req_prod_concluindo = 0;
  req_prod_alterando = 0;
  return 0;
}
