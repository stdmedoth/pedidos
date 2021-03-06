int cad_pag_alterar_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;
  cad_pag_alterando = 1;

  if(cad_pag_code_fun()){
    cad_pag_cancelar_fun();
    return 1;
  }

  sprintf(query,"select tl.cliente, t.razao, tl.pedido, tl.status, DATE_FORMAT(p.data_criacao,'%%d/%%m/%%Y'),  DATE_FORMAT(p.data_vencimento,'%%d/%%m/%%Y'), p.valor from titulos as tl inner join terceiros as t inner join parcelas_tab as p on tl.code = p.parcelas_id and tl.cliente = t.code where tl.code = %i and p.posicao = %i and tl.tipo_titulo = %i",atoi(cad_pag_code_gchar), cad_pag_parcela_int, TP_TIT_PAG);
  if(!(res=consultar(query))){
    popup(NULL,"Não foi possível pesquisar o título");
    cad_pag_cancelar_fun();
    return 1;
  }

  if(!(row=mysql_fetch_row(res))){
    popup(NULL,"Título não existe para ser alterado");
    cad_pag_cancelar_fun();
    return 1;
  }

  gtk_entry_set_text(GTK_ENTRY(cad_pag_cli_entry),row[0]);
  gtk_entry_set_text(GTK_ENTRY(cad_pag_cli_nome_entry),row[1]);
  if(atoi(row[2]))
    gtk_entry_set_text(GTK_ENTRY(cad_pag_ped_entry),row[2]);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cad_pag_status_combo),atoi(row[3]));
  gtk_entry_set_text(GTK_ENTRY(cad_pag_datacriacao_entry),row[4]);
  gtk_entry_set_text(GTK_ENTRY(cad_pag_datavencimento_entry),row[5]);
  gtk_entry_set_text(GTK_ENTRY(cad_pag_valor_entry),row[6]);

  return 0;
}
