int trsp_cad_fun();

GtkWidget *trsp_cad_code_entry, *trsp_cad_code_button;
GtkWidget *trsp_cad_trspcode_entry, *trsp_cad_trsp_entry, *trsp_cad_trsp_button;
GtkWidget *trsp_cad_clicode_entry, *trsp_cad_cli_entry, *trsp_cad_cli_button;
GtkWidget *trsp_cad_cepini_entry, *trsp_cad_cepini_button;
GtkWidget *trsp_cad_cepentr_entry, *trsp_cad_cepentr_button;
GtkWidget *trsp_cad_nument_entry;
GtkWidget *trsp_cad_orc_entry,*trsp_cad_orc_button;
GtkWidget *trsp_cad_vlrfrt_entry;
GtkWidget *trsp_cad_descfrt_entry;
GtkWidget *trsp_cad_obs_entry;

GtkWidget *trsp_cad_endini_entry, *trsp_cad_endentr_entry;

gchar *trsp_cad_code_gchar;
gchar *trsp_cad_trspcode_gchar;
gchar *trsp_cad_clicode_gchar;
gchar *trsp_cad_cepini_gchar;
gchar *trsp_cad_cepentr_gchar;
gchar *trsp_cad_nument_gchar;
gchar *trsp_cad_orc_gchar;
gchar *trsp_cad_vlrfrt_gchar;
gchar *trsp_cad_descfrt_gchar;
gchar *trsp_cad_obs_gchar;

GtkWidget *trsp_cad_concluir_button, *trsp_cad_alterar_button,
*trsp_cad_excluir_button, *trsp_cad_cancelar_button;

static int trsp_cad_concluindo=0, trsp_cad_alterando=0, trsp_cad_rec_alteracao=0;

int trsp_cad_cancelar_fun();
int trsp_cad_alterar_fun();
int trsp_cad_concluir_fun();
int trsp_cad_excluir_fun();

#include "campos/cep_destino.c"
#include "campos/cep_inicio.c"
#include "campos/cliente.c"
#include "campos/codigo.c"
#include "campos/numero.c"
#include "campos/transportador.c"
#include "campos/desconto.c"
#include "campos/observacoes.c"
#include "campos/orcamento.c"
#include "campos/valor.c"

#include "concluir.c"
#include "alterar.c"
#include "cancelar.c"
#include "excluir.c"
