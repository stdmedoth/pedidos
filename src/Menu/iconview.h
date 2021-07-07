#define ABRIR_MENU_TECLA GDK_KEY_Control_L
#define SAIR_MENU_TECLA GDK_KEY_Escape

int menu_icon_views_wnd();

GtkWidget *menu_notebook;

static int menu_notebook_atual_pos=0;

#include "cad_ico.h"
#include "est_ico.h"
#include "vnd_ico.h"
#include "cmp_ico.h"
#include "fin_ico.h"
#include "mkt_ico.h"
#include "rel_ico.h"
#include "tcn_ico.h"
