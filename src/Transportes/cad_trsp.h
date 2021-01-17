int trsp_cad_fun();

enum TRSP_COLS{
  TRSP_CODE_COL,
  TRSP_TRANSP_COL,
  TRSP_CLI_COL,
  TRSP_CEPINI_COL,
  TRSP_CEPFIM_COL,
  TRSP_NUM_COL,
  TRSP_ORC_COL,
  TRSP_VLR_COL,
  TRSP_DESC_COL,
  TRSP_FRTPAG_COL,
  TRSP_OBS_COL
};

struct _transporte{
	int code;
	int transportador;
	int cliente;
	char *cep_inicio;
	char *cep_entrega;
	int num;
	int orcamento;
	float vlr;
	float vlr_desc;
	char *obs;
};


GtkWidget *trsp_cad_code_entry, *trsp_cad_code_button;
GtkWidget *trsp_cad_trspcode_entry, *trsp_cad_trsp_entry, *trsp_cad_trsp_button;
GtkWidget *trsp_cad_clicode_entry, *trsp_cad_cli_entry, *trsp_cad_cli_button;
GtkWidget *trsp_cad_cepini_entry, *trsp_cad_cepini_button;
GtkWidget *trsp_cad_cepentr_entry, *trsp_cad_cepentr_button;
GtkWidget *trsp_cad_nument_entry;
GtkWidget *trsp_cad_orc_entry,*trsp_cad_orc_button;
GtkWidget *trsp_cad_vlrfrt_entry;
GtkWidget *trsp_cad_descfrt_entry;
GtkWidget *trsp_cad_frtpag_check;
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
gint trsp_cad_frtpag_gint=0;

GtkWidget *trsp_cad_concluir_button, *trsp_cad_alterar_button,
*trsp_cad_excluir_button, *trsp_cad_cancelar_button;

static int trsp_cad_concluindo=0, trsp_cad_alterando=0, trsp_cad_rec_alteracao=0;

int trsp_cad_cancelar_fun();
int trsp_cad_alterar_fun();
int trsp_cad_concluir_fun();
int trsp_cad_excluir_fun();
