#define STATUS_PED_EMIT 1
#define STATUS_PED_CAN 2

static struct{
	float valor_prds;
	float valor_prds_desc;
	float valor_prds_liquido;

	float valor_frete;
	float desconto_frete;
	float valor_frete_liquido;

	float desconto_total;
	float valor_total;
}ped_valores;

static struct{
  int ped_code;
	int status;
  int cliente_code;
  char data_mov[MAX_DATE_LEN];
  int tipo_mov;
}ped_infos;

static struct {
	int tipo_parc;
	int dia_inicial;
	int dia_inicial_flag;
	int intervalos;
	int parcelas_qnt;
	int pagcond_code;
	char *parcelas_data[MAX_PARCELAS_QNT];
	float parcelas_vlr[MAX_PARCELAS_QNT];
	float total_geral;
	int tipo_tit;
}ped_parcelas;
