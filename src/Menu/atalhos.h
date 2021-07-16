gboolean tecla_menu (GtkWidget *widget, GdkEventKey  *event, gpointer   user_data);
void chama_menu(GtkWidget *widget);
GtkWidget *botao_iniciar;
int controle_menu=0;

#define ABRIR_MENU_TECLA GDK_KEY_Control_L
#define SAIR_MENU_TECLA GDK_KEY_Escape
