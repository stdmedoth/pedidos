struct _cfe_ide{
  char CNPJ[15]; //software house
  char signAC[345];
  int numeroCaixa;
};

struct _cfe_emit{
  char CNPJ[15];
  char IE[15];
  int cRegTribISSQN;
  char indRatISSQN[2];
};

struct _cfe_dest{
  char CPF[15];
  char xNome[61];
  char xLgr[61];
  int nro;
  char xCpl[61];
  char xMun[61];
  char UF[3];
};

struct _cfe_produto{
  char cProd[61];
  char cEAN[15];
  char xProd[121];
  char NCM[9];
  char CFOP[5];
  char uCom[7];
  float qCom;
  float vUnCom;
  float vDesc;
  float vOutro;
};

struct _cfe_imposto{
  int cst;
};

struct _cfe_det{ //itens
  int nItem; //atributo
  struct _cfe_produto produto;
  struct _cfe_imposto imposto;
};


struct _CFe{
  struct _cfe_ide ide;
  struct _cfe_emit emit;
  struct _cfe_dest dest;
  struct _cfe_det det[990];
  xmlDoc *xml;
};


struct _CFe *get_cupons_from_orc();


xmlDoc *ini_cupom_xml(struct _CFe *cfe_struct);

xmlNode *add_ide_xml(struct _CFe *cfe_struct);

xmlNode *add_emit_xml(struct _CFe *cfe_struct);

xmlNode *criar_InfCFeNode(xmlDoc *xml);
