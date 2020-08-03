GtkWidget *cad_ceps_code_entry;
GtkWidget *cad_ceps_cep_entry;
GtkWidget *cad_ceps_descr_entry;
GtkWidget *cad_ceps_tipo_combo;
GtkWidget *cad_ceps_uf_combo;
GtkWidget *cad_ceps_bairro_entry;
GtkWidget *cad_ceps_cid_code_entry;
GtkWidget *cad_ceps_cid_descr_entry;

GtkWidget *cad_cid_id_entry;
GtkWidget *cad_cid_descr_entry;
GtkWidget *cad_cid_uf_combo;
GtkWidget *cad_cid_ibge_entry;
GtkWidget *cad_cid_ddd_entry;

gchar *cad_ceps_code_gchar;
gchar *cad_ceps_cep_gchar;
gchar *cad_ceps_descr_gchar;
gint cad_ceps_tipo_int;
gint cad_ceps_uf_int;
gchar *cad_ceps_bairro_gchar;
gchar *cad_ceps_cid_code_gchar;

gchar *cad_cid_id_gchar;
gchar *cad_cid_descr_gchar;
gint cad_cid_uf_int;
gchar *cad_cid_ibge_gchar;
gchar *cad_cid_ddd_gchar;

static int cad_ceps_alterando=0,cad_ceps_concluindo=0;

GtkWidget *cad_cep_confirma_button,
*cad_cep_cancela_button,
*cad_cep_altera_button,
*cad_cep_exclui_button;

char uf_list[MAX_UF_QNT][MAX_UF_LEN];
int cad_cep(),cad_ceps_uf_qnt=0;

#include "campos/codigo.c"
#include "campos/cep.c"
#include "campos/logr_descricao.c"
#include "campos/tipo_logr.c"
#include "campos/uf.c"
#include "campos/bairro.c"
#include "campos/cidade.c"
#include "cancelar.c"
#include "concluir.c"
#include "alterar.c"
#include "excluir.c"
