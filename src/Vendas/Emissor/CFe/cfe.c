#include "tags/dest.c"
#include "tags/detalhamentos.c"
#include "tags/emit.c"
#include "tags/entrega.c"
#include "tags/ide.c"
#include "tags/impostos.c"
#include "tags/itens.c"
#include "tags/total.c"
#include "tags/pagamento.c"
#include "tags/informacoes.c"
#include "tags/pedidos.c"
#include "tags/cupom.c"

struct _CFe *cupom_get_base_infos(struct _CFe *cfe_struct){

  strcpy(cad_software_house.CNPJ,"23115714000140");

  strcpy(cad_software_house.signAC, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                                    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                                    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                                    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                                    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                                    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

  strcpy(cfe_struct->ide.CNPJ,cad_software_house.CNPJ);
  strcpy(cfe_struct->ide.signAC,cad_software_house.signAC);
  struct _maquina *maquina = maquinas_get_atual();

  if(!maquina)
    return NULL;
  struct _caixa *caixa = caixa_get_aberto(maquina);
  if(!caixa)
    return NULL;

  if(caixa->status == CAIXA_ABERTO){
    sprintf(cfe_struct->ide.numeroCaixa, "%03d" , caixa->id);
  }
  else{
    sprintf(cfe_struct->ide.numeroCaixa, "000");
  }

  strcpy(cfe_struct->emit.CNPJ,cad_emp_strc.CNPJ);
  strcpy(cfe_struct->emit.IE,cad_emp_strc.IE);
  strcpy(cfe_struct->emit.IM,cad_emp_strc.IM);
  strcpy(cfe_struct->emit.cRegTribISSQN, cad_emp_strc.cRegTribISSQN);
  strcpy(cfe_struct->emit.indRatISSQN, cad_emp_strc.indRatISSQN);

  return cfe_struct;
}

xmlDoc *ini_cupom_xml(struct _CFe *cfe_struct){
  if(!cfe_struct)
    return NULL;
  xmlChar *version = (xmlChar *)"1.0";
  xmlDoc *cfe_xml = xmlNewDoc(version);
  if(cfe_xml){
    xmlNode *cfe = xmlNewNode(NULL,(xmlChar *)"CFe");
    xmlDocSetRootElement(cfe_xml,cfe);
    cfe_struct->xml = cfe_xml;
  }

  return cfe_xml;
}

xmlNode *criar_InfCFeNode(xmlDoc *xml){
  if(!xml)
    return NULL;
  xmlNode *CFe = xmlDocGetRootElement(xml);
  xmlNode *infCFe = NULL;
  xmlXPathContextPtr contxt = xmlXPathNewContext(xml);
  xmlXPathObjectPtr node_contxt= xmlXPathEval((xmlChar*)"/CFe/infCFe[1]",contxt);

  if(node_contxt &&
    node_contxt->nodesetval &&
    node_contxt->nodesetval->nodeNr &&
    node_contxt->nodesetval->nodeTab){

    g_print("Node encontrado\n");
    infCFe = node_contxt->nodesetval->nodeTab[0];
  }

  if(!infCFe){
    infCFe = xmlNewNode(NULL, (xmlChar*)"infCFe");
    //xmlSetProp(infCFe, (xmlChar*)"Id", (xmlChar*)"1");
    xmlSetProp(infCFe, (xmlChar*)"versaoDadosEnt", (xmlChar*)"0.06");
    xmlAddChild(CFe,infCFe);
  }

  return infCFe;
}
