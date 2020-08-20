int cad_baixas_pagar();

GtkWidget *cad_bxs_pag_cli_psq_button, *cad_bxs_pag_tit_psq_button, *cad_bxs_pag_ped_psq_button, *cad_bxs_pag_datacri_psq_button, *cad_bxs_pag_datavenc_psq_button;

GtkWidget *cad_bxs_pag_concluir_button, *cad_bxs_pag_cancelar_button, *cad_bxs_pag_excluir_button, *cad_bxs_pag_alterar_button;

GtkWidget *cad_bxs_pag_code_entry;
GtkWidget *cad_bxs_pag_cli_entry, *cad_bxs_pag_cli_nome_entry;
GtkWidget *cad_bxs_pag_status_combo;
GtkWidget *cad_bxs_pag_parcela_spin;
GtkWidget *cad_bxs_pag_datacriacao_entry;
GtkWidget *cad_bxs_pag_datavencimento_entry;
GtkWidget *cad_bxs_pag_valor_entry;

char *cad_bxs_pag_code_gchar;
char *cad_bxs_pag_cli_gchar;
char *cad_bxs_pag_ped_gchar;
int cad_bxs_pag_status_int;
int cad_bxs_pag_parcela_int;
char *cad_bxs_pag_datacriacao_gchar;
char *cad_bxs_pag_datavencimento_gchar;
char *cad_bxs_pag_valor_gchar;

static int cad_bxs_pag_alterando=0, cad_bxs_pag_concluindo=0;
