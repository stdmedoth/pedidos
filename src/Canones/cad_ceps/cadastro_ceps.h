GtkWidget *cad_ceps_code_entry;
GtkWidget *cad_ceps_cep_entry;
GtkWidget *cad_ceps_descr_entry;
GtkWidget *cad_ceps_tipo_combo;
GtkWidget *cad_ceps_uf_combo;
GtkWidget *cad_ceps_bairro_entry;
GtkWidget *cad_ceps_cid_code_entry;
GtkWidget *cad_ceps_cid_descr_entry;

GtkWidget *cad_cid_id_entry;
GtkWidget *cad_cid_descr_entry;
GtkWidget *cad_cid_uf_combo;
GtkWidget *cad_cid_ibge_entry;
GtkWidget *cad_cid_ddd_entry;

gchar *cad_ceps_code_gchar;
gchar *cad_ceps_cep_gchar;
gchar *cad_ceps_descr_gchar;
gint cad_ceps_tipo_int;
gint cad_ceps_uf_int;
gchar *cad_ceps_bairro_gchar;
gchar *cad_ceps_cid_code_gchar;

gchar *cad_cid_id_gchar;
gchar *cad_cid_descr_gchar;
gint cad_cid_uf_int;
gchar *cad_cid_ibge_gchar;
gchar *cad_cid_ddd_gchar;

GtkWidget *psq_cep_button, *psq_cid_button;

static int cad_ceps_alterando=0,cad_ceps_concluindo=0,cad_ceps_consultando=0;

GtkWidget *cad_cep_confirma_button,
*cad_cep_cancela_button,
*cad_cep_altera_button,
*cad_cep_exclui_button,
*cad_cep_consulta_button;

char uf_list[MAX_UF_QNT][MAX_UF_LEN];

int cad_ceps_uf_qnt=0;

struct _cad_cidade{
  int code;
  gchar *descricao;
  gchar *uf;
  gchar *ddd;
  int code_ibge;

};

struct _cad_cep{
  int code;
  int tipo;
  int numero;
  int id_cidade;

  gchar *cep;
  gchar *bairro;
  gchar *ldescricao;
  gchar *complemento;
  struct _cad_cidade *cidade;
};

enum CEP_COLS{
  CEP_CEP_COL,
  CEP_ID_COL,
  CEP_TIPO_COL,
  CEP_DESCR_COL,
  CEP_IDCIDADE_COL,
  CEP_UF_COL,
  CEP_COMPLEM_COL,
  CEP_DESCRSNUM_COL,
  CEP_DESCRCID_COL,
  CEP_CODIBGE_COL,
  CEP_DESCR_BAIRRO
};

#define MAX_CEP_LEN 10

#define CEP_LEN 8

struct _cad_cep *get_ender_by_cep(gchar *cepcode);

int cad_ceps_consultar_fun();

int cad_ceps_excluir_fun();

int cad_ceps_alterar_fun();

int cad_ceps_concluir_fun();

int cad_ceps_cancelar_fun();

int cad_cep();

struct _cad_cep *ws_consulta_ceps();
struct _cad_cidade *get_cidade_by_ibgecode(int ibgecode);
