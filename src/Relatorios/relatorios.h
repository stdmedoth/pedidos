static int codigo_rel_campo=0, codigo_rel_tabel=0;

static GtkWidget *cad_rel_code_entry, 
*cad_rel_nome_entry,
*cad_rel_tabel_combo;

static GtkWidget *cad_relat_treeview;

static gchar *cad_rel_code_gchar, 
*cad_rel_nome_gchar;

struct 
{
	int codigo;
	int campos_code[MAX_RELAT_CAMPOS];
	int campos_code_bkp[MAX_RELAT_CAMPOS];
	int qnt_campos;
	char nome[MAX_RELAT_NOME];
	bool status[MAX_RELAT_CAMPOS];
	
}
relat_struct;
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

#include "campos/codigo.c"
#include "campos/nome.c"
#include "campos/tabela.c"
#include "campos/remover.c"

#include "cancelar.c"
#include "concluir.c"
#include "alterar.c"
#include "excluir.c"

#include "pesquisar/relat_campos.c"
