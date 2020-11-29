int pdv_fecha_cupom_fun(){
  gtk_label_set_text(GTK_LABEL(pdv_acaoatual_label), "Fechando Cupom...");

  pdv_venda_atual->cliente = 1;

  struct _CFe *cfe = get_cupom_from_pdv(pdv_venda_atual);
  if(!cfe){
    popup(NULL, "Erro na criação do cupom");
    return 1;
  }

  char *cupom_path = malloc( sizeof(char) * strlen(CUPONS_XMLS_DIR) + MAX_NAME_LEN);
  sprintf(cupom_path,"%scupom_caixa.xml",CUPONS_XMLS_DIR);
  FILE *xml = fopen(cupom_path,"w");
  if(!xml){
    popup(NULL,"Arquivo do cupom não pode ser aberto");
    return 1;
  }

  if(cfe->xml){
    autologger("Exportando\n");
    if(xmlDocDump( xml,	cfe->xml ) == -1){
      if(PopupBinario("O cupom não pode ser emitido, Cancelar movimentos?", "Sim! reverta os movimentos", "Não! mantenha os sem o cupom")){
        return 0;
      }
    }
  }
  fclose(xml);

  popup(NULL,"Venda feita com sucesso");
  return 0;
}
