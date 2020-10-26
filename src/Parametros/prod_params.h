GtkWidget *prod_varios_grupos_wdt;

static struct{
	struct{
		int grupo;
		int peso;
		int unidade;
		int fornecedor;

	}criticar;

	struct{
		int prod_varios_grupos;
	}parametros;
}produtos;

int ler_prod_params();

void criar_prod_params(FILE *xmlf);

int atualizar_prod_criticas();

int receber_prod_params();
