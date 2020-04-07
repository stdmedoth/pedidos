#define MAX_PROD_ORC 1000
#define PROD_LINHAS_ORC 1
int inicializar_orc()
{
	
	return 0;
}
int pressionado=0;

static GtkWidget *pesquisa_orc,*pesquisa_ter,**pesquisa_prod;
static GtkWidget *img_pesquisa_orc,*img_pesquisa_ter,**img_pesquisa_prod;

static gchar *cliente_orc_gchar,
*cliente_orc_name_gchar,
*cliente_orc_end_gchar,
*cliente_orc_tel_gchar;

static gchar *codigo_orc_gchar,
*operacao_orc_gchar,
*observacoes_orc_gchar;

static gchar *codigo_prod_orc_gchar, 
*descricao_prod_orc_gchar,
*qnt_prod_orc_gchar,
*preco_prod_orc_gchar,
*orig_preco_prod_orc_gchar,
*desconto_prod_orc_gchar,
*total_prod_orc_gchar;
static char *item_frame_char;
static GtkWidget *janela_orcamento;
//  FRAMES
static GtkWidget *codigo_orc_frame,*operacao_orc_frame,*cliente_orc_frame,*observacoes_orc_frame,*itens_orc_frame,**linhas_prod_orc_frame;

// FIXEDs
static GtkWidget *orc_infos_fixed,*orc_itens_fixed,*orc_geral_fixed;

// LABELS

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

static GtkWidget **codigo_prod_orc_entry,
**descricao_prod_orc_entry,
**qnt_prod_orc_entry,
**preco_prod_orc_entry,
**orig_preco_prod_orc_entry,
**desconto_prod_orc_entry,
**total_prod_orc_entry;

//  BOXES
static GtkWidget *caixa_orc_infos_c;/*,*caixa_orc_infos_b;*/
static GtkWidget *codigo_orc_box,*operacao_orc_box,*cliente_orc_box,*itens_orc_box,**linhas_prod_orc_box;
static GtkWidget *caixa_grande,*caixa_orc_infos_d,*caixa_orc_infos_e,*caixa_orc_infos;

//Containers
static GtkWidget *prod_scroll_window,*prod_scroll_box;
static GtkWidget /**codigo_prod_orc_box,
**descricao_prod_orc_box,
**qnt_prod_est_orc_box,
**qnt_prod_orc_box,
**preco_prod_orc_box,
**orig_preco_prod_orc_box,
**desconto_prod_orc_box,*/
*img_botao_orc_mais,**img_botao_menos;
static int cont;

static GtkWidget *observacoes_orc,*buffer_orc;

//Botoes
static GtkWidget *botao_orc_mais,**botao_menos;

int itens_qnt=1;
int id_vetor[MAX_PROD_ORC];

struct itens_struct
{
	int id;
	int item;
}ativos[MAX_PROD_ORC],excluidos[MAX_PROD_ORC];
#include "campos/cliente_orc.c"
#include "campos/prod_orc.c"
#include "campos/qnt_orc.c"
#include "campos/preco_orc.c"
#include "campos/total_orc.c"
#include "campos/orig_preco_orc.c"
#include "campos/desconto_orc.c"
#include "campos/pesquisas/pesquisa_terceiros.c"
#include "campos/pesquisas/pesquisa_produtos.c"
