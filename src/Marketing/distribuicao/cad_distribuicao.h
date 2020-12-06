int mkt_cad_distrib_fun();
int mkt_cad_distrib_cancelar_fun();
int mkt_cad_distrib_alterar_fun();
int mkt_cad_distrib_excluir_fun();
int mkt_cad_distrib_concluir_fun();

gchar *distrib_code_gchar, *distrib_nome_gchar, *distrib_pessoacode_gchar;

GtkWidget *distrib_code_entry, *distrib_nome_entry, *distrib_pessoacode_entry;
GtkWidget *distrib_code_psq_button;

GtkWidget *distrib_pessoas_treeview;
GtkWidget *distrib_pessoas_add_button;

GtkWidget *distrib_confirmar_button;
GtkWidget *distrib_alterar_button;
GtkWidget *distrib_cancelar_button;
GtkWidget *distrib_excluir_button;

#define MAX_MAILDISTRIB_CONTTS 2000
int mkt_cad_distrib_removidos[MAX_MAILDISTRIB_CONTTS];

int mkt_cad_distrib_concluindo = 0, mkt_cad_distrib_alterando = 0;
