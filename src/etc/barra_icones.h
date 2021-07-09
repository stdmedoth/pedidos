static int notificacao_pendencias=0;

const int icon_button_width = 75;
const int icon_button_height = 60;

#define ULT_BARRA_POS (ult_barra_pos = ult_barra_pos+65)
int ult_barra_pos = 0;

int barra_icones_add();
int *barra_icones_rem();
GtkWidget *barra_icones_wnd();
