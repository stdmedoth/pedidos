int criar_xml_simples();
int criar_xml();

struct terceiro{
  char xNome[MAX_NAME_LEN];
  char IE[15];
  int CRT ; // 3
  char CNPJ[15];

  char xLgr[MAX_LOGR_LEN];
  int nro;
  char xBairro[MAX_BAIRRO_LEN];
  int cMun; //Código de município precisa ser válido e igual o  cMunFG
  char xMun[MAX_CID_LEN];
  char UF[3];
  char CEP[MAX_CEP_LEN];
  int cPais;
  char xPais[MAX_NAME_LEN];
};

struct item{

  //tagprod
  int item;
  char cEAN[MAX_CODE_LEN];
  char cEANTrib[MAX_CODE_LEN];
  char cProd[MAX_CODE_LEN];
  char NCM[MAX_CODE_LEN];
  float qCom;
  char CFOP[5];
  char uCom[5];
  float vUnCom;
  float vProd;
  char uTrib[5];
  float qTrib;
  float vUnTrib;
  float indTot;

  //tagimposto
  float vTotTrib;

  //tagICMS
  float vBC;
  float pICMS;
  float vICMS;

  //tagIPI
  char cEnqIPI[5];
  char CSTIPI[5];
  float vIPI;
  float vBCIPI;
  float pIPI;

  //tagPIS
  float CSTPIS[5];
  float vBCPIS;
  float pPIS;
  float vPIS;

  //tagCOFINSST
  float vCOFINS_ST;
  float vBCCOFINS_ST;
  float pCOFINS_ST;

  //tagCOFINS
  char CSTCOFINS;
  float vBCCOFINS;
  float pCOFINS;
  float vCOFINS;
  float qBCProdCOFINS;
  float vAliqProdCOFINS;

  //tagICMSTot
  float vBCTOTAIS;
  float vICMSTOTAIS;
  float vICMSDesonTOTAIS;
  float vBCSTTOTAIS;
  float vSTTOTAIS;
  float vProdTOTAIS;
  float vFreteTOTAIS;
  float vSegTOTAIS;
  float vDescTOTAIS;
  float vIITOTAIS;
  float vIPITOTAIS;
  float vPISTOTAIS;
  float vCOFINSTOTAIS;
  float vOutroTOTAIS;
  float vNFTOTAIS;
  float vTotTribTOTAIS;

};

struct criacao_xml{
  struct terceiro emissor;
  struct terceiro destinatario;

  struct item itens[MAX_PROD_ORC+1];
};
