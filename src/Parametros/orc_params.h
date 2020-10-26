GtkWidget *orc_prod_mov_wdt, *orc_prod_sld_wdt, *orc_prod_sld_lmt_wdt, *orc_ped_canc_wdt;

static struct{
	struct {
		int prod_movimento;
		int prod_saldo;
		int prod_saldo_limite;
		int orc_ped_cancelado;
	}criticar;
}orcamentos;

int ler_orc_params();

int atualizar_orc_criticas();
