int cntrats_concluir_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  cntrats_concluindo = 1;

  if(cntrats_code_fun())
    return 1;

  if(cntrats_modulos_fun())
    return 1;

  if(cntrats_ativo_fun())
    return 1;
    
  if(cntrats_vencimento_fun())
    return 1;

  sprintf(query, "SELECT * FROM contratos WHERE code = %s", cntrats_code_gchar);
  if(!(res = consultar(query))){
    popup(NULL, "Não foi possível buscar contrato");
    return 1;
  }

  if(!(row = mysql_fetch_row(res))){
    sprintf(query,"insert into contratos values(%s, %i, %i, %i, %i, %i, %i, %i, %i, STR_TO_DATE('%s', '%%d/%%m/%%Y'))",
      cntrats_code_gchar,
      contrato_modulos[CONTRATOS_CAD_MOD],
      contrato_modulos[CONTRATOS_CMP_MOD],
      contrato_modulos[CONTRATOS_FAT_MOD],
      contrato_modulos[CONTRATOS_EST_MOD],
      contrato_modulos[CONTRATOS_FIN_MOD],
      contrato_modulos[CONTRATOS_MARKT_MOD],
      contrato_modulos[CONTRATOS_REL_MOD],
      cntrats_ativo_gint,
      cntrats_vencimento_gchar
    );
    if(enviar_query(query)){
      popup(NULL,"Erro ao criar contrato");
      return 1;
    }
  }else{
    sprintf(query,"update contratos set cadastro = '%i', compras = %i, faturamento = %i, estoque  = %i, financeiro = %i, marketing = %i, relatorios = %i, ativo = %i, data_vencimento = STR_TO_DATE('%s', '%%d/%%m/%%Y') where code = %s",
      contrato_modulos[CONTRATOS_CAD_MOD],
      contrato_modulos[CONTRATOS_CMP_MOD],
      contrato_modulos[CONTRATOS_FAT_MOD],
      contrato_modulos[CONTRATOS_EST_MOD],
      contrato_modulos[CONTRATOS_FIN_MOD],
      contrato_modulos[CONTRATOS_MARKT_MOD],
      contrato_modulos[CONTRATOS_REL_MOD],
      cntrats_ativo_gint,
      cntrats_vencimento_gchar,
      cntrats_code_gchar
    );
    if(enviar_query(query)){
      popup(NULL,"Erro ao atualizar contrato");
      return 1;
    }
  }

  popup(NULL,"Contrato atualizado com sucesso");
  cntrats_cancelar_fun();
  return 0;
}
