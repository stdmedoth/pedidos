int PopupBinario(char *mensagem, char *positivo, char *negativo);

void popup(GtkWidget *widget,gchar *string);

void reportar_encerramento_brusco();

gpointer carregando_wnd();

xmlNodePtr confirmar_envio_email(gchar *destino, gchar *conteudo);

char *get_text_from_input(char *text, GtkWidget *parent_wnd);

void progress_bar_init();

static GtkWidget *global_progress_bar_widget, *global_progress_bar_window;
static gint global_progress_bar_active = 0, global_progress_bar_active_changed = 0;

#define GLOBAL_PROGRESS_BAR_DEFAULT_TXT "..."
static gchar *global_progress_bar_text = GLOBAL_PROGRESS_BAR_DEFAULT_TXT;
