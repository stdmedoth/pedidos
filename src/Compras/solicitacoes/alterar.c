int req_prod_alterar_fun(){
  req_prod_alterando = 1;

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(req_prod_code_fun()){
    gtk_widget_grab_focus(req_prod_code_entry);
    return 1;
  }

  sprintf(query,"select code, produto, quantidade, descricao, DATE_FORMAT(data, '%%d/%%m/%%Y'), prioridade, DATE_FORMAT(data_evento, '%%d/%%m/%%Y'), status from prod_requisicoes where code = %s", req_prod_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar a solicitação");
    return 1;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Solicitação não existente");
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(req_prod_prod_entry),row[REQ_PROD_COL]);
  gtk_widget_activate(req_prod_prod_entry);
  gtk_entry_set_text(GTK_ENTRY(req_prod_qnt_spin),row[REQ_QNT_COL]);
  gtk_combo_box_set_active(GTK_COMBO_BOX(req_prod_prori_combo),atoi(row[REQ_PRIOR_COL]));

  GtkTextIter inicio, fim;
  GtkTextBuffer * buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(req_prod_descr_text));
  gtk_text_buffer_get_bounds(buffer, &inicio, &fim);
  gtk_text_buffer_set_text(buffer,row[REQ_DESCR_COL], strlen(row[REQ_DESCR_COL]));

  gtk_entry_set_text(GTK_ENTRY(req_prod_data_entry),row[REQ_DATA_COL]);
  gtk_entry_set_text(GTK_ENTRY(req_prod_dtevent_entry),row[REQ_DTEVENT_COL]);
  gtk_combo_box_set_active(GTK_COMBO_BOX(req_prod_status_combo),atoi(row[REQ_STATUS_COL]));
  gtk_widget_grab_focus(req_prod_prod_entry);

  return 0;
}
