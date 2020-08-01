static GtkWidget *caixa_postlist;
static GtkWidget *scroll_postlist ;

static GtkWidget *sup_adiciona_button, *sup_psq_status_combo;

static GtkWidget **postlist,**titulo_list,**titulo_list_frame,**descr_list, **sup_atualiza_button, **sup_status_combo, **sup_priorit_spin;

static GtkWidget *suport_grid, **sup_posts_frame;

static GtkWidget **sup_deleta_button,**sup_opcoes_box;

static GtkWidget **sup_tipo_combo;

GtkWidget **sup_prioridade_frame;
static GtkWidget *sup_prior_combo;

static char **sup_status_nomes;
static int sup_status_nomes_qnt=0, sup_status = 0;

static int sup_posts_qnt=1, sup_posts_pos=1;
static int *sup_vet_posts_qnt;

static char status_end_query[MAX_QUERY_LEN/3];
static char prioridade_end_query[MAX_QUERY_LEN/3];

static const int sup_prior_qnt=5;
static int sup_prior = 0;

static char **sup_tipo_nomes;
static int sup_tipo_nomes_qnt=0, sup_tipo = 0;

int suporte_princ_wnd();
