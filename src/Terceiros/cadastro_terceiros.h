int inicializar_ter();
int  cad_terc();

struct _terc_infos{
  int code;
  char *razao;
  char *ie;
  char *doc;
  int tipo_terc;
  char *cep;
};

struct _Terceiros{
  struct _terc_infos *terceiro;
  int qnt;
};

//variaveis referentes ao campos em campos/vars/campos_ter.h

static int concluindo_ter=0;
static int ter_com_entrega = 0;

enum{
  COD_TER_COL,
  COD_TER_NFE_COL,
  RAZ_TER_COL,
  DOC_TER_COL,
  IE_TER_COL,
  TDOC_TER_COL,
  TIPC_TER_COL,
  TIPI_TER_COL,
  CEP_TER_COL,
  END_TER_COL,
  CPLMNT_TER_COL,
  BAIR_TER_COL,
  CID_TER_COL,
  UF_TER_COL,
  REND_TER_COL,
  TRUA_TER_COL
};
/*
#define TEL_TER_COL 16
#define CTEL_TER_COL 17
#define CEL_TER_COL 18
#define CCEL_TER_COL 19
#define EMAIL_TER_COL 20
#define CEMAIL_TER_COL 21
*/

#define TRSP_COD_COL 16
#define TRSP_LOGR_COL 17
#define TRSP_NUM_COL 18
#define TRSP_BAIR_COL 19
#define TRSP_CID_COL 20
#define TRSP_UF_COL 21
#define TRSP_CEP_COL 22
#define TRSP_TEL_COL 23
#define TRSP_OBS_COL 24

#define FLAG_MIN_FRT_PAG_COL 25
#define VLR_MIN_FRT_PAG_COL 26

#define PRAZ_TER_COL 27
#define OBS_TER_COL 28


#define TER_PAGE_ITENS 0
#define TER_PAGE_TRSP 1
#define TER_PAGE_OUTR 2

#include "campos.h"
