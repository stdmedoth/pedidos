int calcular_div(char *chave_nfe){
  //calcula digito verificado da chave nfe
  char formatador[5];
  int multiplicadores[] = {2,3,4,5,6,7,8,9};
  int soma_ponderada = 0;
  int i = 42, resto, resultado;

  while (i >= 0) {
    for (int m=0; m<multiplicadores[m] && i>=0; m++) {
          sprintf(formatador,"%c",chave_nfe[i]);
          soma_ponderada += atoi(formatador) * multiplicadores[m];
          i--;
        }
      }
      resto = soma_ponderada % 11;
      if (resto == 0 || resto == 1) {
        return 0;

      } else {
      return 11 - resto;
    }

    return 1;
}

int criar_xml(){

  FILE *ter_infos_file;
  GSubprocess *processo=NULL;
  GError *erro=NULL;
  MYSQL_ROW row;
  MYSQL_RES *res;
  char *formated_cnpj,
  *formated_data,
  chave_nfe[46],
  pre_chave_nfe[44],
  numNF[10],numPed[9],
  ano[3];

  char formatador[5];
  int somatorio;

  int uf_code = 35;
  int modelo_nf = 55;
  int serie_nf = 1;
  int tp_emiss_nf = 1;
  int numNFInt = 1;
  int numPedInt = 1;
  int tpNFTagInt = 1; // saida
  int idDestInt = 1; // operacao interna
  int tpImpTagInt = 0; // sem DANFE

  sprintf(numNF,"%09d",numNFInt);
  sprintf(numPed,"%08d",numPedInt);

  GDateTime  *gdate;
  GTimeZone *timezone;
  timezone = g_time_zone_new_identifier(NULL);
  gdate = g_date_time_new_now(timezone);
  formated_data = g_date_time_format(gdate,"%Y-%m-%dT%T%:z");
  if(!formated_data){
    popup(NULL,"Não foi possivel criar formato de datas para xml");
    return 1;
  }

  sprintf(formatador,"%d",g_date_time_get_year(gdate));
  sprintf(ano,"%c%c",formatador[2], formatador[3]);

  xmlDocPtr doc;
  doc = xmlNewDoc((xmlChar *)"1.0");
  xmlNodePtr NFeTag = xmlNewNode(NULL, (xmlChar *)"NFe");
  xmlNodePtr infNFeTag = xmlNewNode(NULL, (xmlChar *)"infNFe");
  xmlNodePtr ideTag = xmlNewNode(NULL, (xmlChar *)"ide");

  xmlNodePtr cUFTag = xmlNewNode(NULL, (xmlChar *)"cUF");
  xmlNodePtr cNFTag = xmlNewNode(NULL, (xmlChar *)"cNF");
  xmlNodePtr natOpTag = xmlNewNode(NULL, (xmlChar *)"natOp");
  xmlNodePtr modTag = xmlNewNode(NULL, (xmlChar *)"mod");
  xmlNodePtr serieTag = xmlNewNode(NULL, (xmlChar *)"serie");
  xmlNodePtr nNFTag = xmlNewNode(NULL, (xmlChar *)"nNF");
  xmlNodePtr dhEmiTag = xmlNewNode(NULL, (xmlChar *)"dhEmi");
  xmlNodePtr dhSaiEntTag = xmlNewNode(NULL, (xmlChar *)"dhSaiEnt");
  xmlNodePtr tpNFTag = xmlNewNode(NULL, (xmlChar *)"tpNF");
  xmlNodePtr idDestTag = xmlNewNode(NULL, (xmlChar *)"idDest");
  xmlNodePtr cMunFGTag = xmlNewNode(NULL, (xmlChar *)"cMunFG");
  xmlNodePtr tpImpTag = xmlNewNode(NULL, (xmlChar *)"tpImp");
  xmlNodePtr tpEmisTag = xmlNewNode(NULL, (xmlChar *)"tpEmis");
  xmlNodePtr cDVTag = xmlNewNode(NULL, (xmlChar *)"cDV");
  xmlNodePtr tpAmbTag = xmlNewNode(NULL, (xmlChar *)"tpAmb");
  xmlNodePtr finNFeTag = xmlNewNode(NULL, (xmlChar *)"finNFe");
  xmlNodePtr indFinalTag = xmlNewNode(NULL, (xmlChar *)"indFinal");
  xmlNodePtr indPresTag = xmlNewNode(NULL, (xmlChar *)"indPres");
  xmlNodePtr procEmiTag = xmlNewNode(NULL, (xmlChar *)"procEmiTag");
  xmlNodePtr verProcTag = xmlNewNode(NULL, (xmlChar *)"verProcTag");

  xmlNodePtr EmitTag = xmlNewNode(NULL, (xmlChar *)"emit");
  xmlNodePtr DestTag = xmlNewNode(NULL,(xmlChar *)"dest");

  xmlNodePtr EmitxNomeTag = xmlNewNode(NULL,(xmlChar *)"xNome");
  xmlNodePtr EmitCNPJTag = xmlNewNode(NULL,(xmlChar *)"CNPJ");

  xmlNodePtr EmitenderEmitTag = xmlNewNode(NULL,(xmlChar *)"enderEmit");
  xmlNodePtr EmitxLgrTag = xmlNewNode(NULL,(xmlChar *)"xLgr");
  xmlNodePtr EmitnroTag = xmlNewNode(NULL,(xmlChar *)"nro");
  xmlNodePtr EmitxBairroTag = xmlNewNode(NULL,(xmlChar *)"xBairro");
  xmlNodePtr EmitxMunTag = xmlNewNode(NULL,(xmlChar *)"xMun");
  xmlNodePtr EmitUFTag = xmlNewNode(NULL,(xmlChar *)"UF");
  xmlNodePtr EmitcPaisTag = xmlNewNode(NULL,(xmlChar *)"cPais");
  xmlNodePtr EmitxPaisTag = xmlNewNode(NULL,(xmlChar *)"xPais");

  xmlNodePtr DestxNomeTag = xmlNewNode(NULL,(xmlChar *)"xNome");
  xmlNodePtr DestCNPJTag = xmlNewNode(NULL,(xmlChar *)"CNPJ");

  xmlNodePtr DestenderEmitTag = xmlNewNode(NULL,(xmlChar *)"enderDest");
  xmlNodePtr DestxLgrTag = xmlNewNode(NULL,(xmlChar *)"xLgr");
  xmlNodePtr DestnroTag = xmlNewNode(NULL,(xmlChar *)"nro");
  xmlNodePtr DestxBairroTag = xmlNewNode(NULL,(xmlChar *)"xBairro");
  xmlNodePtr DestxMunTag = xmlNewNode(NULL,(xmlChar *)"xMun");
  xmlNodePtr DestUFTag = xmlNewNode(NULL,(xmlChar *)"UF");
  xmlNodePtr DestcPaisTag = xmlNewNode(NULL,(xmlChar *)"cPais");
  xmlNodePtr DestxPaisTag = xmlNewNode(NULL,(xmlChar *)"xPais");

  FILE *pre_nfe_xml;
  struct criacao_xml xml;

  strcpy(xml.emissor.xNome,cad_emp_strc.xNome);

  if(format_cnpj_num(cad_emp_strc.CNPJ))
    strcpy(xml.emissor.CNPJ,format_cnpj_num(cad_emp_strc.CNPJ));
  else{
    popup(NULL,"Falha ao formatar cnpj");
    return 1;
  }

  strcpy(xml.emissor.xLgr,cad_emp_strc.xLgr);

  xml.emissor.nro = cad_emp_strc.nro;

  strcpy(xml.emissor.xBairro,cad_emp_strc.xBairro);

  strcpy(xml.emissor.xMun,cad_emp_strc.xMun);

  strcpy(xml.emissor.UF,cad_emp_strc.UF);

  xml.emissor.cPais = cad_emp_strc.cPais;

  strcpy(xml.emissor.xPais,cad_emp_strc.xPais);

  xmlNodeSetContent(EmitxNomeTag,(xmlChar *)xml.emissor.xNome);
  xmlNodeSetContent(EmitCNPJTag,(xmlChar *)xml.emissor.CNPJ);

  xmlAddChild(EmitTag,EmitxNomeTag);
  xmlAddChild(EmitTag,EmitCNPJTag);

  xmlAddChild(ideTag,cUFTag);
  xmlNodeSetContent(cUFTag,(xmlChar *)"35");

  sprintf(pre_chave_nfe,"%02d%s%02d%s%02d%02d%s%02d%s",
  uf_code,
  ano,
  g_date_time_get_month(gdate),
  xml.emissor.CNPJ,
  modelo_nf,
  serie_nf,
  numNF,
  tp_emiss_nf,
  numPed);

  sprintf(chave_nfe,"%s%d",pre_chave_nfe, calcular_div(pre_chave_nfe));

  xmlAddChild(ideTag,cNFTag);
    xmlNodeSetContent(cNFTag,(xmlChar *)numPed);

  xmlAddChild(ideTag,natOpTag);
  xmlNodeSetContent(natOpTag,(xmlChar *)"Venda de mercadoria adquirida ou recebida de terceiros.");

  xmlAddChild(ideTag,modTag);
  xmlNodeSetContent(modTag,(xmlChar *)"55");

  xmlAddChild(ideTag,serieTag);
  xmlNodeSetContent(serieTag,(xmlChar *)"1");

  xmlAddChild(ideTag,nNFTag);
  xmlNodeSetContent(nNFTag,(xmlChar *)numNF);

  xmlAddChild(ideTag,dhEmiTag);
  xmlNodeSetContent(dhEmiTag,(xmlChar *)formated_data);

  xmlAddChild(ideTag,dhSaiEntTag);
  xmlNodeSetContent(dhSaiEntTag,(xmlChar *)formated_data);

  //0=Entrada;
  //1=Saída
  xmlAddChild(ideTag,tpNFTag);
  sprintf(formatador,"%i",tpNFTagInt);
  xmlNodeSetContent(tpNFTag,(xmlChar *)formatador);

  //1=Operação interna;
  //2=Operação interestadual;
  //3=Operação com exterior.
  sprintf(formatador,"%i",idDestInt);
  xmlAddChild(ideTag,idDestTag);
  xmlNodeSetContent(idDestTag,(xmlChar *)formatador);

  //código IBGE do município
  sprintf(formatador,"%i",xml.emissor.cMun);
  xmlAddChild(ideTag,cMunFGTag);
  xmlNodeSetContent(cMunFGTag,(xmlChar *)formatador);

  sprintf(formatador,"%i",tpImpTagInt);
  xmlAddChild(ideTag,tpImpTag);
  xmlNodeSetContent(tpImpTag,(xmlChar *)formatador);

  xmlAddChild(ideTag,tpEmisTag);
  xmlNodeSetContent(tpEmisTag,(xmlChar *)"1");

  sprintf(formatador,"%i",calcular_div(pre_chave_nfe));
  xmlAddChild(ideTag,cDVTag);
  xmlNodeSetContent(cDVTag,(xmlChar *)formatador);

  xmlAddChild(ideTag,tpAmbTag);
  xmlNodeSetContent(tpAmbTag,(xmlChar *)"2");//homologacao

  xmlAddChild(ideTag,finNFeTag);
  xmlAddChild(ideTag,indFinalTag);
  xmlAddChild(ideTag,indPresTag);
  xmlAddChild(ideTag,procEmiTag);
  xmlAddChild(ideTag,verProcTag);

  xmlAddChild(infNFeTag,ideTag);

  xmlAddChild(NFeTag,infNFeTag);

  xmlDocSetRootElement(doc,NFeTag);

  pre_nfe_xml = fopen(SCRPT_NFE_INFOS,"w");
  if(!pre_nfe_xml){
    popup(NULL,"Não foi possivel criar Pré XML");
    return 1;
  }
  if(xmlDocDump(pre_nfe_xml,doc)<=0){
    popup(NULL,"O arquivo de comunicaçao teve erro na exportação XML");
    return 1;
  }

  return 0;
}


int preencher_campos(){


  return 0;
}

int chamar_emissor_xml(){


  return 0;
}
