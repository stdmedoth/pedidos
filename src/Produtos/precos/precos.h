enum PROD_PRC_COLS{
  PRC_CODE_COL,
  PRC_NOME_COL,
  PRC_PROD_COL,
  PRC_VLRFAT_COL,
  PRC_VLRVIST_COL
};

struct _prod_precos{
  int code;
  char *nome;
  int produto;
  float vlr_faturado;
  float vlr_vista;
};

int prod_precos_wnd();
GtkWidget *prod_prc_code_entry,
  *prod_prc_prodcode_entry,
  *prod_prc_nome_entry,
  *prod_prc_vlrfat_entry,
  *prod_prc_vlrvist_entry;

gchar *prod_prc_code_gchar,
*prod_prc_nome_gchar,
*prod_prc_prodcode_gchar,
*prod_prc_vlrfat_gchar,
*prod_prc_vlrvist_gchar;

GtkWidget *prod_prc_codepsq_button, *prod_prc_prodnome_entry, *prod_prc_prodpsq_button;

GtkWidget *prod_prc_concluir_button, *prod_prc_alterar_button, *prod_prc_cancelar_button, *prod_prc_excluir_button;

int prod_precos_concluir_fun();
int prod_precos_alterar_fun();
int prod_precos_cancelar_fun();
int prod_precos_excluir_fun();

int prod_precos_alterando=0, prod_precos_concluindo=0;

int prod_precos_code_fun();
int prod_precos_prod_fun();
int prod_precos_nome_fun();
int prod_precos_vltfat_fun();
int prod_precos_vlrvist_fun();

struct _prod_precos *precos_get_preco(int prc_code);
