struct _cheque *cheque_get_cheque(int cheque_code);
struct _cheque *cheque_get_simple_cheque(int cheque_code);

GtkWidget 
*cheque_code_entry,
*cheque_psqcode_button,

*cheque_bnccode_entry,
*cheque_bncpsqcode_button,
*cheque_bncnome_entry,

*cheque_conta_entry,
*cheque_serie_entry,
*cheque_numero_entry,

*cheque_pgntcode_entry,
*cheque_pgntpsqcode_button,
*cheque_pgntnome_entry,

*cheque_dtemissao_entry,
*cheque_valor_entry;

GtkWidget
*cheque_concluir_button,
*cheque_alterar_button,
*cheque_cancelar_button,
*cheque_excluir_button;

int cheque_wnd_fun();

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