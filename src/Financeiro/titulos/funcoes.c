int criar_titulo(struct _titulo *titulo){
  char query[MAX_QUERY_LEN];

  char pedido[12];
  if(titulo->pedido){
    sprintf(pedido, "%i", titulo->pedido);
  }else{
    sprintf(pedido, "NULL");
  }

  sprintf(query, 
    "insert into titulos(cliente, pedido, status, qnt_parcelas, tipo_titulo)"
    " values(%i, %s, %i, %i, %i)", 
    titulo->cliente, pedido, titulo->status, titulo->qnt_parcelas, titulo->tipo_titulo);
  if(enviar_query(query)){
    return 1;
  }
  int code_tit = mysql_insert_id(&conectar);
  for(int cont=0;cont<titulo->qnt_parcelas;cont++){

    if(titulo->parcelas[cont].banco && !titulo->parcelas[cont].banco->code){
      titulo->parcelas[cont].banco->ccode = strdup("NULL");
    }else{
      titulo->parcelas[cont].banco->ccode = inttochar(titulo->parcelas[cont].banco->code);
    }

    sprintf(query, 
    "insert into parcelas_tab(parcelas_id, posicao, banco, data_criacao, data_vencimento, valor)"
    " values(%i, %i, %s, '%s', '%s', %.2f)", 
    code_tit, 
    titulo->parcelas[cont].posicao, 
    titulo->parcelas[cont].banco->ccode,
    titulo->parcelas[cont].data_criacao,
    titulo->parcelas[cont].data_vencimento,
    titulo->parcelas[cont].valor);
    if(enviar_query(query)){
      return 1;
    } 
  }
  for(int cont=0;cont<titulo->qnt_baixas;cont++){

    int id_baixa = cont+1;
    sprintf(query, 
    "insert into baixas_titulos(parcelas_id, posicao, id_baixa, data_criacao, valor)"
    " values(%i, %i, %i, '%s', %.2f)", 
    code_tit, 
    titulo->parcelas[cont].posicao, 
    id_baixa,
    titulo->parcelas[cont].data_criacao,
    titulo->parcelas[cont].valor);
    if(enviar_query(query)){
      return 1;
    } 
  }

  return 0;
}

MYSQL_RES *titulos_get_pendentes(struct _titulo *titulos){
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos where status = %i",STAT_PENDENTE);
  if((titulos->result = consultar(query))){
    return NULL;
  }

  return titulos->result;
}

MYSQL_RES *titulos_get_baixados(struct _titulo *titulos){
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos where status = %i",STAT_QUITADO);
  if((titulos->result = consultar(query))){
    return NULL;
  }

  return titulos->result;
}

MYSQL_RES *titulos_get_todos(struct _titulo *titulos){
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos");
  if((titulos->result = consultar(query))){
    return NULL;
  }
  return titulos->result;
}

MYSQL_RES *titulos_por_cliente(struct _titulo *titulos){
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos where cliente = %i",titulos->cliente);
  if((titulos->result = consultar(query))){
    return NULL;
  }
  return titulos->result;
}

MYSQL_RES *titulos_por_cliente_status(struct _titulo *titulos){

  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from titulos where cliente = %i",titulos->cliente);
  if((titulos->result = consultar(query))){
    return NULL;
  }
  return titulos->result;
}

