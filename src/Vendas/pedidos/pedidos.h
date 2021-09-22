enum PED_COLS{
	PED_CODE_COL,
	PED_TIPO_COL,
	PED_VENDDOR_COL,
	PED_CLI_COL,
	PED_DATE_COL,
	PED_PAG_COND,
	PED_FORMPAG_COL,
	PED_TOT_COL,
	PED_STATUS_COL
};

GtkWidget *janela_pedidos;
GtkWidget *ped_cod_entry;
GtkWidget *ped_ter_entry;
GtkWidget *ped_data_entry;
GtkWidget *ped_pag_entry;
GtkWidget *ped_est_combo;
GtkWidget *ped_tipo_combo;
GtkWidget *ped_form_pag_combo;
GtkWidget *emiteped_status_combo;
GtkWidget *ped_bancocod_entry,*ped_banco_entry;
GtkWidget *ped_psq_cod_button;

struct _ped_valores{
	float valor_prds;
	float valor_prds_desc;
	float valor_prds_liquido;

	float valor_frete;
	float desconto_frete;
	float valor_frete_liquido;

	float desconto_total;
	float valor_total;
};

struct _ped_infos{
  int ped_code;
	int banco;
	int status;
  int cliente_code;
  char data_mov[MAX_DATE_LEN];
  int tipo_mov;
};

struct _ped_parcelas{
	struct  _condpag condpag;
	char *parcelas_data[MAX_PARCELAS_QNT];
	float parcelas_vlr[MAX_PARCELAS_QNT];
	float total_geral;
	int tipo_tit;
};

struct _pedido{
	struct _ped_infos *infos;
	struct _ped_valores *valores;
	struct _ped_parcelas *parcelas;
};

int produtos_ped_list(GtkEntry *widget, GtkTreeView *treeview);

GtkWidget *campos_produto_ped();

int vnd_ped();
