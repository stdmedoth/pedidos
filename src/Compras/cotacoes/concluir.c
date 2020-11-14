int cotacao_concluir_fun(){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  cotac_concluindo = 1;

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

  sprintf(query,"select * from cotacoes where code = %i",
  cotacao_new->code);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível verificar existencia da cotação");
    return 1;
  }
  if((row = mysql_fetch_row(res))){

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
  int itens_inseridos=0;
  for(int participantes_pos=0; participantes_pos<Participantes->qnt; participantes_pos++){

    int participante_index = Participantes->terceiro[participantes_pos].index;
    itens_inseridos = cotac_get_req_qnt(participante_index);

    sprintf(query,"select * from cotacoes_participantes where cotacoes_id = %i and participante = %i",
    cotacao_new->code,
    Participantes->terceiro[participantes_pos].code);
    if(!(res = consultar(query))){
      popup(NULL,"Não foi possível verificar existencia de Partipante");
      return 1;
    }
    if(!(row = mysql_fetch_row(res))){
      sprintf(query,"insert into cotacoes_participantes(cotacoes_id, participante) values (%i, %i)",
      cotacao_new->code,
      Participantes->terceiro[participantes_pos].code);
      if(enviar_query(query)){
        popup(NULL,"Não foi possivel inserir participante");
        return 1;
      }
    }

    g_print("Concluindo para os itens do fornecedor %i\n",Participantes->terceiro[participantes_pos].code);
    if(itens_inseridos){
      for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
        g_print("Concluindo para o fornecedor %i index %i na posicao %i\n",Participantes->terceiro[participantes_pos].code, participante_index, cont);
        if(cotac_ativo[participante_index][cont] && cotac_produto_inserido[participante_index][cont]){
          gchar *id = malloc(12);
          sprintf(id,"%i",Participantes->terceiro[participantes_pos].code);
          if(!gtk_combo_box_set_active_id(GTK_COMBO_BOX(cotac_partc_combo),id)){
            popup(NULL,"Index de um dos participantes não encontrado");
            return 1;
          }

          if(cotat_itens_prod_fun(GTK_ENTRY(cotac_prod_cod_entry[participante_index][cont]), cont))
            return 1;

          if(cotat_itens_qnt_fun(GTK_ENTRY(cotac_prod_qnt_entry[participante_index][cont]), cont))
            return 1;

          if(cotat_itens_prc_fun(GTK_ENTRY(cotac_prod_prc_entry[participante_index][cont]), cont))
            return 1;

          if(cotac_alterando){
            sprintf(query,"select * from itens_cotacoes where cotacoes_id = %i and participante_id = %i and item_index = %i",
            cotacao_new->code,
            Participantes->terceiro[participantes_pos].code,
            cont);

            if(!(res = consultar(query))){
              popup(NULL,"Não foi possível analisar existencia do item");
              return 1;
            }
            if((row = mysql_fetch_row(res))){
              sprintf(query,"update itens_cotacoes set requisicao = %i, qnt = %.2f, preco = %.2f where cotacoes_id = %i and participante_id = %i and item_index = %i",
              cotacao_new->cotacao_itens[participantes_pos][cont].requisicao,
              cotacao_new->cotacao_itens[participantes_pos][cont].quantidade,
              cotacao_new->cotacao_itens[participantes_pos][cont].valor,

              cotacao_new->code,
              Participantes->terceiro[participantes_pos].code,
              cont);
              if(enviar_query(query)){
                popup(NULL,"Não foi possivel atualizar cotação");
                return 1;
              }
            }else{
              sprintf(query,"insert into itens_cotacoes(item_index, cotacoes_id, participante_id, requisicao, qnt, preco) values( %i, %i, %i, %i, %.2f, %.2f)",
              cont,
              cotacao_new->code,
              Participantes->terceiro[participantes_pos].code,
              cotacao_new->cotacao_itens[participantes_pos][cont].requisicao,
              cotacao_new->cotacao_itens[participantes_pos][cont].quantidade,
              cotacao_new->cotacao_itens[participantes_pos][cont].valor);
              if(enviar_query(query)){
               popup(NULL,"Não foi inserir item na cotação");
               return 1;
              }
            }
          }else{
            sprintf(query,"insert into itens_cotacoes(item_index, cotacoes_id, participante_id, requisicao, qnt, preco) values( %i, %i, %i, %i, %.2f, %.2f)",
            cont,
            cotacao_new->code,
            Participantes->terceiro[participantes_pos].code,
            cotacao_new->cotacao_itens[participantes_pos][cont].requisicao,
            cotacao_new->cotacao_itens[participantes_pos][cont].quantidade,
            cotacao_new->cotacao_itens[participantes_pos][cont].valor);
            if(enviar_query(query)){
             popup(NULL,"Não foi inserir item na cotação");
             return 1;
            }
          }
        }
        while (g_main_context_pending(NULL))
          g_main_context_iteration(NULL,FALSE);
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
