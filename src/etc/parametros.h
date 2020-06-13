//combo_box de terceiros
static gchar **nomes_temas;
static int temas_qnt=0;
GtkWidget **campos_de_critica;

//combo_box de produtos
GtkWidget *prod_fornecedor,*prod_grupo,*prod_preco,*prod_total,*prod_peso,*prod_unidade,*prod_fator;

//quantidade de flags/aba
const int ter_critic_campos_qnt=13,
orc_critic_campos_qnt=17;

int temas();
static int orc_prod_saldo_limite=0;
static GtkWidget *janela_init,*janela_keep_above,*tema_combo_box;

struct
{
	int janela_init;
	int janela_keep_above;
	int tema;
}personalizacao;

struct
{
	struct parametros
	{
		bool doc;
		bool inscricao;
		bool tipodoc;
		bool endereco;
		bool cep;
		bool cidade;
		bool uf;
		bool tipo;
		bool celular;
		bool contatoc;
		bool telefone;
		bool contatot;
		bool email;
		bool contatoe;
		bool observacoes;
		bool prazo;
		bool vlr_frete_pago;
		bool fornecedor;
		bool grupo;
		bool produto;
		bool preco;
		bool entrega;
		bool total;
		bool peso;
		bool unidade;
		bool fator;
		bool vincula_prod_obs;
		bool prod_movimento;
		bool prod_saldo;
		bool prod_saldo_limite;
		bool orc_ped_cancelado;
	}criticar;
}terceiros,produtos,orcamentos;

#define CAMPOS_QNT 25
int vet_erro[CAMPOS_QNT+1];

#define COD_ERR 0
#define DOC_ERR 1
#define INSC_ERR 2
#define NOM_ERR 3
#define END_ERR 4
#define UF_ERR 5
#define CID_ERR 6
#define TIP_ERR 7
#define CEL_ERR 8
#define CNC_ERR 9
#define TEL_ERR 10
#define CNT_ERR 11
#define EML_ERR 12
#define CNE_ERR 13
#define OBS_ERR 14
#define PRC_ERR 15
#define VIN_ERR 16
#define PES_ERR 17
#define FOR_ERR 18
#define UND_ERR 19
#define GRP_ERR 20
#define MRC_ERR 21
#define CEP_ERR 22
#define PRD_ERR 23
#define CLI_ERR 24
#define PRAZ_ERR 25
#define QNT_ERR 26

char *critica_campos[] =
{
	"ter_doc",
	"ter_tipo_doc",
	"ter_endereco",
	"ter_cep",
	"ter_tipo",
	"ter_celular",
	"ter_contatoc",
	"ter_telefone",
	"ter_contatot",
	"ter_email",
	"ter_contatoe",
	"ter_entrega",
	"ter_prazo",
	"ter_vlr_frete_pago",

	"orc_prod_movimento",
	"orc_prod_saldo",
	"orc_prod_saldo_limite",
	"orc_ped_cancelado"
};

char *desktop_images_vet[] =
{
	THUMBDESKTOP1,
	THUMBDESKTOP2,
	THUMBDESKTOP3,
	THUMBDESKTOP4,
	THUMBDESKTOP5,
	THUMBDESKTOP6
};
