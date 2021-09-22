enum ORC_COLS{
	ORC_COD_COL,
	ORC_TIPMOV_COL,
	ORC_VENDD_COL,
	ORC_CLI_COL,
	ORC_DATE_COL,
	ORC_PAGCOND_COL,
	ORC_FORMPAG_COL,
	ORC_BANC_COL,
	ORC_CHEQUE_COL,
	ORC_TOTAL_COL,
	ORC_OBS_COL
};

#define MAX_PROD_ORC 10

enum TIPO_DESC{
	DESCT_EM_REAIS,
	DESCT_EM_PORCENT
};

enum ORC_PROD_COLS{
	ORC_PROD_COD_COL,
	ORC_PROD_ITM_COL,
	ORC_PROD_PROD_COL,
	ORC_PROD_UND_COL,
	ORC_PROD_VLR_COL,
	ORC_PROD_VLR_ORIG_COL,
	ORC_PROD_TIP_DESC_COL,
	ORC_PROD_DESC_COL,
	ORC_PROD_TOTAL_COL,
	ORC_PROD_OBS_COL
};

struct _orc_estoque_prods{
	int code;
	float saldo;
	float saldo_min;
	float saldo_usado;
	float saldo_liquido;
	int mov_qnt;
};

static struct _orc_estoque{
	struct _orc_estoque_prods **produtos;
	int length;
}orc_estoque;


static struct _orc_itens
{

	int id;
	int item;
	char item_c[12];
	int produto;
	char produto_c[12];
	char produto_nome[MAX_NAME_LEN];
	char CFOP[5];
	char cEAN[15];
	char NCM[10];
	float qnt_f;
	float preco_f;
	float desconto_f;
	int tipodesc;
	float total_f;
	char qnt_c[MAX_PRECO_LEN];
	char preco_c[MAX_PRECO_LEN];
	char desconto_c[MAX_PRECO_LEN];
	char total_c[MAX_PRECO_LEN];
	int origem_preco;
	char *observacao;

	struct _cad_produtos *_produto;
}ativos[MAX_PROD_ORC],excluidos[MAX_PROD_ORC];


static struct _orc_valores{
	float valor_prds;
	float valor_prds_desc;
	float valor_prds_liquido;

	float valor_frete;
	float desconto_frete;
	float valor_frete_liquido;

	float desconto_total;
	float valor_total;

	float valor_total_liquido;
}orc_valores;

static struct _orc_infos{

	int code;
	struct _terc_infos *cliente;
	struct _terc_infos * vendedor;
	struct _cheque *cheque;
	int tipo_mov;
	char *data;
	float total;
	char *observacoes;

}orc_infos;

static struct _orc_parcelas{
	int banco;
	float total_geral;
	float valor_faltante;
	struct _condpag *condpag;
	struct _forma_pagamento *forma_pagamento;
	float vlrs[MAX_PARCELAS_QNT];
	char *datas[MAX_PARCELAS_QNT];
	int parcelas_qnt;
}orc_parcelas;

struct _orc{
	struct _orc_infos *infos;
	struct _orc_itens **itens;
	struct _transporte *entrega;
	struct _orc_valores *valores;
	struct _orc_parcelas *parcelas;

	int itens_qnt;
};

#define DATE_QUERY "select DATE_FORMAT(dia,\"%d/%m/%Y\") from orcamentos where code = "

GtkWidget *orc_data_vlr_lists_box, **orc_data_lists_entry, **orc_vlr_lists_entry, *orc_data_vlr_lists_grid, *orc_box_datas;

GtkWidget *orc_prods_grid;

static float saldo_limite = 3;

static int recebendo_prod_orc=0;
static int alterando_orc=0;
static int cancelando_orc=0;
static int concluindo_orc=0;
static int copiando_orc=0;
static int excluindo_orc=0;

static int aviso_estoque[MAX_PROD_ORC];
static int orc_pag_cond_activated=0;
static int orc_pag_cond_fp=0;

static int adicionando_linha_ignore=0;

static int pag_cond=0, tipo_pag=0;

static int rec_altera_qnt=1;
static GtkWidget *orc_notebook;

static int preco_alterado[MAX_PROD], valor_orig[MAX_PROD];
static int pressionado=0;
static int ativos_qnt=1;

static float total_geral_orc =0 ;
static float desconto_geral_orc =0 ;

int orc_contem_ped=0;

//COMBO
GtkWidget **tipodesconto_prod_orc_combo;
GtkWidget *orc_pag_cond_entry, *orc_pag_cond_nome, *orc_pag_cond_frame, *orc_pag_cond_fixed, *orc_pag_cond_box, *orc_pag_cond_psq_button;
gchar *orc_pag_cond_gchar;
//  BUTTONS

GtkWidget *pesquisa_orc,*pesquisa_ter,**pesquisa_prod;

GtkWidget *concluir_orc_button,*gerar_orc_button,*pedido_orc_button,*alterar_orc_button,*cancelar_orc_button,*excluir_orc_button, *copia_orc_button;
GtkWidget *concluir_orc_img_button,*gerar_orc_img_button,*pedido_orc_img_button,*alterar_orc_img_button,*cancelar_orc_img_button,*excluir_orc_img_button;
GtkWidget *caixa_opcoes_orc;
//  GCHAR
static gchar *orc_bnc_code_gchar;
static gchar *data_orc_gchar;

static gchar *cliente_orc_gchar;

static gchar *codigo_orc_gchar,
//*operacao_orc_gchar,
*observacoes_orc_gchar;

static gchar *codigo_prod_orc_gchar,
//*descricao_prod_orc_gchar
*qnt_prod_orc_gchar,
*preco_prod_orc_gchar,
*orig_preco_prod_orc_gchar,
*desconto_prod_orc_gchar,
*total_prod_orc_gchar;

static char *item_frame_char;
static GtkWidget *janela_orcamento;

//  FRAMES/BOX
GtkWidget **codigo_prod_orc_frame;
GtkWidget **desconto_prod_orc_frame,**desconto_prod_orc_box;
GtkWidget **preco_prod_orc_frame,**preco_prod_orc_box;
GtkWidget **saldo_prod_orc_frame,**saldo_prod_orc_box;
GtkWidget **qnt_prod_orc_frame,**qnt_prod_orc_box;
GtkWidget **total_prod_orc_frame,**total_prod_orc_box, **total_prod_orc_fixed;


GtkWidget *data_orc_frame;
GtkWidget *codigo_orc_frame,*operacao_orc_frame,*cliente_orc_frame,*observacoes_orc_frame,**linhas_prod_orc_frame;
GtkWidget *total_geral_orc_frame,*desconto_geral_orc_frame,*frete_orc_frame;

// FIXEDs
GtkWidget *orc_infos_fixed,*orc_itens_fixed,*orc_geral_fixed;
GtkWidget *opcoes_orc_fixed;

GtkWidget **obs_prod_orc_scroll,**obs_prod_orc_fixed;

// LABELS

//static GtkWidget *data_orc_label;
GtkWidget *total_geral_orc_label,*desconto_geral_orc_label, *frete_orc_label;

GtkWidget *codigo_orc_label,*operacao_orc_label,*cliente_orc_label;
GtkWidget **codigo_prod_orc_label,
**descricao_prod_orc_label,
**preco_prod_orc_label,
**qnt_prod_orc_label,
**saldo_prod_orc_label,
**orig_preco_prod_orc_combo,
**desconto_prod_orc_label;

//  ENTRYs
GtkWidget *codigo_orc_entry,*operacao_orc_combo,*cliente_orc_entry,*cliente_orc_name_entry,*cliente_orc_end_entry,*cliente_orc_tel_entry;

GtkWidget *orc_form_pag_combo;

GtkWidget **codigo_orc_prod_box;
GtkWidget *orc_bnc_code_entry, *orc_bnc_nome_entry, *orc_bnc_psq_button;

GtkWidget **codigo_prod_orc_entry,
**descricao_prod_orc_entry,
**qnt_prod_orc_entry,
**preco_prod_orc_entry,
**saldo_prod_orc_entry,
**desconto_prod_orc_entry,
**total_prod_orc_entry;

GtkWidget *data_orc_entry;

//  BOXES
GtkWidget *caixa_orc_infos_c;/*,*caixa_orc_infos_b;*/
GtkWidget *codigo_orc_box,*operacao_orc_box,*cliente_orc_box,*itens_orc_box,*transp_orc_box,*outros_orc_box,
**linhas_prod_orc_box,
**linhas2_prod_orc_box,
**juncao_linha_prod_orc_box ;
GtkWidget *caixa_grande,*caixa_orc_infos_d,*caixa_orc_infos_e,*caixa_orc_infos;

//  CONTAINERS
GtkWidget *prod_scroll_window,*prod_scroll_box;
GtkWidget *img_botao_orc_mais,**img_botao_menos;

GtkWidget *observacoes_orc,*buffer_orc;

//Botoes
GtkWidget *botao_orc_mais,**botao_menos;

static int produto_inserido[MAX_PROD_ORC+1];
static int itens_qnt=1;
int id_vetor[MAX_PROD_ORC+1];

static int sinal_operacao_int=0;
static int operacao_orc_int=0;

int orc_transp_msg_cep=0;
int transp_verified=0;
GtkTextBuffer  **obs_prod_orc_buffer;
GtkWidget **obs_prod_orc_view, **obs_prod_orc_frame;
static gchar **obs_prod_orc_gchar;

GtkWidget *orc_entrega_campos_widget;

#include "campos.h"
#include "get.h"

static int vnd_orc();
