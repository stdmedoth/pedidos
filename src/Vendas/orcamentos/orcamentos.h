#define COD_ORC_COL 0
#define COD_ORC_COL 0
#define NOM_ORC_COL 0

#define COD_ORC_PROD_COL 0
#define ITM_ORC_PROD_COL 1
#define PROD_ORC_PROD_COL 2
#define SUBGRP_ORC_PROD_COL 3
#define UND_ORC_PROD_COL 4
#define VLR_ORC_PROD_COL 5
#define VLR_ORIG_ORC_PROD_COL 6
#define TIP_DESC_ORC_PROD_COL 7
#define DESC_ORC_PROD_COL 8
#define TOTAL_ORC_PROD_COL 9


#define MAX_PROD_ORC 1000
#define PROD_LINHAS_ORC 1
#define DATE_QUERY "select DATE_FORMAT(dia,\"%d/%m/%Y\") from orcamentos where code = "
int altera_orc();
int tirar_linha(int);
int vnd_orc();

int inicializar_orc()
{
	int cont;
	for(cont=0;cont<=CAMPOS_QNT;cont++)
		vet_erro[cont] = 0;
	return 0;
}
static int orc_vista=0,orc_faturado=0;

int rec_altera_qnt=1;
static GtkWidget *orc_notebook;

int preco_prod_orc(GtkWidget *widget,int posicao);
int preco_alterado[MAX_PROD];
int pressionado=0;
static int ativos_qnt=1;

static float total_geral_orc =0 ;
static float desconto_geral_orc =0 ;
//COMBO
static GtkWidget **tipodesconto_prod_orc_combo;
static GtkWidget *faturado_avista_combo, *faturado_avista_fixed, *faturado_avista_box;

//  BUTTONS 

static GtkWidget *pesquisa_orc,*pesquisa_ter,**pesquisa_prod;
static GtkWidget *img_pesquisa_orc,*img_pesquisa_ter,**img_pesquisa_prod;

static GtkWidget *concluir_orc_button,*gerar_orc_button,*pedido_orc_button,*alterar_orc_button,*cancelar_orc_button,*excluir_orc_button;
static GtkWidget *concluir_orc_img_button,*gerar_orc_img_button,*pedido_orc_img_button,*alterar_orc_img_button,*cancelar_orc_img_button,*excluir_orc_img_button;
static GtkWidget *caixa_opcoes_orc;
//  GCHAR

static gchar *data_orc_gchar;

static gchar *cliente_orc_gchar;

static gchar *codigo_orc_gchar,
//*operacao_orc_gchar,
*observacoes_orc_gchar;

static gchar *codigo_prod_orc_gchar, 
//*descricao_prod_orc_gchar,
*subgrp_prod_orc_cod_gchar,
*qnt_prod_orc_gchar,
*preco_prod_orc_gchar,
*orig_preco_prod_orc_gchar,
*desconto_prod_orc_gchar,
*total_prod_orc_gchar;

int gerar_total_geral();
static char *item_frame_char;
static GtkWidget *janela_orcamento;

//  FRAMES


static GtkWidget **codigo_prod_orc_frame;
static GtkWidget **desconto_prod_orc_frame,**desconto_prod_orc_box;
static GtkWidget **preco_prod_orc_frame,**preco_prod_orc_box;
static GtkWidget **qnt_prod_orc_frame,**qnt_prod_orc_box;
static GtkWidget **subgrp_prod_orc_frame,**subgrp_prod_orc_box;

static GtkWidget *data_orc_frame;
static GtkWidget *codigo_orc_frame,*operacao_orc_frame,*cliente_orc_frame,*observacoes_orc_frame,**linhas_prod_orc_frame;
static GtkWidget *total_geral_orc_frame,*desconto_geral_orc_frame;

// FIXEDs
static GtkWidget *orc_infos_fixed,*orc_itens_fixed,*orc_geral_fixed;
static GtkWidget *opcoes_orc_fixed;

// LABELS

//static GtkWidget *data_orc_label;
static GtkWidget *total_geral_orc_label,*desconto_geral_orc_label;

static GtkWidget *codigo_orc_label,*operacao_orc_label,*cliente_orc_label;
static GtkWidget **codigo_prod_orc_label,
**descricao_prod_orc_label,
**qnt_prod_orc_label,
**preco_prod_orc_label,
**orig_preco_prod_orc_label,
**desconto_prod_orc_label,
**total_prod_orc_label;

//  ENTRYs

static GtkWidget *codigo_orc_entry,*operacao_orc_entry,*cliente_orc_entry,*cliente_orc_name_entry,*cliente_orc_end_entry,*cliente_orc_tel_entry;


static GtkWidget **codigo_orc_prod_box;

static GtkWidget **codigo_prod_orc_entry,
**descricao_prod_orc_entry,
**subgrp_prod_orc_entry, **subgrp_prod_orc_cod_entry,
**subgrp_prod_orc_button, 
**qnt_prod_orc_entry,
**preco_prod_orc_entry,
**orig_preco_prod_orc_entry,
**desconto_prod_orc_entry,
**total_prod_orc_entry;

static GtkWidget *data_orc_entry;

//  BOXES
static GtkWidget *caixa_orc_infos_c;/*,*caixa_orc_infos_b;*/
static GtkWidget *codigo_orc_box,*operacao_orc_box,*cliente_orc_box,*itens_orc_box,*transp_orc_box,*outros_orc_box,**linhas_prod_orc_box;
static GtkWidget *caixa_grande,*caixa_orc_infos_d,*caixa_orc_infos_e,*caixa_orc_infos;

//  CONTAINERS
static GtkWidget *prod_scroll_window,*prod_scroll_box;
static GtkWidget *img_botao_orc_mais,**img_botao_menos;

static int cont;
int adicionar_linha_orc();
static GtkWidget *observacoes_orc,*buffer_orc;

//Botoes
static GtkWidget *botao_orc_mais,**botao_menos;

int itens_qnt=1;
int id_vetor[MAX_PROD_ORC];



struct itens_struct
{
	int id;
	int item;
	int produto;
	int subgrupo;
	float qnt_f;
	float preco_f;
	float desconto_f;
	int tipodesc;
	float total_f;
	char qnt_c[MAX_PRECO_LEN];
	char preco_c[MAX_PRECO_LEN];
	char desconto_c[MAX_PRECO_LEN];
	char total_c[MAX_PRECO_LEN];
	char origem_preco[15];
}ativos[MAX_PROD_ORC],excluidos[MAX_PROD_ORC];


