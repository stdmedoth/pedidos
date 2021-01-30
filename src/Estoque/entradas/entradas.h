static GtkWidget *est_ent_cod_entry,
*est_ent_prod_entry,
*est_ent_ped_entry,
*est_ent_qnt_entry,
*est_ent_tipo_combo,
*est_ent_data_entry,
*est_ent_client_entry,
*est_ent_obs_view;

GtkWidget *est_ent_psqcod_button;

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
*est_ent_ped_gchar,
*est_ent_obs_gchar;

static int alterando_mov_ent_est=0, concluindo_mov_ent_est=0;

int est_entradas();
void est_ent_confirmar_fun();
void est_ent_cancelar_fun();
void est_ent_alterar_fun();
int est_ent_excluir_fun();
