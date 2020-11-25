enum PROD_COLS{
  PROD_COD_COL,
  PROD_NOM_COL,
  PROD_PES_COL,
  PROD_PRC_COL,
  PROD_UND_COL,
  PROD_UND_ATAC_COL,
  PROD_FORN_COL,
  PROD_GRP_COL,
  PROD_OBS_COL
};

enum PROD_ORIG{
  PROD_ORIG_NAC,
  PROD_ORIG_ESTRANG_IMPORT,
  PROD_ORIG_ESTRANG_NAC,
  PROD_ORIG_ESTRANG_40_70,
  PROD_ORIG_NAC_LEGISAJUST,
  PROD_ORIG_ESTRANG_0_40,
  PROD_ORIG_ESTRANG_CAMEX,
  PROD_ORIG_ESTRANG_NAC_CAMEX,
  PROD_ORIG_ESTRANG_70_100,
};

int code_prod();
int altera_prod();

static GtkWidget *prod_concluir_button, *prod_alterar_button, *prod_cancelar_button, *prod_excluir_button;
static GtkWidget *psq_prod_codigo_button;
static int alterando_prod=0, concluindo_prod=0, cancelando_prod=0;
int intgr_prods();
int inicializar_prod();
int  cad_prod();
static gchar *codigos_prod=NULL;
static gchar *nomes_prod=NULL;
static gchar *precos_prod=NULL;
static gchar *pesos_prod=NULL;
static gchar *unidades_prod=NULL;
static gchar *unidades_atac_prod=NULL;
static gchar *fornecedores_prod=NULL;
static gchar *grupos_prod=NULL;
static gchar *precos_faturado_prod=NULL;
static gchar *observacoes_prod=NULL;
static GtkWidget *grupo_precos_tree;
static GtkWidget *notebook_cad_prod;

static int tipo_prod=0;
static int tipo_class_prod=0;
static char *data_alteracao_prod=NULL;
static char *data_validade_prod=NULL;
static int ativo_flag_prod=0;
static float sld_min_lim_prod=0.0;
static float sld_at_prod=0.0;

static int grupo_nivel=0;
static GtkWidget *atualiza_grupo_preco_button, *atualiza_grupo_preco_fixed;

static GtkWidget *psq_forn_button,*psq_subgrp_button,*psq_und_button,*psq_qnt_atacado_button;
static GtkWidget *psq_forn_img,*psq_subgrp_img,*psq_und_img,*psq_qnt_atacado_img;
static GtkWidget *psq_forn,*psq_subgrp,*psq_und,*psq_qnt_atacado;


static GtkWidget *codigo_prod_field, *nome_prod_field,
*preco_prod_field,  *peso_prod_field, *unidade_prod_field,
*fornecedor_prod_field, *grupo_prod_field,
*preco_faturado_prod_field, *observacao_prod_field,*qnt_atacado_field;


static GtkWidget *campo_nome_unidade,
*campo_nome_fornecedor,
*campo_nome_grupo,
*campo_nome_qnt_atacado;

//produtos
#define PROD_CAD_QUERY "insert into produtos(nome, peso, preco, unidades, unidades_atacado ,fornecedor, grupo, grupo_nivel, observacoes) values( '%s', %s, %s, %s, %s, %s, %s, %i,'%s');"
#define ARGS_PROD_CAD_QUERY nomes_prod, pesos_prod, precos_prod, unidades_prod, unidades_atac_prod, fornecedores_prod, grupos_prod, grupo_nivel, observacoes_prod
#define PROD_UPD_QUERY "update produtos set nome = '%s', peso = %s, preco = %s, unidades = %s, unidades_atacado = %s,  fornecedor = %s, grupo = %s, grupo_nivel = %i, observacoes = '%s' where code = %s"
#define ARGS_PROD_UPD_QUERY nomes_prod, pesos_prod, precos_prod, unidades_prod, unidades_atac_prod, fornecedores_prod, grupos_prod, grupo_nivel, observacoes_prod,codigos_prod
