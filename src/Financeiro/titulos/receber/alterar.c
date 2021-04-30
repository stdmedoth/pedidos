int cad_rec_alterar_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;
  cad_rec_alterando = 1;

  if(cad_rec_code_fun()){
    cad_rec_cancelar_fun();
    return 1;
  }

  enum{
    CLIENTE,
    PEDIDO,
    BANCO,
    STATUS,
    CRIACAO,
    VENCIMENTO,
    VALOR
  };

  sprintf(query,"select tl.cliente, tl.pedido, p.banco, tl.status, DATE_FORMAT(p.data_criacao,'%%d/%%m/%%Y'),  DATE_FORMAT(p.data_vencimento,'%%d/%%m/%%Y'), p.valor from titulos as tl inner join parcelas_tab as p on tl.code = p.parcelas_id where tl.code = %i and p.posicao = %i and tl.tipo_titulo = %i",atoi(cad_rec_code_gchar), cad_rec_parcela_int, TP_TIT_REC);
  if(!(res=consultar(query))){
    popup(NULL,"Não foi possível pesquisar o título");
    cad_rec_cancelar_fun();
    return 1;
  }

  if(!(row=mysql_fetch_row(res))){
    popup(NULL,"Título não existe para ser alterado");
    cad_rec_cancelar_fun();
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(cad_rec_cli_entry),row[CLIENTE]);
  gtk_widget_activate(cad_rec_cli_entry);
  
  if(atoi(row[PEDIDO]))
    gtk_entry_set_text(GTK_ENTRY(cad_rec_ped_entry),row[PEDIDO]);

  if(row[BANCO])
    gtk_entry_set_text(GTK_ENTRY(cad_rec_bnc_entry),row[BANCO]);

  gtk_widget_activate(cad_rec_bnc_entry);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_rec_status_combo),atoi(row[STATUS]));
  gtk_entry_set_text(GTK_ENTRY(cad_rec_datacriacao_entry),row[CRIACAO]);
  gtk_entry_set_text(GTK_ENTRY(cad_rec_datavencimento_entry),row[VENCIMENTO]);
  gtk_entry_set_text(GTK_ENTRY(cad_rec_valor_entry),row[VALOR]);

  return 0;
}
