struct
{
	char campos[MAX_RELAT_CAMPOS*MAX_QUERY_ELM_LEN+MAX_QUERY_ELM_LEN];
	char campo_query[MAX_RELAT_CAMPOS][MAX_QUERY_ELM_LEN];
	int campos_qnt;
}mov_query;

static GtkWidget *relat_mov_code_entry,
*relat_mov_nome_entry,
*relat_mov_query_entry;

static GtkWidget *psq_relat_mov_code;

static gchar *relat_mov_codigo_gchar, *relat_mov_query_gchar;

int relat_mov_codigo_fun();
int relat_mov_query_fun();
int relat_mov_gerar_fun();

#include "campos/codigo.c"
#include "campos/query.c"
#include "gerar.c"
