struct _CFe *get_cupons_from_ped(struct _pedido *pedido){

  if(!pedido)
    return NULL;

  struct _CFe *pCFe = malloc(sizeof(struct _CFe));
  pCFe = cupom_get_base_infos(pCFe);

  if(!pCFe)
    return NULL;

  autologger("Base do cupom criada");
  if(!ini_cupom_xml(pCFe))
    return NULL;

  autologger("Xml do cupom inicializada");
  if(!add_ide_xml(pCFe))
    return NULL;

  autologger("Dados do software adicionados");
  if(!add_emit_xml(pCFe))
    return NULL;

  autologger("Dados do emitente adicionados");
  struct _terc_infos *destino = terceiros_get_terceiro(pedido->infos->cliente_code);
  if(!destino)
    return NULL;

  if(!add_dest_xml(pCFe, destino))
    return NULL;
  autologger("Dados do destinatário adicionados");

  if(!add_entrega_xml(pCFe, destino))
    return NULL;

  autologger("Dados da entrega adicionados");
  struct _cfe_det *detalhamentos = malloc(sizeof(struct _cfe_det));
  pCFe->det = detalhamentos;

  int itens_qnt = orcamentos_get_orc_itens_qnt(pedido->infos->ped_code);
  pCFe->det->itens_qnt = itens_qnt;
  struct _cfe_produto *itens = get_cupom_itens_from_orc(pedido->infos->ped_code);
  if(!itens)
    return NULL;
  detalhamentos->produtos = itens;

  struct _cfe_imposto *impostos = get_cupom_impostos(pCFe);
  if(!impostos)
    return NULL;
  detalhamentos->impostos = impostos;

  if(!add_dets_xml(pCFe))
    return NULL;
  autologger("Detalhamentos adicionados");

  if(!add_total_xml(pCFe))
    return NULL;
  autologger("Totais adicionados");

  if(!add_pgto_xml(pCFe))
    return NULL;
  autologger("Pagamentos adicionados");

  if(!add_infAdic_xml(pCFe))
    return NULL;

  autologger("informacoes adicionadas");

  autologger("XML gerado");
  return pCFe;
}
