#define MAX_COTAC_ITENS 25
#include "interface/itens_container.h"

int cotacao_excluir_fun();

int cotacao_alterar_fun();

int cotacao_concluir_fun();

int cotacao_cancelar_fun();

int cotacao_fun();

int cotac_code_fun();

static int cotac_alterando=0, cotac_concluindo=0;


GtkWidget **cotac_itens_container;
GtkWidget *cotac_code_entry;
GtkWidget *cotac_status_combo;
GtkWidget *cotac_publica_check;
GtkWidget *cotac_partc_entry;
GtkWidget *cotac_data_entry;
GtkWidget *cotac_validade_entry;
GtkWidget *cotac_partc_combo;

gchar *cotac_code_gchar;
gint cotac_status_int;
gint cotac_publica_int;
gchar *cotac_partc_gchar;
gchar *cotac_data_gchar;
gchar *cotac_validade_gchar;
