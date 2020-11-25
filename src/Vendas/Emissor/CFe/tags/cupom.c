struct _CFe *get_cupom_from_pdv(struct _pdv_venda_atual *pdv){

  if(!pdv)
    return NULL;

  struct _CFe *pCFe = malloc(sizeof(struct _CFe));
  pCFe = cupom_get_base_infos(pCFe);
  if(!pCFe)
    return NULL;

  if(!ini_cupom_xml(pCFe))
    return NULL;

  if(!add_ide_xml(pCFe)){
    return NULL;
  }

  if(!add_emit_xml(pCFe))
    return NULL;

  struct _terc_infos *destino = terceiros_get_terceiro(pdv->cliente);
  if(!destino)
    return NULL;

  if(!add_dest_xml(pCFe, destino))
    return NULL;

  if(!add_entrega_xml(pCFe, destino))
    return NULL;

  if(!pdv->cupom_atual->det)
    return NULL;

  pCFe->det = malloc(sizeof(struct _cfe_det));
  pCFe->det->itens_qnt = pdv->itens_qnt;
  pCFe->det->produtos = pdv->cupom_atual->det->produtos;
  pCFe->det->impostos = get_cupom_impostos(pCFe);

  if(!pCFe->det->impostos)
    return NULL;

  if(!add_dets_xml(pCFe))
    return NULL;

  return pCFe;
}
