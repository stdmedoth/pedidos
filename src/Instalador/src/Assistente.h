#include <gtk/gtk.h>

enum{
  APRESENTACAO_PAGE,
  BD_CONFIG_PAGE,
  EMPRESA_CONFIG_PAGE,
  CONCLUSAO_PAGE
};

GtkWidget *assistente_wnd;

int assistente_init();

GtkWidget *assistente_render_wnd();
