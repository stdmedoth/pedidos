struct _cheque *cheque_get_cheque(int cheque_code);
struct _cheque *cheque_get_simple_cheque(int cheque_code);

enum CHEQUE_COLS{
	CHEQUE_CODE_COL,
	CHEQUE_BNC_COL,
	CHEQUE_CONTA_COL,
	CHEQUE_SERIE_COL,
	CHEQUE_NUM_COL,
	CHEQUE_PAGNT_COL,
	CHEQUE_DT_EMSSAO_COL,
	CHEQUE_VLR_COL,
	CHEQUE_NUM_ROWS
};

struct _cheque {
	int code;
	struct _banco *banco;
	char *conta;
	char *serie;
	char *numero;
	char *data_emissao;
	struct _terc_infos *pagante;
	float valor;
};