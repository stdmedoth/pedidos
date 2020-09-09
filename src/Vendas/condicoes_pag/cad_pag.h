int cad_pag(void);

static GtkWidget *pag_psq_cod_button;
static GtkWidget *pag_cod_entry,*pag_nome_entry,*pag_parc_spin,*pag_parc_qnt_spin,*pag_tipo_combo,*pag_init_spin;
static GtkWidget *pag_cod_frame,*pag_nome_frame,*pag_parc_frame,*pag_parc_qnt_frame,*pag_tipo_frame,*pag_init_frame;
static GtkWidget *pag_cod_fixed,*pag_nome_fixed,*pag_parc_fixed,*pag_parc_qnt_fixed,*pag_tipo_fixed,*pag_init_fixed;
static GtkWidget *pag_dia_fixo_fixed,*pag_dia_fixo_check,*pag_dia_fixo_box;
gint pag_dia_fixo_int=0;

static int pag_concluindo = 0;
static int pag_alterando = 0;

static gchar *pag_cod_gchar, *pag_nome_gchar;
static gint pag_parc_int,pag_parc_qnt_int,pag_tipo_int,pag_init_int;

static GtkWidget *pag_datas_tree,
*pag_datas_fixed,
*pag_datas_frame,
*pag_datas_box,
*pag_datas_entry,
*pag_psq_datas_button,
*pag_psq_datas_box;

GtkTreeStore *pag_datas_model;
static GtkWidget *pag_grid;

static GtkWidget *pag_confirmar_button,
*pag_alterar_button,
*pag_cancelar_button,
*pag_excluir_button;
