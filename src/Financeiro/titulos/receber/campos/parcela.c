int cad_rec_parcela_fun(){

  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;

  if(cad_rec_code_fun()){
    
    return 1;
  }

  cad_rec_parcela_int = atoi(gtk_entry_get_text(GTK_ENTRY(cad_rec_parcela_spin)));

  sprintf(query,"select tl.cliente, tl.pedido, tl.status, p.data_criacao, p.data_vencimento, p.valor from titulos as tl inner join terceiros as t inner join parcelas_tab as p on tl.code = p.parcelas_id and t.code = tl.cliente where tl.code = %i and p.posicao = %i and tl.tipo_titulo = 1",atoi(cad_rec_code_gchar), cad_rec_parcela_int);

  if(!(res=consultar(query))){
    popup(NULL,"Não foi possível pesquisar o título");
    return 1;
  }

  if((row=mysql_fetch_row(res))){
    if( cad_rec_concluindo == 0 )
      cad_rec_alterar_fun();
    return 0;
  }else{
    if( cad_rec_concluindo == 0 ){
      cad_rec_alterando=0;
      gtk_entry_set_text(GTK_ENTRY(cad_rec_cli_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_rec_cli_nome_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_rec_ped_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_rec_valor_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_rec_valor_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_rec_datacriacao_entry),"");
      gtk_entry_set_text(GTK_ENTRY(cad_rec_datavencimento_entry),"");
      gtk_combo_box_set_active(GTK_COMBO_BOX(cad_rec_status_combo),0);
    }
  }

  gtk_widget_grab_focus(cad_rec_cli_entry);
  return 0;
}
