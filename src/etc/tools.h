int is_texto(char *texto);

char *text_to_html(char *texto);

char *formatar_data(char *data);

int file_logger(char *string);

void receber_psq_code_space(GtkTreeView *treeview, GtkTreePath *path,  GtkTreeViewColumn *column, GtkWidget *window);

void mover_scroll(GtkWidget *widget, GtkWidget *scroll_window);

char *get_elem_from_path(char *path);

void get_filename_to_entry(GtkFileChooserButton *fchooser, GtkEntry *entry);

void encerrando();

int close_window_callback(GtkWidget *widget,gpointer *ponteiro);

char *randomizar_string();

int autologger(char *string);

static void popup(GtkWidget *widget,gchar *string);

MYSQL_RES *consultar(char *query);

int enviar_query(char *query);

int tasker(char *table);

char *infos(int pos);

int configurar_parametros();

char *tipo_ter_num_to_str(int num);

GtkWidget *popup_fechar;

char *ped_status_from_int(int code);

char *status_tit_str(int status);

int aviso_de_baixa_fin();

int cep_nao_existente_fun(gchar *cep);

xmlNodePtr confirmar_envio_email(gchar *destino, gchar *conteudo);
