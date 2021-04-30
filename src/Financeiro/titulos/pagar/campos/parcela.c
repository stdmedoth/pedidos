int cad_pag_parcela_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;

  if(cad_pag_code_fun()){
    return 1;
  }

  cad_pag_parcela_int = atoi(gtk_entry_get_text(GTK_ENTRY(cad_pag_parcela_spin)));

  sprintf(query,"select tl.cliente, tl.pedido, tl.status, p.data_criacao, p.data_vencimento, p.valor from titulos as tl inner join terceiros as t inner join parcelas_tab as p on tl.code = p.parcelas_id and t.code = tl.cliente where tl.code = %i and p.posicao = %i and tl.tipo_titulo = %i",atoi(cad_pag_code_gchar), cad_pag_parcela_int, TP_TIT_PAG);

  if(!(res=consultar(query))){
    popup(NULL,"Não foi possível pesquisar o título");
    return 1;
  }

  if((row=mysql_fetch_row(res))){
    if( cad_pag_concluindo == 0 )
      cad_pag_alterar_fun();
    return 0;
  }else{
    if( cad_pag_concluindo == 0 ){
      cad_pag_alterando=0;
      gtk_entry_set_text(GTK_ENTRY(cad_pag_forn_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_pag_forn_nome_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_pag_ped_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_pag_valor_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_pag_datacriacao_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_pag_datavencimento_entry),"");
      gtk_combo_box_set_active(GTK_COMBO_BOX(cad_pag_status_combo),0);
    }
  }

  gtk_widget_grab_focus(cad_pag_forn_entry);
  return 0;
}
