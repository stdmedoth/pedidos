int consulta_contrib(const gchar *formated_cnpj, struct _terc_infos *contrib){

  struct _consulta_cnpj *consulta_receitaws = consulta_contrib_receitaws(formated_cnpj);
  if(!consulta_receitaws){
    popup(NULL,"Não foi possível efetuar a consulta");
    return 1;
  }
  contrib->doc = strdup(consulta_receitaws->cnpj);
  contrib->razao = strdup(consulta_receitaws->xNome);
  contrib->nomes_fantasia = strdup(consulta_receitaws->NFantasia);
  contrib->ie = strdup(consulta_receitaws->IE);

  contrib->cep = strdup(consulta_receitaws->CEP);
  contrib->xLgr = strdup(consulta_receitaws->xLgr);
  contrib->c_nro = strdup(consulta_receitaws->nro);
  contrib->xBairro = strdup(consulta_receitaws->xBairro);
  contrib->xMun = strdup(consulta_receitaws->xMun);

  contrib->contatos = malloc(sizeof(struct _Contato) * consulta_receitaws->contatos_qnt);
  contrib->contatos_qnt = consulta_receitaws->contatos_qnt;
  for(int cont=0;cont<consulta_receitaws->contatos_qnt; cont++){
      contrib->contatos[cont] = consulta_receitaws->contato[cont];
  }


  return 0;
}
