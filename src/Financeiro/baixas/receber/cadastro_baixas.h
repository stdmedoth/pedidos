int cad_baixas_receber();

GtkWidget *cad_bxs_rec_cli_psq_button,
*cad_bxs_rec_tit_psq_button,
*cad_bxs_rec_ped_psq_button,
*cad_bxs_rec_datacri_psq_button,
*cad_bxs_rec_datavenc_psq_button;

GtkWidget *cad_bxs_rec_concluir_button, *cad_bxs_rec_cancelar_button, *cad_bxs_rec_excluir_button, *cad_bxs_rec_alterar_button;
GtkWidget *cad_bxs_rec_code_button,
*cad_bxs_rec_datacriacao_button;


GtkWidget *cad_bxs_rec_code_entry;
GtkWidget *cad_bxs_rec_code_id_spin;
GtkWidget *cad_bxs_rec_cli_nome_entry;
GtkWidget *cad_bxs_rec_parcela_spin;
GtkWidget *cad_bxs_rec_datacriacao_entry;
GtkWidget *cad_bxs_rec_datavencimento_entry;
GtkWidget *cad_bxs_rec_parcvalor_entry;
GtkWidget *cad_bxs_rec_bxrvalor_entry;
GtkWidget *cad_bxs_rec_valor_entry;

gchar *cad_bxs_rec_code_gchar;
gchar *cad_bxs_rec_code_id_gchar;
gchar *cad_bxs_rec_cli_gchar;
gchar *cad_bxs_rec_ped_gchar;
gint cad_bxs_rec_parcela_int;
gchar *cad_bxs_rec_parcela_gchar;
gchar *cad_bxs_rec_datacriacao_gchar;
gchar *cad_bxs_rec_datavencimento_gchar;
gchar *cad_bxs_rec_valor_gchar;

static struct {
  int titulo_code;
  int id;
  int cliente_code;
  int parcela;
  char *data;
  float valor_titulo;
  float valor_baixas;
  float abaixar;
  float valor;
}rec_baixas;

static int cad_bxs_rec_alterando=0, cad_bxs_rec_concluindo=0;

int cad_bxs_rec_alterar_fun();
int cad_bxs_rec_cancelar_fun();
int cad_bxs_rec_concluir_fun();

#include "campos/id.c"
#include "campos/titulo.c"
#include "campos/parcela.c"
#include "campos/data_criacao.c"
#include "campos/valor.c"

#include "cancelar.c"
#include "concluir.c"
#include "alterar.c"
