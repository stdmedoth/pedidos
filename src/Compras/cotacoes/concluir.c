int cotacao_concluir_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  if(cotac_code_fun())
    return 1;

  if(cotac_data_fun())
    return 1;

  if(cotac_validade_fun())
    return 1;

  if(cotac_tipo_fun())
    return 1;

  if(cotac_status_fun())
    return 1;

  if(cotac_descricao_fun())
    return 1;

  if(cotac_alterando){
    sprintf(query,"update cotacoes set descricao = '%s', status = %i, publica = %i, data = STR_TO_DATE('%s', '%%d/%%m/%%Y'), validade = STR_TO_DATE('%s', '%%d/%%m/%%Y') where code = %i",
    cotacao_new->descricao, cotacao_new->status, cotacao_new->publica, cotacao_new->data, cotacao_new->validade, cotacao_new->code);
    if(enviar_query(query)){
      popup(NULL,"Não foi possivel atualizar cotação");
      return 1;
    }
  }else{
    sprintf(query,"insert into cotacoes(code, descricao,status,publica,data, validade) values( %i, '%s', %i, %i, STR_TO_DATE('%s', '%%d/%%m/%%Y'), STR_TO_DATE('%s', '%%d/%%m/%%Y'))",
    cotacao_new->code, cotacao_new->descricao, cotacao_new->status, cotacao_new->publica, cotacao_new->data, cotacao_new->validade);
    if(enviar_query(query)){
     popup(NULL,"Não foi possivel criar cotação");
     return 1;
    }
  }


  struct _Terceiros *Participantes = cotac_get_participantes();
  if(!Participantes->qnt){
    popup(NULL,"Não há participantes");
    return 1;
  }
  g_print("Iniciando analise dos itens\n");

  for(int participantes_pos=0; participantes_pos<Participantes->qnt; participantes_pos++){
    int participante_index = Participantes->terceiro[participantes_pos].index;
    g_print("Iniciando analise dos itens do fornecedor %i\n",Participantes->terceiro[participantes_pos].code);
    for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
      g_print("Iniciando analise dos itens do fornecedor %i index %i na posicao %i\n",Participantes->terceiro[participantes_pos].code, participante_index, cont);
      if(cotac_ativo[participante_index][cont] && cotac_produto_inserido[participante_index][cont]){

        if(cotat_itens_prod_fun(GTK_ENTRY(cotac_prod_cod_entry[participante_index][cont]), cont))
          return 1;

        if(cotat_itens_prc_fun(GTK_ENTRY(cotac_prod_cod_entry[participante_index][cont]), cont))
          return 1;

        if(cotat_itens_qnt_fun(GTK_ENTRY(cotac_prod_qnt_entry[participante_index][cont]), cont))
          return 1;

        if(cotac_alterando){
          sprintf(query,"update itens_cotacoes set produto = %i, qnt = %.2f, preco = %.2f where cotacoes_id = %i and participante_id = %i and code = %i",
          cotacao_new->cotacao_itens[participantes_pos][cont].produto,
          cotacao_new->cotacao_itens[participantes_pos][cont].quantidade,
          cotacao_new->cotacao_itens[participantes_pos][cont].valor,
          cotacao_new->code,
          Participantes->terceiro[participantes_pos].code,
          cont+1);
          if(enviar_query(query)){
            popup(NULL,"Não foi possivel atualizar cotação");
            return 1;
          }

        }else{
          sprintf(query,"insert into itens_cotacoes(cotacoes_id, participante_id, produto, qnt, preco) values( %i, %i, %i, %.2f, %.2f)",
          cotacao_new->code,
          Participantes->terceiro[participantes_pos].code,
          cotacao_new->cotacao_itens[participantes_pos][cont].produto,
          cotacao_new->cotacao_itens[participantes_pos][cont].quantidade,
          cotacao_new->cotacao_itens[participantes_pos][cont].valor);
          if(enviar_query(query)){
           popup(NULL,"Não foi possivel criar cotação");
           return 1;
          }
        }

      }
    }
  }

  if(cotac_alterando)
    popup(NULL,"Atualizado com sucesso");
  else
    popup(NULL,"Criado com sucesso");

  cotacao_cancelar_fun();
  return 0;
}
