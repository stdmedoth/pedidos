static GtkPrintSettings *print_settings = NULL;

static GtkPageSetup *	print_pagesetup = NULL;

int orc_begin_print(GtkPrintOperation *operation, GtkPrintContext   *context, struct _orc *orc);

int orc_draw_page(GtkPrintOperation *operation, GtkPrintContext *context, gint page_nr, struct _orc *orc);

int orc_print_operation_fun(struct _orc *orc, int tipo );

int print_operation_wnd(int (*fun)());
