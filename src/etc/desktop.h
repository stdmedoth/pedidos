static void criar_janela_princ();

const int default_user_code = 1;
static GtkWidget  *janela_principal;
static GtkWidget *imagem_desktop;

static GtkWidget *superior, *superior_1, *superior_2;
static GtkWidget *inferior, *inferior_1, *inferior_2;
static GtkWidget *area_de_trabalho;
static GtkWidget *barra;

GtkWidget *imagem_barra,*layout_barra;

int desktop();

GtkApplication *app;

static GtkWidget  *sessao_criacao_label, *sessao_expiracao_label, *sessao_inatividade_label;
static GtkWidget  *fixed_razao, *fixed_endereco, *fixed_cnpj;
static GtkWidget  *razao,*endereco,*cnpj, *caixa_infos;
static GtkWidget *janela_inicializacao;
