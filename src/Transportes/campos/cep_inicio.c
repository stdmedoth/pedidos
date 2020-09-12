int trsp_cad_cepini_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  char *endereco_resumido = malloc(MAX_CID_LEN+MAX_LOGR_LEN+MAX_BAIRRO_LEN);

  trsp_cad_cepini_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(trsp_cad_cepini_entry));

  if(!strlen(trsp_cad_cepini_gchar)){
    if( !trsp_cad_rec_alteracao )
      popup(NULL,"O CEP de inicio precisa ser inserido");
    return 1;
  }

  if(strlen(trsp_cad_cepini_gchar)!=CEP_LEN)
  {
    popup(NULL,"Insira o CEP com formato indicado");
    return 1;
  }

  sprintf(query,"select l.descricao, l.descricao_bairro, c.descricao, l.UF from logradouro as l inner join cidade as c on l.id_cidade = c.id_cidade where CEP = '%s'",trsp_cad_cepini_gchar);
  if(!(res = consultar(query)))
  {
    popup(NULL,"Erro ao consultar CEP");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    if(!trsp_cad_concluindo  && !trsp_cad_rec_alteracao)
      cep_nao_existente_fun(trsp_cad_cepini_gchar);
  }else{
    if(row[0] && row[1] && row[2] && row[3])
    sprintf(endereco_resumido,"%s, %s, %s, %s",row[0],row[1],row[2],row[3]);
    gtk_entry_set_text(GTK_ENTRY(trsp_cad_endini_entry),endereco_resumido);
  }


  gtk_widget_grab_focus(trsp_cad_cepentr_entry);
  return 0;
}