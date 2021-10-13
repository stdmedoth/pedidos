enum PROD_COLS{
  PROD_COD_COL,
  PROD_NOM_COL,
  PROD_PES_COL,
  PROD_PRC_COL,
  PROD_UND_COL,
  PROD_UND_ATAC_COL,
  PROD_FORN_COL,
  PROD_GRP_COL,
  PROD_GRPNIVEL_COL,
  PROD_NCM_COL,
  PROD_BAR_COL,
  PROD_ICMSCST_COL,
  PROD_PISCST_COL,
  PROD_PISALIQ_COL,
  PROD_COFINSCST_COL,
  PROD_COFINSALIQ_COL,
  PROD_ORIGEM_COL,
  PROD_OBS_COL,
  PROD_DTCRIAC_COL,
  PROD_DTMODIF_COL,
  PROD_COLS_QNT
};

int code_prod();
int altera_prod();

GtkWidget *prod_concluir_button, *prod_alterar_button, *prod_cancelar_button, *prod_excluir_button;
GtkWidget *psq_prod_codigo_button;
int alterando_prod=0, concluindo_prod=0, cancelando_prod=0;
int intgr_prods();
int inicializar_prod();
int  cad_prod();
gchar *codigos_prod=NULL;
gchar *nomes_prod=NULL;
gchar *precos_prod=NULL;
gchar *pesos_prod=NULL;
gchar *unidades_prod=NULL;
gchar *unidades_atac_prod=NULL;
gchar *fornecedores_prod=NULL;
gchar *grupos_prod=NULL;
gchar *observacoes_prod=NULL;
gchar *prod_barra_gchar=NULL;
GtkWidget *grupo_precos_tree;
GtkWidget *notebook_cad_prod;

int tipo_prod=0;
int tipo_class_prod=0;
char *data_alteracao_prod=NULL;
char *data_validade_prod=NULL;
int ativo_flag_prod=0;
float sld_min_lim_prod=0.0;
float sld_at_prod=0.0;

int grupo_nivel=0;
GtkWidget *atualiza_grupo_preco_button, *atualiza_grupo_preco_fixed, *prod_prcwnd_button;

GtkWidget *psq_forn_button,*psq_subgrp_button,*psq_und_button,*psq_qnt_atacado_button;
GtkWidget *psq_forn_img,*psq_subgrp_img,*psq_und_img,*psq_qnt_atacado_img;
GtkWidget *psq_forn,*psq_subgrp,*psq_und,*psq_qnt_atacado;

GtkWidget *codigo_prod_field, *prod_barra_entry, *nome_prod_field,
*preco_prod_field,  *peso_prod_field, *unidade_prod_field,
*fornecedor_prod_field, *grupo_prod_field, *observacao_prod_field,*qnt_atacado_field;

GtkWidget *prod_ncm_entry, *prod_icmscst_combo, *prod_origem_combo;

GtkWidget *prod_pisaliq_entry, *prod_piscst_combo;
GtkWidget *prod_cofinsaliq_entry, *prod_cofinscst_combo;

gchar *prod_ncm_gchar, *prod_icmscst_gchar, *prod_origem_gchar, *prod_cofinscst_gchar, *prod_piscst_gchar;
gchar *prod_cofinsaliq_gchar, *prod_pisaliq_gchar;

GtkWidget *campo_nome_unidade,
*campo_nome_fornecedor,
*campo_nome_grupo,
*campo_nome_ncm,
*campo_nome_qnt_atacado;

GtkWidget *prod_dt_alteracao_entry;

struct _cad_produtos{
  int code;
  char *xNome;
  char *code_barra;
  float peso;
  float preco;
  //int und;
  int grp;
  int NCM;

  struct _und *und;
};

struct _cad_produtos *get_cad_prod(int prod_code);

//produtos
#define PROD_CAD_QUERY "insert into produtos(code, nome, peso, preco, unidades, unidades_atacado ,fornecedor, grupo, grupo_nivel, ncm, code_barra, origem, icmscst, piscst, pisaliq, cofinscst, cofinsaliq, observacoes, dt_criacao, dt_modificacao) values( %s, '%s', %s, %s, %s, %s, %s, %s, %i, %s, %s,'%s', %s, %s, %s, %s, %s, '%s', now(), now());"
#define ARGS_PROD_CAD_QUERY codigos_prod, nomes_prod, pesos_prod, precos_prod, unidades_prod, unidades_atac_prod, fornecedores_prod, grupos_prod, grupo_nivel, prod_ncm_gchar, prod_barra_gchar, prod_origem_gchar, prod_icmscst_gchar, prod_piscst_gchar, prod_pisaliq_gchar, prod_cofinscst_gchar, prod_cofinsaliq_gchar, observacoes_prod
#define PROD_UPD_QUERY "update produtos set nome = '%s', peso = %s, preco = %s, unidades = %s, unidades_atacado = %s,  fornecedor = %s, grupo = %s, grupo_nivel = %i, ncm = %s, code_barra = %s, origem = %s, icmscst = %s, piscst = %s, pisaliq = %s, cofinscst = %s, cofinsaliq = %s, observacoes = '%s', dt_modificacao = now() where code = %s"
#define ARGS_PROD_UPD_QUERY nomes_prod, pesos_prod, precos_prod, unidades_prod, unidades_atac_prod, fornecedores_prod, grupos_prod, grupo_nivel, prod_ncm_gchar, prod_barra_gchar, prod_origem_gchar, prod_icmscst_gchar, prod_piscst_gchar, prod_pisaliq_gchar, prod_cofinscst_gchar, prod_cofinsaliq_gchar, observacoes_prod,codigos_prod
