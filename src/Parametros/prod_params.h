static struct{
	struct{
		int grupo;
		int peso;
		int unidade;
		int fornecedor;

	}criticar;

	struct{
		int nul;
	}parametros;
}produtos;

int ler_prod_params();

void criar_prod_params(FILE *xmlf);

int atualizar_prod_params();

int receber_prod_params();
