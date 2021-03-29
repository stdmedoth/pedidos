GtkWidget *orc_prod_mov_wdt,
					*orc_prod_sld_wdt,
					*orc_prod_sld_lmt_wdt,
					*orc_ped_canc_wdt,
					*orc_ped_doc_wdt;

enum ORC_TIPO_FAT{
	ORC_FAT_INATIVO,
	ORC_FAT_CUPOM,
	ORC_FAT_NFE
};

static struct{
	struct {
		int prod_movimento;
		int prod_saldo;
		int prod_saldo_limite;
		int orc_ped_cancelado;
	}criticar;

	int envia_email;
	int tipo_faturamento;
}orcamentos;

int ler_orc_params();

int atualizar_orc_params();
