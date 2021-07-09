#define RANDOM_STRING_SIZE 10
#define DEFAULT_ERROR_CODE 4321


GtkWidget*find_child(GtkWidget* parent, const gchar* name);

#define ENUM_NAME(x) #x
#define ENUM_TO_STR(x) ENUM_NAME(x)

static int alt_pressionado = 0;

static int logging = 0;

void remover_barra_n(char *string);

void menu_icon_view_select(GtkIconView *icon_view, GtkTreePath *path, gpointer data);

void icon_view_select_caller(GtkIconView *icon_view, GtkTreePath *path, gpointer data);
void icon_view_select_caller_with_intarg(GtkIconView *icon_view, GtkTreePath *path, gpointer data);

size_t write_download_file(void *ptr, size_t size, size_t nmemb, FILE *stream);

gboolean atualizar_inatividade_label();

gboolean atualizar_inatividade();

GtkWidget *print_janela;

GtkWidget *msg_abrir_orc_window;

static MYSQL conectar;
static int primeira_conexao=0;

static char **tipo_ter_list;

void passar_campo(GtkWidget *widget,gpointer widget2);

int is_texto(char *texto);

char *inttochar(int intnum);

char *text_to_html(char *texto);

char *formatar_data(char *data);


char  *format_only_num(char *text);

gchar *get_full_ender_from_cep(gchar *cep, int num);

char **array(char *text);

void receber_psq_code_space(GtkTreeView *treeview, GtkTreePath *path,  GtkTreeViewColumn *column, GtkWidget *window);

void auto_vmover_scroll(GtkWidget *widget, GdkRectangle *null, GtkWidget *scroll_window);

void auto_hmover_scroll(GtkWidget *widget, GdkRectangle *null, GtkWidget *scroll_window);

void button_mover_scroll(GtkButton *button, GtkWidget *scroll_window);

char *get_elem_from_path(char *path);

void get_filename_to_entry(GtkFileChooserButton *fchooser, GtkEntry *entry);

int close_window_callback(GtkWidget *widget,gpointer *ponteiro);

char *randomizar_string();

int tasker(char *table);

char *infos(int pos);

int configurar_parametros();


char *tipo_ter_num_to_str(int num);

GtkWidget *popup_fechar;

char *ped_status_from_int(int code);

char *status_tit_str(int status);

int aviso_de_baixa_fin();

int cep_nao_existente_fun(gchar *cep);

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

struct MemoryStruct {
  char *memory;
  size_t size;
};

gchar *get_db_formated_date(gchar *date_row);

void carregar_interface();

char *camel_case(char *text);

void *NOT_NULL(void *pointer);

void enter_code_from_treeview(GtkTreeView *treeview, GtkTreePath *path,  GtkTreeViewColumn *column, GtkWidget *entry);

gboolean only_number_entry(GtkWidget *widget, GdkEventKey  *event, gpointer   user_data);

GtkWidget *get_relat_treeview(gchar *query1, gchar *query2);

void adjustment_mover_scroll(GtkAdjustment *adjustment);

gboolean desktop_window_delete_event(GtkWidget *widget, GdkEvent  *event, gpointer   user_data);

void click_button_callback(GtkWidget *widget,gpointer button);
