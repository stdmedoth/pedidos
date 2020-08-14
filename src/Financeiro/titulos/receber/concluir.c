int cad_rec_concluir_fun(){
  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;
  cad_rec_concluindo = 1;

  if(cad_rec_code_fun()){
    return 1;
  }
  if(cad_rec_parcela_fun()){
    return 1;
  }
  if(cad_rec_cli_fun()){
    return 1;
  }
  if(cad_rec_ped_fun()){
    return 1;
  }
  if(cad_rec_datacriacao_fun()){
    return 1;
  }
  if(cad_rec_datavencimento_fun()){
    return 1;
  }
  if(cad_rec_valor_fun()){
    return 1;
  }
  if(cad_rec_status_fun()){
    return 1;
  }

  if(cad_rec_alterando == 0){

    if(cad_rec_parcela_int==0){
      sprintf(query,"insert into titulos(code,cliente,pedido,status, qnt_parcelas, tipo_titulo) values(%i,%i,%i,%i,0,1)",
      atoi(cad_rec_code_gchar),
      atoi(cad_rec_cli_gchar),
      atoi(cad_rec_ped_gchar),
      cad_rec_status_int);
      if(enviar_query(query)){
          popup(NULL,"Não foi possível criar Título");
          return 1;
      }

    }

    sprintf(query,"select * from titulos where code = %i",atoi(cad_rec_code_gchar));
    if(!(res=consultar(query))){
      popup(NULL,"Erro ao confirmar existencia do título");
      return 1;
    }
    if(!(row=mysql_fetch_row(res))){
      popup(NULL,"Título base não existente");
      return 1;
    }

    sprintf(query,"insert into parcelas_tab(parcelas_id, posicao, data_criacao, data_vencimento, valor) values(%i, %i, STR_TO_DATE('%s','%%d/%%m/%%Y'), STR_TO_DATE('%s','%%d/%%m/%%Y'), '%s')",
    atoi(cad_rec_code_gchar),
    cad_rec_parcela_int,
    cad_rec_datacriacao_gchar,
    cad_rec_datavencimento_gchar,
    cad_rec_valor_gchar);
  }
  else{
    sprintf(query,"update titulos set cliente = %i, pedido = %i, status = %i, qnt_parcelas = 0, tipo_titulo = 1 where code = %i",
    atoi(cad_rec_cli_gchar),
    atoi(cad_rec_ped_gchar),
    cad_rec_status_int,
    atoi(cad_rec_code_gchar));

    if(enviar_query(query)){
        popup(NULL,"Não foi atualizar Título");
        return 1;
    }

    sprintf(query,"update parcelas_tab set data_criacao = STR_TO_DATE('%s','%%d/%%m/%%Y'), data_vencimento = STR_TO_DATE('%s','%%d/%%m/%%Y'), valor = '%s' where parcelas_id = %i and posicao = %i",
    cad_rec_datacriacao_gchar,
    cad_rec_datavencimento_gchar,
    cad_rec_valor_gchar,
    atoi(cad_rec_code_gchar),
    cad_rec_parcela_int);
  }

  if(enviar_query(query)){
    if(cad_rec_alterando)
      popup(NULL,"Não foi possível atualizar parcela");
    else
      popup(NULL,"Não foi possível criar parcela");

    return 1;
  }

  if(cad_rec_alterando == 0)
    popup(NULL,"Título criado com sucesso");
  else
    popup(NULL,"Título atualizado com sucesso");

  cad_rec_cancelar_fun();
  return 0;
}
