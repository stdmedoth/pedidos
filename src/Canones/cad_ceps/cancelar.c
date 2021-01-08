int cad_ceps_cancelar_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  gtk_entry_set_text(GTK_ENTRY(cad_ceps_code_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_cep_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_descr_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_cid_code_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_cid_descr_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_bairro_entry),"");
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_uf_combo),0);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_ceps_uf_combo),0);
  cad_ceps_alterando=0;
  cad_ceps_concluindo=0;
  cad_ceps_consultando = 0;


  int logr_code = tasker("logradouro");
  gchar *code_task = malloc(MAX_CODE_LEN);
  sprintf(code_task, "%i", logr_code);

  gtk_widget_set_sensitive(cad_cep_consulta_button, TRUE);
  gtk_widget_set_sensitive(cad_cep_altera_button, TRUE);
  gtk_widget_set_sensitive(cad_ceps_cep_entry, TRUE);
  gtk_widget_set_sensitive(psq_cep_button, TRUE);
  gtk_entry_set_text(GTK_ENTRY(cad_ceps_code_entry),code_task);
  return 0;
}
