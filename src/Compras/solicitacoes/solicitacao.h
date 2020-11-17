struct _requisicao_prod{
  int code;
  int produto;
  char descricao[MAX_OBS_LEN];
  char data[MAX_DATE_LEN];
  int prioridade;
  char data_evento[MAX_DATE_LEN];
  int status;
};

enum REQ_COLS{
  REQ_CODE_COL,
  REQ_PROD_COL,
  REQ_QNT_COL,
  REQ_DESCR_COL,
  REQ_DATA_COL,
  REQ_PRIOR_COL,
  REQ_DTEVENT_COL,
  REQ_STATUS_COL
};

enum REQ_PRIOR{
  REQ_BAIXA_PRIOR,
  REQ_MEDIA_PRIOR,
  REQ_ALTA_PRIOR
};

enum REQ_STATUS{
  REQ_PROD_PENDENTE,
  REQ_PROD_REPREVADO,
  REQ_PROD_APROVADO,
  REQ_PROD_CONCLUIDO
};

int solicitacao();

int req_prod_excluir_fun();
int req_prod_concluir_fun();
int req_prod_cancelar_fun();
int req_prod_alterar_fun();

char *req_prod_get_prior_name(int prior);

static int req_prod_concluindo=0, req_prod_alterando=0;
GtkWidget *req_prod_concluir_button,
*req_prod_alterar_button,
*req_prod_cancelar_button,
*req_prod_excluir_button;

gchar *req_prod_code_gchar,
*req_prod_prod_gchar,
*req_prod_qnt_gchar,
*req_prod_data_gchar,
*req_prod_dtevent_gchar,
*req_prod_descr_gchar;

gint req_prod_prori_int,
req_prod_qnt_int,
req_prod_status_int;

GtkWidget *req_prod_code_entry,
*req_prod_prodnome_entry,
*req_prod_prod_entry,
*req_prod_qnt_spin,
*req_prod_descr_text,
*req_prod_prori_combo,
*req_prod_data_entry,
*req_prod_dtevent_entry,
*req_prod_status_combo;
