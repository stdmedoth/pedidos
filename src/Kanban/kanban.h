#ifndef PEDIDOS_KANBAN_HEADER
#define PEDIDOS_KANBAN_HEADER

#define MAX_CARTS_QNT 20
int kanban_princ_wnd();

MYSQL_RES *kanban_get_cartoes();

int kanban_rem_cart(GtkWidget *button, gpointer data);

int kanban_add_cart(GtkWidget *button, gpointer data);

GtkWidget *kanban_get_checkboxs(int cartao_code);

char *kanban_cart_get_titulo(int cart_code);

char *kanban_cart_get_data_entrega(int cart_code);

int kanban_cart_get_free_pos();

void kanban_cart_free_all_pos();

int kanban_carts_qnt=0;
int kanban_carts_pos[MAX_CARTS_QNT];

GtkWidget *cartoes_grid, *cartoes_box, *cartoes_scroll, *kanban_add_cart_button;

#endif
