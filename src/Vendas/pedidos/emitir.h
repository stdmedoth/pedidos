static struct _ped_valores{
	float valor_prds;
	float valor_prds_desc;
	float valor_prds_liquido;

	float valor_frete;
	float desconto_frete;
	float valor_frete_liquido;

	float desconto_total;
	float valor_total;
}ped_valores;

static struct _ped_infos{
  int ped_code;
	int banco;
	int status;
  int cliente_code;
  char data_mov[MAX_DATE_LEN];
  int tipo_mov;
}ped_infos;

static struct _ped_parcelas{
	struct  _condpag condpag;
	char *parcelas_data[MAX_PARCELAS_QNT];
	float parcelas_vlr[MAX_PARCELAS_QNT];
	float total_geral;
	int tipo_tit;
}ped_parcelas;

struct _pedido{
	struct _ped_valores valores;
	struct _ped_infos infos;
	struct _ped_parcelas parcelas;
};
