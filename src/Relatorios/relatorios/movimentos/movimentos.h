struct
{

	char campos[MAX_RELAT_CAMPOS*MAX_QUERY_ELM_LEN+MAX_QUERY_ELM_LEN];
	char campo_query[MAX_RELAT_CAMPOS][MAX_QUERY_ELM_LEN];
	int campos_qnt;
}sld_query;

static GtkWidget *relat_sld_code_entry,
*relat_sld_nome_entry,
*relat_sld_query_entry;

static GtkWidget *psq_relat_sld_code;

static gchar *relat_sld_codigo_gchar, *relat_sld_query_gchar;

int relat_sld_codigo_fun();
int relat_sld_query_fun();
int relat_sld_gerar_fun();

#include "campos/codigo.c"
#include "campos/query.c"
#include "gerar.c"
