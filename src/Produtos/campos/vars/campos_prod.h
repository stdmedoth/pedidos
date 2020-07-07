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

static int grupo_nivel=0;
static GtkWidget *atualiza_grupo_preco_button, *atualiza_grupo_preco_fixed;

static GtkWidget *psq_forn_button,*psq_subgrp_button,*psq_und_button,*psq_qnt_atacado_button;
static GtkWidget *psq_forn_img,*psq_subgrp_img,*psq_und_img,*psq_qnt_atacado_img;
static GtkWidget *psq_forn,*psq_subgrp,*psq_und,*psq_qnt_atacado;

static GtkWidget *code_prod_label,  *nome_prod_label,
*preco_prod_label, *peso_prod_label , *unidade_prod_label,
*fornecedor_prod_label, *grupo_prod_label,
*preco_faturado_prod_label,  *observacao_prod_label,*qnt_atacado_label;

static GtkWidget *codigo_prod_field, *nome_prod_field,
*preco_prod_field,  *peso_prod_field, *unidade_prod_field,
*fornecedor_prod_field, *grupo_prod_field,
*preco_faturado_prod_field, *observacao_prod_field,*qnt_atacado_field;

static GtkWidget *tipos_scroll_window, *tipos_scroll_caixa;

static GtkWidget *campo_nome_unidade,
*campo_nome_fornecedor,
*campo_nome_grupo,
*campo_nome_qnt_atacado;

//produtos
#define PROD_CAD_QUERY "insert into produtos(nome, peso, unidades, unidades_atacado ,fornecedor, grupo, grupo_nivel, observacoes) values( '%s', %s, %s, %s, %s, %s, %i,'%s');"
#define ARGS_PROD_CAD_QUERY nomes_prod, pesos_prod, unidades_prod, unidades_atac_prod, fornecedores_prod, grupos_prod, grupo_nivel, observacoes_prod
#define PROD_UPD_QUERY "update produtos set nome = '%s', peso = %s, unidades = %s, unidades_atacado = %s,  fornecedor = %s, grupo = %s, grupo_nivel = %i, observacoes = '%s' where code = %s"
#define ARGS_PROD_UPD_QUERY nomes_prod, pesos_prod, unidades_prod, unidades_atac_prod, fornecedores_prod, grupos_prod, grupo_nivel, observacoes_prod,codigos_prod
