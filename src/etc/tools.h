
int file_logger(char *string);  

void receber_psq_code_space(GtkTreeView *treeview, GtkTreePath *path,  GtkTreeViewColumn *column, GtkWidget *window);

void mover_scroll(GtkWidget *widget, GtkWidget *scroll_window);

char *get_elem_from_path(char *path);

void get_filename_to_entry(GtkFileChooserButton *fchooser, GtkEntry *entry);

void encerrando();

int close_window_callback(GtkWidget *widget,gpointer *ponteiro);

void carregar_navimps();

int iniciar_impressao(char *gerado);

int desenhar_pdf(char *gerando_file);

int iniciar_escolha(GtkWidget *widget , char *gerando_file);

int escolher_finalizacao(char *gerando_file);

char *randomizar_string();

int autologger(char *string);

static void popup(GtkWidget *widget,gchar *string);

MYSQL_RES *consultar(char *query);

int enviar_query(char *query);

int tasker(char *table);

char *infos(int pos);

int configurar_parametros();
