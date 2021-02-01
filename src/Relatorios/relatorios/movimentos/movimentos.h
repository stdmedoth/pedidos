struct
{
	char campos[MAX_RELAT_CAMPOS*MAX_ROW_LEN];
	char campo_query[MAX_RELAT_CAMPOS][MAX_ROW_LEN];
	int campos_qnt;
}mov_query;

static GtkWidget *relat_mov_int1_mov_entry, *relat_mov_int2_mov_entry, *relat_mov_int_mov_frame, *relat_mov_int_mov_box;
static GtkWidget *relat_mov_int1_ter_entry, *relat_mov_int2_ter_entry, *relat_mov_int_ter_frame, *relat_mov_int_ter_box;
static GtkWidget *relat_mov_int1_prod_entry, *relat_mov_int2_prod_entry, *relat_mov_int_prod_frame, *relat_mov_int_prod_box;
static GtkWidget *relat_mov_int1_grp_entry, *relat_mov_int2_grp_entry, *relat_mov_int_grp_frame, *relat_mov_int_grp_box;
static GtkWidget *relat_mov_int1_ped_entry, *relat_mov_int2_ped_entry, *relat_mov_int_ped_frame, *relat_mov_int_ped_box;
static GtkWidget *relat_mov_tipo_combo, *relat_mov_tipo_frame, *relat_mov_tipo_box;
static GtkWidget *relat_mov_ordem_combo, *relat_mov_ordem_frame, *relat_mov_ordem_box;
static GtkWidget *relat_mov_cresc_combo, *relat_mov_cresc_frame, *relat_mov_cresc_box;

static GtkWidget *relat_mov_psq_mov_button;
static GtkWidget *relat_mov_psq_ter_button;
static GtkWidget *relat_mov_psq_prod_button;
static GtkWidget *relat_mov_psq_grp_button;
static GtkWidget *relat_mov_psq_ped_button;

static GtkWidget *relat_mov_code_entry,
*relat_mov_nome_entry,
*relat_mov_query_entry;

static GtkWidget *relat_mov_gerar_button, *relat_mov_gerar_fixed;

static GtkWidget *psq_relat_mov_code;

static gchar *relat_mov_codigo_gchar, *relat_mov_query_gchar;

static int relat_mov_gerando=0;

int relat_mov_codigo_fun();
int relat_mov_query_fun();
int relat_mov_gerar_fun();
int relat_mov_fun();
