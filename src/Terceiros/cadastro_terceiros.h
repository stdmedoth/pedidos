int alterando_ter=0;

GtkWidget *concluir_ter_buttom,
*alterar_ter_buttom,
*psq_ter_button,
*cancelar_ter_buttom,
*excluir_ter_buttom;

int inicializar_ter();
int  cad_terc();

struct _terc_infos *terceiros_get_simp_terceiro(int code);
struct _terc_infos *terceiros_get_terceiro(int code);
void ter_consulta_contrib();

struct _terc_infos{
  int index;
  int code;
  char *razao;
  char *ie;
  char *doc;
  int tipo_terc;
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
enum {
  TER_TRSP_COD_COL=16,
  TER_TRSP_LOGR_COL=17,
  TER_TRSP_NUM_COL=18,
  TER_TRSP_BAIR_COL=19,
  TER_TRSP_CID_COL=20,
  TER_TRSP_UF_COL=21,
  TER_TRSP_CEP_COL=22,
  TER_TRSP_TEL_COL=23,
  TER_TRSP_OBS_COL=24,
};


#define FLAG_MIN_FRT_PAG_COL 25
#define VLR_MIN_FRT_PAG_COL 26

#define PRAZ_TER_COL 27
#define OBS_TER_COL 28


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
