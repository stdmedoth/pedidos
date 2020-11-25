int req_prod_concluir_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  req_prod_concluindo = 1;
  if(req_prod_code_fun()){
    gtk_widget_grab_focus(req_prod_code_entry);
    return 1;
  }

  if(req_prod_prod_fun()){
    gtk_widget_grab_focus(req_prod_prod_entry);
    return 1;
  }

  if(req_prod_qnt_fun()){
    gtk_widget_grab_focus(req_prod_qnt_spin);
    return 1;
  }

  if(req_prod_descr_fun()){
    gtk_widget_grab_focus(req_prod_descr_text);
    return 1;
  }
  if(req_prod_data_fun()){
    gtk_widget_grab_focus(req_prod_prori_combo);
    return 1;
  }

  if(req_prod_priori_fun()){
    gtk_widget_grab_focus(req_prod_prori_combo);
    return 1;
  }

  if(req_prod_priori_fun()){
    gtk_widget_grab_focus(req_prod_prori_combo);
    return 1;
  }

  if(req_prod_status_fun()){
    gtk_widget_grab_focus(req_prod_status_combo);
    return 1;
  }
  if(!req_prod_alterando){
    sprintf(query,"insert into prod_requisicoes(code, produto, quantidade, descricao, data, prioridade, data_evento, status) values(%s, %s, %s, '%s', STR_TO_DATE('%s', '%%d/%%m/%%Y'), %i, now(), %i)",
    req_prod_code_gchar, req_prod_prod_gchar, req_prod_qnt_gchar, req_prod_descr_gchar, req_prod_data_gchar, req_prod_prori_int, req_prod_status_int);
  }else{
    sprintf(query,"update prod_requisicoes set produto = %s, quantidade = %s,  descricao = '%s', data = STR_TO_DATE('%s', '%%d/%%m/%%Y'), prioridade = %i, data_evento = now(), status = %i where code = %s",
    req_prod_prod_gchar, req_prod_qnt_gchar, req_prod_descr_gchar, req_prod_data_gchar, req_prod_prori_int, req_prod_status_int, req_prod_code_gchar);
  }

  if(enviar_query(query)){
    popup(NULL,"Não foi possível enviar requisicao");
    return 1;
  }
  if(!req_prod_alterando)
    popup(NULL,"Requisição criada com sucesso");
  else
    popup(NULL,"Requisição atualizada com sucesso");

  req_prod_cancelar_fun();

  return 0;
}
