enum{
  TP_TIT_REC,
  TP_TIT_PAG
};

struct _titulo_parcela{
  int posicao;
  struct _banco *banco;
  char *data_criacao;
  char *data_vencimento;
  float valor;
};

struct _titulo{
  int code;
  int cliente;
  int pedido;
  int status;
  int qnt_parcelas;
  int qnt_baixas;
  int tipo_titulo;

  struct _titulo_parcela *parcelas;
  struct _titulo_parcela *baixas;

  GtkTreeView *treeview;
  MYSQL_RES *result;
  MYSQL_ROW row;
};

enum _TIT_STATS{
  STAT_QUITADO,
  STAT_PARC_BAIXA,
  STAT_PENDENTE
};
