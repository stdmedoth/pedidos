enum ORIGPRC_COLS{
  ORIGPRC_NUL,
  ORIGPRC_PROD,
  ORIGPRC_CLI,
  ORIGPRC_OPER,
  ORIGPRC_COLS_QNT
};

#define ORC_ORIGPRC_NUL "NULO"
#define ORC_ORIGPRC_PROD "PRODUTO"
#define ORC_ORIGPRC_CLI "CLIENTE"
#define ORC_ORIGPRC_OPER "OPERADOR"

int orc_scrolled_item();

static int adicionar_linha_orc();
