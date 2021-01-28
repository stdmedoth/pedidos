int cad_bancos_fun();
GtkWidget *cad_bnc_code_psq_button;
GtkWidget *cad_bancos_code_entry,
*cad_bancos_nome_entry,
*cad_bancos_conta_entry,
*cad_bancos_tipoconta_combo,
*cad_bancos_agencia_entry,
*cad_bancos_usuario_entry,
*cad_bancos_doc_entry,
*cad_bancos_saldoini_entry;

static gchar *cad_bancos_code_gchar,
*cad_bancos_nome_gchar,
*cad_bancos_conta_gchar,
*cad_bancos_agencia_gchar,
*cad_bancos_usuario_gchar,
*cad_bancos_doc_gchar,
*cad_bancos_saldoini_gchar;

static gint cad_bancos_tipoconta_int;
static int cad_bancos_alterando =0, cad_bancos_concluindo =0;
GtkWidget *cad_bancos_concluir_button, *cad_bancos_cancelar_button, *cad_bancos_excluir_button, *cad_bancos_alterar_button;

int cad_bancos_concluir_fun();
int cad_bancos_cancelar_fun();
int cad_bancos_alterar_fun();
int cad_bancos_excluir_fun();

#include "campos/codigo.c"
#include "campos/agencia.c"
#include "campos/documento.c"
#include "campos/nomebanco.c"
#include "campos/numconta.c"
#include "campos/saldo.c"
#include "campos/tipoconta.c"
#include "campos/usuario.c"

#include "cancelar.c"
#include "concluir.c"
#include "alterar.c"
#include "excluir.c"

enum BANCO_COLS{
  BNC_CODE_COL,
  BNC_NOME_COL,
  BNC_CONTA_COL,
  BNC_TTIPO_COL,
  BNC_AGNC_COL,
  BNC_USER_COL,
  BNC_DOC_COL,
  BNC_SLD_COL
};

struct _banco{
  int code;
  gchar *nome;
  gchar *conta;
  int tipo_conta;
  gchar *agencia;
  gchar *nome_usuario;
  gchar *documento;
  float saldo;
};


struct _banco *get_banco(int bnc_code);
