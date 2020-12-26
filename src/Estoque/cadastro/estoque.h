
enum{
  COD_MOV_EST,
  EST_MOV_EST,
  PED_MOV_EST,
  CLI_MOV_EST,
  PROD_MOV_EST,
  ENTS_MOV_EST,
  SAID_MOV_EST,
  DATA_MOV_EST,
  TIPO_MOV_EST,
  OBS_MOV_EST
};


int est_cad_alterando=0;
int est_cad_concluindo=0;

static GtkWidget *est_cod_entry;
static GtkWidget *est_nome_entry;

static GtkWidget *est_concluir_button,
*est_alterar_button,
*est_cancelar_button,
*est_excluir_button,
*est_psq_code_button;

gchar *est_cad_cod_gchar, *est_cad_nome_gchar;

int cad_est();

void inicializar_est();
