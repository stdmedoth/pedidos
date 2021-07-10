int import_tits();

#define MAX_IMP_TITS 200
struct _imprt_titulos{
  char *data;
  char *nome;
  float valor;
}**imprt_titulos;
gchar *imprt_tits_path_gchar;
gint imprt_tits_tipo_int;
GtkWidget *imprt_tits_choose, *imprt_tits_entry, *imprt_tits_tipo_combo;
GtkWidget *imprt_tits_analisar_button, *imprt_tits_cancelar_button, *imprt_tits_importar_button;
