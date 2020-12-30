#define ABRIR_MENU_TECLA GDK_KEY_Control_L
#define SAIR_MENU_TECLA GDK_KEY_Escape

int menu_icon_views_wnd();

void menu_icon_view_select(GtkIconView *icon_view, GtkTreePath *path, gpointer data);

GtkWidget *menu_notebook;

static int menu_notebook_atual_pos=0;
