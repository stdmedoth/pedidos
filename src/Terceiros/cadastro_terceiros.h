int alterando_ter=0;

GtkWidget *concluir_ter_buttom,
*alterar_ter_buttom,
*psq_ter_button,
*cancelar_ter_buttom,
*excluir_ter_buttom;

int inicializar_ter();
int  cad_terc();

void ter_consulta_contrib();

struct _terc_infos{
  int index;
  int code;
  char *razao;
  char *nomes_fantasia;
  char *ie;
  char *doc;
  int tipo_terc;
  gchar *relacionamento_desde;
  char *cep;
  char *xLgr;
  int i_nro;
  char *c_nro;
  char *xCpl;
  char *xBairro;
  char *xMun;
  char *UF;
  struct _Contato *contatos;
  int contatos_qnt;
};

struct _Terceiros{
  struct _terc_infos *terceiro;
  int qnt;
};

//variaveis referentes ao campos em campos/vars/campos_ter.h
static int concluindo_ter=0;
static int ter_com_entrega = 0;

enum TIPOS_TER{
  TIPO_TER_NULL,
  TIPO_TER_CLI,
  TIPO_TER_FRN,
  TIPO_TER_CLIFRN,
  TIPO_TER_TRSP
};

enum TER_SETOR{
  SETOR_INDUSTRIAL,
  SETOR_COMERCIAL,
  SETOR_PREST_SERV
};

enum{
  COD_TER_COL,
  COD_TER_NFE_COL,
  RAZ_TER_COL,
  NOMFAN_TER_COL,
  DOC_TER_COL,
  IE_TER_COL,
  TDOC_TER_COL,
  TIPC_TER_COL,
  TIPI_TER_COL,
  RELDSD_TER_COL,
  CEP_TER_COL,
  END_TER_COL,
  CPLMNT_TER_COL,
  BAIR_TER_COL,
  CID_TER_COL,
  UF_TER_COL,
  REND_TER_COL,
  TRUA_TER_COL,
  TER_TRSP_COD_COL,
  TER_TRSP_LOGR_COL,
  TER_TRSP_NUM_COL,
  TER_TRSP_BAIR_COL,
  TER_TRSP_CID_COL,
  TER_TRSP_UF_COL,
  TER_TRSP_CEP_COL,
  TER_TRSP_TEL_COL,
  TER_TRSP_OBS_COL,
  FLAG_MIN_FRT_PAG_COL,
  VLR_MIN_FRT_PAG_COL,
  PRAZ_TER_COL,
  OBS_TER_COL,
  DT_CRIAC_COL,
  DT_MODIF_COL,
};

#define TER_PAGE_ITENS 0
#define TER_PAGE_TRSP 1
#define TER_PAGE_OUTR 2

#define MAX_TERC_QNT 100;

enum TER_ORIG{
  TER_DENTRO_ESTADO,
  TER_FORA_ESTADO,
  TER_FORA_PAIS,
};

#include "campos.h"
