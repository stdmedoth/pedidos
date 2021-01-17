gchar *tracelog_function_name=NULL;
gchar *tracelog_widget_name=NULL;
gchar *tracelog_wnd_name=NULL;
gchar *tracelog_obj_name=NULL;

GtkWidget *tracelog_ultima_janela;
GtkWidget *tracelog_ultimo_widget;
int init_logger();

int app_tracelog();

void tracelogger_set_func_name(gchar *func_name);

void tracelogger_set_widget_name(gchar *widget_name);

void tracelogger_set_obj_name(gchar *obj_name);

void tracelogger_set_wnd_name(gchar *wnd_name);

int file_logger(char *string);

int autologger(char *string);
