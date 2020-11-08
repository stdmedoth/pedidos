struct _requisicao_prod{
  int code;
  int produto;
  char descricao[MAX_OBS_LEN];
  char data[MAX_DATE_LEN];
  int prioridade;
  char data_evento[MAX_DATE_LEN];
  int status;
};

enum{
  REQ_PROD_PENDENTE,
  REQ_PROD_REPREVADO,
  REQ_PROD_APROVADO,
  REQ_PROD_CONCLUIDO
};

int solicitacao();

GtkWidget *req_prod_code_entry,
*req_prod_prod_entry,
*req_prod_descr_text,
*req_prod_prori_combo,
*req_prod_data_entry,
*req_prod_dtevent_entry,
*req_prod_status_combo;
