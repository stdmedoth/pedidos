int pag_concluir_fun(){
  char query[MAX_QUERY_LEN];

  if(pag_cod_fun())
    return 1;
  if(pag_nome_fun())
    return 1;
  if(pag_tipo_fun())
    return 1;
  
  pag_dia_fixo_fun();

  if(pag_init_fun())
    return 1;
  if(pag_parc_fun())
    return 1;
  if(pag_parc_qnt_fun())
    return 1;

  if(pag_fpg_fun())
    return 1;

  if(pag_alterando == 0)
    sprintf(query,"insert into pag_cond(nome,tipo,forma_pag,dia_fixo_flag,init_dia,intervalos,qnt_parcelas) values('%s',%i,%s,%i,%i,%i,%i)",
    pag_nome_gchar, 
    pag_tipo_int, 
    pag_fpg_gchar, 
    pag_dia_fixo_int, 
    pag_init_int, 
    pag_parc_int, 
    pag_parc_qnt_int);
  else
    sprintf(query,"update pag_cond set nome = '%s', tipo = %i , forma_pag = %s, dia_fixo_flag = %i, init_dia = %i, intervalos = %i , qnt_parcelas = %i where code = %s",
    pag_nome_gchar, 
    pag_tipo_int, 
    pag_fpg_gchar,
    pag_dia_fixo_int, 
    pag_init_int,
    pag_parc_int, 
    pag_parc_qnt_int, 
    pag_cod_gchar);

  if(enviar_query(query)!=0){
    popup(NULL,"Erro ao criar modelo de parcelas");
    return 1;
  }

  if(pag_alterando == 0)
    popup(NULL,"Modelo de datas criado com sucesso");
  else
    popup(NULL,"Modelo de datas atualizado com sucesso");

  pag_cancelar_fun();

  return 0;
}
