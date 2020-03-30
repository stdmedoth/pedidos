struct parametros
{
	int codigo;
	int doc;
	int nome;
	int endereco;
	int tipo;
	int celular;
	int contatoc;
	int telefone;
	int contatot;
	int email;
	int contatoe;
	int observacoes;
	int fornecedor;
	int grupo;
	int preco;
	int peso;
	int unidade;
	int marca;
	int vincula_prod_obs;
}criticar;

int vet_erro[CAMPOS_QNT+1];

#define COD_ERR 0
#define DOC_ERR 1
#define NOM_ERR 2
#define END_ERR 3
#define TIP_ERR 4
#define CEL_ERR 5
#define CNC_ERR 6
#define TEL_ERR 7
#define CNT_ERR 8
#define EML_ERR 9
#define CNE_ERR 10
#define OBS_ERR 11
#define PRC_ERR 12
#define VIN_ERR 13
#define PES_ERR 14
#define FOR_ERR 15
#define UND_ERR 16
#define GRP_ERR 17
#define MRC_ERR 18
