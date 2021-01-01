enum CONTRATOS_COL{
  CONTRATOS_CODE_COL,
  CONTRATOS_CAD_COL,
  CONTRATOS_CMP_COL,
  CONTRATOS_FAT_COL,
  CONTRATOS_EST_COL,
  CONTRATOS_FIN_COL,
  CONTRATOS_MARKT_COL,
  CONTRATOS_REL_COL,
  CONTRATOS_ATIVO_COL,
  CONTRATOS_VENC_COL,
  CONTRATOS_COLS_QNT
};

enum CONTRATOS_MODS{
  CONTRATOS_CAD_MOD,
  CONTRATOS_CMP_MOD,
  CONTRATOS_FAT_MOD,
  CONTRATOS_EST_MOD,
  CONTRATOS_FIN_MOD,
  CONTRATOS_MARKT_MOD,
  CONTRATOS_REL_MOD,
  CONTRATOS_MODS_QNT
};

int cntrats_modulos_fun();
int cntrats_ativo_fun();
int cntrats_vencimento_fun();

int contratos_get_modulos_qnt();

int cntrats_concluir_fun();
int cntrats_cancelar_fun();
int cntrats_alterar_fun();

int contrato_modulos[CONTRATOS_MODS_QNT];
int cntrats_ativo_gint=0;
gint cntrats_alterando=0, cntrats_concluindo=0;

gchar *cntrats_code_gchar;
gchar *cntrats_vencimento_gchar;

int cad_contratos();

GtkWidget *cntrats_code_entry;

GtkWidget *cntrats_concluir_button, *cntrats_alterar_button, *cntrats_cancelar_button;

GtkWidget *cntrats_cadastro_check,
  *cntrats_compras_check,
  *cntrats_faturamento_check,
  *cntrats_estoque_check,
  *cntrats_financeiro_check,
  *cntrats_marketing_check,
  *cntrats_relatorios_check,
  *cntrats_vencimento_entry;

GtkWidget *cntrats_ativo_check;
