//combo_box de terceiros
static gchar **nomes_temas;
static int temas_qnt=0;
static int orc_estoque_padrao=1;
GtkWidget **campos_de_critica;

//combo_box de produtos
GtkWidget *prod_fornecedor,*prod_grupo,*prod_preco,*prod_total,*prod_peso,*prod_unidade,*prod_fator;
GtkWidget *tecn_param_nav_path1_entry, *tecn_param_nav_path2_entry, *tecn_param_nav_choose1_radio, *tecn_param_nav_choose2_radio;
GtkWidget *tecn_param_imp_path1_entry, *tecn_param_imp_path2_entry, *tecn_param_imp_path3_entry;

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

static struct
{
	struct parametros
	{
		int doc;
		int inscricao;
		int tipodoc;
		int bairro;
		int endereco;
		int cep;
		int cidade;
		int uf;
		int tipo;
		int celular;
		int contatoc;
		int telefone;
		int contatot;
		int email;
		int contatoe;
		int observacoes;
		int prazo;
		int vlr_frete_pago;
		int fornecedor;
		int grupo;
		int produto;
		int preco;
		int entrega;
		int total;
		int peso;
		int unidade;
		int fator;
		int vincula_prod_obs;
		int prod_movimento;
		int prod_saldo;
		int prod_saldo_limite;
		int orc_ped_cancelado;
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

static struct {
	int navegador_pdr;
	gchar navegador_path1[MAX_PATH_LEN];
	gchar navegador_path2[MAX_PATH_LEN];
}navegadores;

static struct {
	gchar imp_path1[MAX_PATH_LEN];
	gchar imp_path2[MAX_PATH_LEN];
	gchar imp_path3[MAX_PATH_LEN];
}impressoras;

char *desktop_images_vet[] =
{
	THUMBDESKTOP1,
	THUMBDESKTOP2,
	THUMBDESKTOP3,
	THUMBDESKTOP4,
	THUMBDESKTOP5,
	THUMBDESKTOP6
};
