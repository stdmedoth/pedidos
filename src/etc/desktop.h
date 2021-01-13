static void criar_janela_princ();

int desktop();

GtkApplication *app;

static GtkWidget  *sessao_criacao_label, *sessao_expiracao_label, *sessao_inatividade_label;
static GtkWidget  *fixed_razao, *fixed_endereco, *fixed_cnpj;
static GtkWidget  *razao,*endereco,*cnpj, *caixa_infos;
static GtkWidget *janela_inicializacao;
