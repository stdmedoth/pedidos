GtkWidget *est_said_cod_entry;
GtkWidget *est_said_prod_entry;
GtkWidget *est_said_qnt_entry;
GtkWidget *est_said_tipo_combo;
GtkWidget *est_said_data_entry;
GtkWidget *est_said_client_entry;

GtkWidget *est_said_est_combo;
gint est_said_est_int;

GtkWidget *est_said_ped_entry;
GtkWidget *est_said_obs_view;
GtkWidget *est_said_campo_nome_prod;
GtkWidget *est_said_campo_nome_client;
GtkWidget *est_said_psqcod_button;

gint est_said_tipo_int, mov_said_est_limit=0;

GtkWidget *est_said_confirma_button,
*est_said_cancela_button,
*est_said_altera_button,
*est_said_exclui_button;

gchar *est_said_cod_gchar,
*est_said_prod_gchar,
*est_said_qnt_gchar,
*est_said_data_gchar,
*est_said_client_gchar,
*est_said_ped_gchar,
*est_said_obs_gchar;

static int alterando_mov_said_est=0, concluindo_mov_said_est=0, cancelando_mov_said_est =0;

void est_said_confirmar_fun();
void est_said_cancelar_fun();
void est_said_alterar_fun();


int est_said_produto_fun();
int est_said_qnt_fun();
int est_said_est_fun();

void inicializar_saidas();

int est_saidas();
