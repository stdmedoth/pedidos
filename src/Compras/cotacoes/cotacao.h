#define MAX_COTAC_ITENS 25
#define MAX_PARTC_QNT 10

#include "interface/itens_container.h"

int cotacao_excluir_fun();

int cotacao_alterar_fun();

int cotacao_concluir_fun();

int cotacao_cancelar_fun();

int cotacao_fun();

int cotac_code_fun();

static int cotac_alterando=0, cotac_concluindo=0;


struct _contacao_itens{
  int index;
  int produto;
  int participante;
  float valor;
  float quantidade;
  float total;
};

struct _cotacao{
  int code;
  char *descricao;
  int status;
  int publica;
  char *data;
  char *validade;

  struct _Terceiros *participantes;
  struct _contacao_itens **cotacao_itens;
}*cotacao_new;


GtkWidget **cotac_itens_container;
GtkWidget *cotac_code_entry;
GtkWidget *cotac_descricao_view;
GtkWidget *cotac_status_combo;
GtkWidget *cotac_publica_check;
GtkWidget *cotac_partc_entry;
GtkWidget *cotac_data_entry;
GtkWidget *cotac_validade_entry;
GtkWidget *cotac_partc_combo;

gchar *cotac_code_gchar;
gint cotac_status_int;
gint cotac_publica_int;
gchar *cotac_descricao_gchar;
gchar *cotac_partc_gchar;
gchar *cotac_data_gchar;
gchar *cotac_validade_gchar;

enum{
  COTAC_CODE_COL,
  COTAC_DESCR_COL,
  COTAC_STAT_COL,
  COTAC_PUB_COL,
  COTAC_DATA_COL,
  COTAC_VAL_COL
};
