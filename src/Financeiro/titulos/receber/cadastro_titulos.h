#define PARC_ID_COL 0
#define PARC_POS_COL 1
#define PARC_BNC_COL 2
#define PARC_DTCR_COL 3
#define PARC_DTVN_COL 4
#define PARC_VLR_COL 5

int cad_titulos_receber();

GtkWidget *cad_rec_cli_psq_button, *cad_rec_tit_psq_button, *cad_rec_ped_psq_button, *cad_rec_datacri_psq_button, *cad_rec_datavenc_psq_button, *cad_rec_bnc_psq_button;

GtkWidget *cad_rec_concluir_button, *cad_rec_cancelar_button, *cad_rec_excluir_button, *cad_rec_alterar_button;

GtkWidget *cad_rec_code_entry;
GtkWidget *cad_rec_cli_entry, *cad_rec_cli_nome_entry;
GtkWidget *cad_rec_bnc_entry, *cad_rec_bnc_nome_entry;
GtkWidget *cad_rec_ped_entry;
GtkWidget *cad_rec_status_combo;
GtkWidget *cad_rec_parcela_spin;
GtkWidget *cad_rec_datacriacao_entry;
GtkWidget *cad_rec_datavencimento_entry;
GtkWidget *cad_rec_valor_entry;

char *cad_rec_code_gchar;
char *cad_rec_cli_gchar;
char *cad_rec_bnc_gchar;
char *cad_rec_ped_gchar;
int cad_rec_status_int;
int cad_rec_parcela_int;
char *cad_rec_datacriacao_gchar;
char *cad_rec_datavencimento_gchar;
char *cad_rec_valor_gchar;

static int cad_rec_alterando=0, cad_rec_concluindo=0;


int cad_rec_cancelar_fun();
int cad_rec_alterar_fun();
int cad_rec_concluir_fun();
