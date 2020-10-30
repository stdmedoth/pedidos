/*
codigo
tipo orc_prodimento
intervalo cliente/fornecedor
intervalo produtos
grupos
intervalo pedidos
*/

struct
{
	char campos[MAX_RELAT_CAMPOS*MAX_QUERY_LEN+MAX_QUERY_LEN];
	char campo_query[MAX_RELAT_CAMPOS][MAX_QUERY_LEN];
	int campos_qnt;
}orc_prod_query;

static GtkWidget *relat_orc_prod_int1_orc_prod_entry, *relat_orc_prod_int2_orc_prod_entry, *relat_orc_prod_int_orc_prod_frame, *relat_orc_prod_int_orc_prod_box;
static GtkWidget *relat_orc_prod_int1_ter_entry, *relat_orc_prod_int2_ter_entry, *relat_orc_prod_int_ter_frame, *relat_orc_prod_int_ter_box;
static GtkWidget *relat_orc_prod_int1_prod_entry, *relat_orc_prod_int2_prod_entry, *relat_orc_prod_int_prod_frame, *relat_orc_prod_int_prod_box;
static GtkWidget *relat_orc_prod_int1_grp_entry, *relat_orc_prod_int2_grp_entry, *relat_orc_prod_int_grp_frame, *relat_orc_prod_int_grp_box;
static GtkWidget *relat_orc_prod_int1_ped_entry, *relat_orc_prod_int2_ped_entry, *relat_orc_prod_int_ped_frame, *relat_orc_prod_int_ped_box;
static GtkWidget *relat_orc_prod_tipo_combo, *relat_orc_prod_tipo_frame, *relat_orc_prod_tipo_box;
static GtkWidget *relat_orc_prod_ordem_combo, *relat_orc_prod_ordem_frame, *relat_orc_prod_ordem_box;
static GtkWidget *relat_orc_prod_cresc_combo, *relat_orc_prod_cresc_frame, *relat_orc_prod_cresc_box;

static GtkWidget *relat_orc_prod_psq_orc_prod_button;
static GtkWidget *relat_orc_prod_psq_ter_button;
static GtkWidget *relat_orc_prod_psq_prod_button;
static GtkWidget *relat_orc_prod_psq_grp_button;
static GtkWidget *relat_orc_prod_psq_ped_button;

gint relat_orc_prod_int1_orc_prod_int, relat_orc_prod_int2_orc_prod_int,
relat_orc_prod_int1_ter_int, relat_orc_prod_int2_ter_int,
relat_orc_prod_int1_prod_int, relat_orc_prod_int2_prod_int,
relat_orc_prod_int1_grp_int, relat_orc_prod_int2_grp_int,
relat_orc_prod_int1_ped_int, relat_orc_prod_int2_ped_int,
relat_orc_prod_tipo_int,
relat_orc_prod_ordem_int,relat_orc_prod_cresc_int;

static GtkWidget *relat_orc_prod_code_entry,
*relat_orc_prod_nome_entry,
*relat_orc_prod_query_entry;

static GtkWidget *relat_orc_prod_gerar_button, *relat_orc_prod_gerar_fixed;

static GtkWidget *psq_relat_orc_prod_code;

static gchar *relat_orc_prod_codigo_gchar, *relat_orc_prod_query_gchar;

static int relat_orc_prod_gerando=0;

int relat_orc_prod_codigo_fun();
int relat_orc_prod_query_fun();
int relat_orc_prod_gerar_fun();
void relat_orc_prod_fun();
