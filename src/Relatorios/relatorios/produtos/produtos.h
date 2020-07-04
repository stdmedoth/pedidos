struct
{

	char *campos;
	char **campo_query;
	int campos_qnt;
}prod_query;

char campos_query[MAX_RELAT_CAMPOS][50];

static int relat_prod_gerando=0;
static GtkWidget *relat_prod_code_entry,
*relat_prod_nome_entry,
*relat_prod_cod_int1_entry, *relat_prod_cod_int2_entry, *relat_prod_cod_int_frame, *relat_prod_cod_int_fixed,
*relat_prod_forn_int1_entry, *relat_prod_forn_int2_entry, *relat_prod_forn_int_frame, *relat_prod_forn_int_fixed,
*relat_prod_grp_int1_entry, *relat_prod_grp_int2_entry, *relat_prod_grp_int_frame, *relat_prod_grp_int_fixed,
*relat_prod_ordem_combo, *relat_prod_crescente_combo, *relat_prod_ordem_box, *relat_prod_ordem_frame, *relat_prod_ordem_fixed,
*relat_prod_query_entry;

static GtkWidget *relat_prod_gerar_button;

static GtkWidget *psq_relat_prod_code;

static gchar *relat_prod_codigo_gchar, *relat_prod_query_gchar;

int relat_prod_codigo_fun();
int relat_prod_query_fun();
int relat_prod_gerar_fun();

#include "campos/codigo.c"
#include "campos/query.c"
#include "gerar.c"
