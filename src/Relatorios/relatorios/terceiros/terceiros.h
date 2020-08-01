struct
{

	char campos[MAX_RELAT_CAMPOS*MAX_QUERY_ELM_LEN+MAX_QUERY_ELM_LEN];
	char campo_query[MAX_RELAT_CAMPOS][MAX_QUERY_ELM_LEN];
	int campos_qnt;
}ter_query;

static int relat_ter_gerando=0;
static GtkWidget *relat_ter_code_entry,
*relat_ter_nome_entry,
*relat_ter_cod_int1_entry, *relat_ter_cod_int2_entry, *relat_ter_cod_int_frame, *relat_ter_cod_int_fixed,
*relat_ter_tipo_combo, *relat_ter_tipo_frame, *relat_ter_pes_combo, *relat_ter_pes_frame,
*relat_ter_cep_int1_entry, *relat_ter_cep_int2_entry, *relat_ter_cep_int_frame, *relat_ter_cep_int_fixed,
*relat_ter_ordem_combo, *relat_ter_crescente_combo, *relat_ter_ordem_box, *relat_ter_ordem_frame, *relat_ter_ordem_fixed,
*relat_ter_query_entry;

static gint relat_ter_cod_int1_int, relat_ter_cod_int2_int,
relat_ter_tipo_int,
relat_ter_pes_int,
relat_ter_cep_int1_int, relat_ter_cep_int2_int,
relat_ter_ordem_int,relat_ter_cresc_int;

static GtkWidget *relat_psq_cod_ter_button, *relat_psq_cep_ter_button;

static GtkWidget *psq_relat_ter_code;
static GtkWidget *relat_ter_gerar_button;

static gchar *relat_ter_codigo_gchar, *relat_ter_query_gchar;

int relat_ter_codigo_fun();
int relat_ter_query_fun();
int relat_ter_gerar_fun();

#include "campos/codigo.c"
#include "campos/query.c"
#include "campos/terceiro.c"
#include "campos/cep.c"
#include "campos/query_man.c"
#include "gerar.c"
