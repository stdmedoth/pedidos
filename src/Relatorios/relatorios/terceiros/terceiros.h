struct 
{
	
	char campos[MAX_RELAT_CAMPOS*MAX_QUERY_ELM_LEN+MAX_QUERY_ELM_LEN];
	char campo_query[MAX_RELAT_CAMPOS][MAX_QUERY_ELM_LEN];
	int campos_qnt;
}ter_query;


static GtkWidget *relat_ter_code_entry,
*relat_ter_nome_entry,
*relat_ter_query_entry;

static GtkWidget *psq_relat_ter_code;

static gchar *relat_ter_codigo_gchar, *relat_ter_query_gchar;

int relat_ter_codigo_fun();
int relat_ter_query_fun();
int relat_ter_gerar_fun();

#include "campos/codigo.c"
#include "campos/query.c"
#include "gerar.c"
