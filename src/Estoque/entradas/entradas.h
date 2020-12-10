static GtkWidget *est_ent_cod_entry,
*est_ent_prod_entry,
*est_ent_ped_entry,
*est_ent_qnt_entry,
*est_ent_tipo_combo,
*est_ent_data_entry,
*est_ent_client_entry;

GtkWidget *est_ent_est_combo;
gint est_ent_est_int;
gint cancelando_mov_ent_est;

static GtkWidget *est_ent_campo_nome_prod,
*est_ent_campo_nome_client;

int est_ent_day_int,
est_ent_mon_int,
est_ent_year_int;

static gint est_ent_tipo_int;

GtkWidget *est_ent_confirma_button,
*est_ent_cancela_button,
*est_ent_altera_button,
*est_ent_exclui_button;

static gchar *est_ent_cod_gchar,
*est_ent_prod_gchar,
*est_ent_qnt_gchar,
*est_ent_data_gchar,
*est_ent_client_gchar,
*est_ent_ped_gchar;

static int alterando_mov_ent_est=0, concluindo_mov_ent_est=0;

enum{
  COD_MOV_EST,
  EST_MOV_EST,
  PED_MOV_EST,
  CLI_MOV_EST,
  PROD_MOV_EST,
  ENTS_MOV_EST,
  SAID_MOV_EST,
  DATA_MOV_EST,
  TIPO_MOV_EST
};

int est_entradas();
void est_ent_confirmar_fun();
void est_ent_cancelar_fun();
void est_ent_alterar_fun();
