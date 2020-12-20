int ordem_cmp_gerar(){

  if(ordem_cmp_code_fun())
    return 1;

  struct _ord_cmp *ordem = ordem_cmp_get(atoi(ordem_cmp_code_gchar));
  if(!ordem){
    popup(NULL,"Não foi possível receber informações da ordem");
    return 1;
  }

  if(gera_doc_ordcmp(ordem)){
    popup(NULL,"Erro ao gerar ordem de compra");
    return 1;
  }

  imp_opc = PDF_IMP;
  if(iniciar_impressao(ORD_CMP_PDF_FILE))
    return 1;

  popup(NULL,"Ordem de compra gerada com sucesso");
  return 0;
}
