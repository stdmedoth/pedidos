static GtkWidget *est_sld_prod_cod_entry,
*est_sld_est_combo,
*est_sld_min_entry,
*est_sld_data_entry;

static GtkWidget *est_sld_prod_entry;
static GtkWidget *est_sld_prod_nome_entry;

static gint est_sld_prod_est_int;
static gchar *est_sld_prod_cod_gchar,  *est_sld_min_gchar;

int est_sald_est();
int calcula_saldo();
int est_sld_prod_fun();
int est_sld_min_fun();

#include "campos/calcula.c"
#include "campos/produto.c"
#include "campos/saldo_min.c"
#include "campos/estoque.c"
