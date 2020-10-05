enum{
  CONTA_FIXA_NULO=0,
  CONTA_FIXA_DIAS=1,
  CONTA_FIXA_MES=2,
  CONTA_FIXA_TQNT
};

int cad_conta_fixa_cancelar();
int cad_conta_fixa_alterar();
int cad_conta_fixa();

GtkWidget *conta_fix_id_entry;
GtkWidget *conta_fix_descr_entry;
GtkWidget *conta_fix_forn_entry;
GtkWidget *conta_fix_dtini_entry;
GtkWidget *conta_fix_dtend_entry;
GtkWidget *conta_fix_int_entry;
GtkWidget *conta_fix_int_combo;
GtkWidget *conta_fix_valor_entry;

GtkWidget *conta_fix_nomeforn_entry;

GtkWidget *conta_fix_pesq_id;
GtkWidget *conta_fix_pesq_forn;
GtkWidget *conta_fix_pesq_dtini;
GtkWidget *conta_fix_pesq_dtend;

GtkWidget *conta_fix_concluir_button;
GtkWidget *conta_fix_alterar_button;
GtkWidget *conta_fix_deletar_button;
GtkWidget *conta_fix_cancelar_button;

gchar *conta_fix_id_gchar;
gchar *conta_fix_descr_gchar;
gchar *conta_fix_forn_gchar;
gchar *conta_fix_dtini_gchar;
gchar *conta_fix_dtend_gchar;
gchar *conta_fix_int_gchar;
gint conta_fix_int_int;
gint conta_fix_tipo_int;
gchar *conta_fix_valor_gchar;

int conta_fixa_alterando=0, conta_fixa_concluindo=0;
