struct _cfe_ide{
  char CNPJ[15]; //software house
  char signAC[345];
  char numeroCaixa[15];
};

struct _cfe_emit{
  char CNPJ[15];
  char IE[15];
  char IM[15];
  char cRegTribISSQN[10];
  char indRatISSQN[10];
};

struct _cfe_dest{
  int id;
  char CPF[15];
  char xNome[61];
  char xLgr[61];
  int nro;
  char xCpl[61];
  char xMun[61];
  char UF[3];
};

struct _cfe_produto{
  char *cProd;
  char *nItem;
  char *cEAN;
  char *xProd;
  char *NCM;
  char *ICMSCST;
  char *PISCST;
  char *PISAliq;
  char *COFINSCST;
  char *COFINSAliq;
  char *Orig;
  char *CFOP;
  char *uCom;
  char *qCom;
  char *vUnCom;
  char *indRegra;
  char *vDesc;
  char *vOutro;
  char *ctotal;
  double dtotal;
};

struct _cfe_imposto{
  char *ICMSCST; //ICMS00
  char *Orig;   // estado
  char *pICMS;  //tributacao

  char *PISCST;
  char *PISAliq;
  char *PISvBC;

  char *COFINSCST;
  char *COFINSAliq;
  char *COFINSvBC;

  char *COFINSSTvBC; //base do cofins para st
  char *COFINSSTpCOFINS; //valor do cofins para st
};

struct _cfe_det{ //itens
  int nItem; //atributo
  int itens_qnt;
  gchar *ctotal;
  double dtotal;
  struct _cfe_produto *produtos;
  struct _cfe_imposto *impostos;
};


struct _CFe{
  struct _cfe_ide ide;
  struct _cfe_emit emit;
  struct _cfe_dest dest;
  struct _cfe_det *det;
  xmlDoc *xml;
};

struct _CFe *get_cupons_from_orc();


struct _cfe_produto *get_cupom_itens_from_orc(int orc_code);

xmlDoc *ini_cupom_xml(struct _CFe *cfe_struct);

struct _CFe *get_base_infos(struct _CFe *cfe_struct);

xmlNode *add_entrega_xml(struct _CFe *cfe_struct, struct _terc_infos *destinatario);

struct _cfe_produto *get_cupom_itens(int orc_code);

xmlNode *add_dest_xml(struct _CFe *cfe_struct, struct _terc_infos *destinatario);

xmlNode *add_dets_xml(struct _CFe *cfe_struct);

xmlNode *add_ide_xml(struct _CFe *cfe_struct);

xmlNode *add_emit_xml(struct _CFe *cfe_struct);

xmlNode *criar_InfCFeNode(xmlDoc *xml);

struct _CFe *cupom_get_base_infos(struct _CFe *cfe_struct);


#define MAX_CUPOM_ITENS 990
