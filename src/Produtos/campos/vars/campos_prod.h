static gchar *codigos_prod=NULL;
static gchar *nomes_prod=NULL;
static gchar *precos_prod=NULL;
static gchar *pesos_prod=NULL;
static gchar *unidades_prod=NULL;
static gchar *fornecedores_prod=NULL;
static gchar *grupos_prod=NULL;;
static gchar *fatores_prod=NULL;;
static gchar *observacoes_prod=NULL;

static GtkWidget *psq_forn_button,*psq_grp_button,*psq_und_button;
static GtkWidget *psq_forn_img,*psq_grp_img,*psq_und_img;
static GtkWidget *psq_forn,*psq_grp,*psq_und;

static GtkWidget *code_prod_label,  *nome_prod_label, 
*preco_prod_label, *peso_prod_label , *unidade_prod_label,
*fornecedor_prod_label, *grupo_prod_label, 
*fator_prod_label,  *observacao_prod_label;

static GtkWidget *codigo_prod_field, *nome_prod_field, 
*preco_prod_field,  *peso_prod_field, *unidade_prod_field,
*fornecedor_prod_field, *grupo_prod_field, 
*fator_prod_field, *observacao_prod_field;

static GtkWidget *tipos_scroll_window, *tipos_scroll_caixa;

static GtkWidget *campo_nome_unidade,
*campo_nome_fornecedor,
*campo_nome_grupo;


//produtos
#define PROD_CAD_QUERY "insert into produtos(nome,preco,peso,unidade,fornecedor,grupo,fator,observacoes) values( '%s', %s, %s, %s, %s, %s, %s, '%s');"
#define ARGS_PROD_CAD_QUERY nomes_prod, precos_prod, pesos_prod, unidades_prod, fornecedores_prod, grupos_prod, fatores_prod, observacoes_prod
#define PROD_UPD_QUERY "update produtos set nome = '%s', preco = %s, peso = %s, unidade = %s, fornecedor = %s, grupo = %s, fator = %s, observacoes = '%s' where code = %s"
#define ARGS_PROD_UPD_QUERY nomes_prod, precos_prod, pesos_prod, unidades_prod, fornecedores_prod, grupos_prod, fatores_prod, observacoes_prod,codigos_prod

//fatores
#define FTR_CAD_QUERY "insert into fatores(nome,observacoes) values('%s','%s');"
#define ARGS_FTR_CAD_QUERY nomes_ftr,observacoes_ftr
#define FTR_UPD_QUERY "update fatores set nome = '%s',observacoes = '%s' where code = %s"
#define ARGS_FTR_UPD_QUERY nomes_ftr,observacoes_ftr,codigos_ftr
