enum ORD_CMP_COLS{
  ORD_CMP_CODE,
  ORD_CMP_FORN,
  ORD_CMP_DTEMIT,
  ORD_CMP_DTENTR,
  ORD_CMP_CONDPAG,
  ORD_CMP_STATUS,
  ORD_CMP_COLS_QNT
};

enum ORDCMP_ITENS_COLS{
  ORDCMP_ITEM_CODE,
  ORDCMP_ITEM_ORDID,
  ORDCMP_ITEM_REQ,
  ORDCMP_ITEM_COLS_QNT_
};

enum ORDCMP_STATUS{
  ORDCMP_N_GERADO,
  ORDCMP_N_ENVIADO,
  ORD_CMP_ENVIADO,
  ORD_CMP_CONCLUIDA,
  ORD_CMP_CANCELADA
};

int ordem_cmp();
struct _ord_cmp *ordem_cmp_get(int ordcmp_code);
int ordem_cmp_excluidos[MAX_PROD];
int ordem_cmp_excluido_pos;

struct _ord_cmp_item{
  struct _requisicao_prod *requisicao;
  struct _cad_produtos *produto;
};

struct _ord_cmp{

  int code;
  struct _terc_infos *fornecedor;
  int itens_qnt;
  struct _ord_cmp_item *itens;
  struct _condpag *condpag;

  float vlr_total;
  char *data_emissao;
  char *data_entrega;
  char *obs;
  int status;
};

GtkWidget *ordem_cmp_code_entry,
  *ordem_cmp_dtemissao_entry,
  *ordem_cmp_dtentrega_entry,
  *ordem_cmp_status_combo,
  *ordem_cmp_condpag_entry,
  *ordem_cmp_forncode_entry,
  *ordem_cmp_obs_view;

gchar *ordem_cmp_code_gchar,
  *ordem_cmp_dtemissao_gchar,
  *ordem_cmp_dtentrega_gchar,
  *ordem_cmp_condpag_gchar,
  *ordem_cmp_forncode_gchar,
  *ordem_cmp_obs_gchar;

gint ordem_cmp_status_int;
GtkWidget *ordem_cmp_condpagnome_entry,
  *ordem_cmp_fornnome_entry;

GtkWidget *ordem_cmp_codepsq_button,
  *ordem_cmp_condpagpsq_button,
  *ordem_cmp_fornpsq_button;


GtkWidget *ordem_cmp_concluir_button,
  *ordem_cmp_alterar_button,
  *ordem_cmp_excluir_button,
  *ordem_cmp_cancelar_button,
  *ordem_cmp_gerar_button,
  *ordem_cmp_enviar_button;

GtkWidget *ordem_cmp_req_treeview, *ordem_cmp_ordreq_treeview;

int ordem_cmp_alterando=0, ordem_cmp_concluindo=0;

int ordem_cmp_concluir_fun();
int ordem_cmp_alterar_fun();
int ordem_cmp_excluir_fun();
int ordem_cmp_cancelar_fun();
