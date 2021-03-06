int cad_relat();

static int codigo_rel_campo=0, codigo_rel_tabel=0;

static GtkWidget *cad_rel_code_entry,
*cad_rel_nome_entry,
*cad_rel_tabel_combo;

static GtkWidget *cad_relat_treeview;

static gchar *cad_rel_code_gchar,
*cad_rel_nome_gchar;

static char campos_query[MAX_RELAT_CAMPOS+1][MAX_ROW_LEN];

static struct{
	int codigo;
	int campos_code[MAX_RELAT_CAMPOS+1];
	int campos_code_bkp[MAX_RELAT_CAMPOS+1];
	int qnt_campos;
	char nome[MAX_RELAT_NOME];
	int status[MAX_RELAT_CAMPOS+1];
}relat_struct;

struct _relat_query{
	char *campos;
	char **campo_query;
	int campos_qnt;
};

static int relat_campo_atual=1;

static int tabelas_bd_id=0;
static gint cad_rel_tabel_int;

static GtkWidget *cad_rel_psqrow_button, *psq_cad_rel_button;

static GtkWidget *cad_rel_confirmar_button, *cad_rel_alterar_button, *cad_rel_cancelar_button, *cad_rel_excluir_button;

GtkWidget *campos_rel_remover_button;

static int concluindo_cad_rel=0, alterando_cad_rel=0;

#define CAD_REL_CODE 0
#define CAD_REL_NOME 1
#define CAD_REL_TABEL 2
#define CAD_REL_CAMPO 3

#include "pesquisar/relat_campos.h"
#include "cancelar.h"
#include "concluir.h"
#include "alterar.h"
#include "excluir.h"
