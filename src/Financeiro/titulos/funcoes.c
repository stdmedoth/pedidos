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

