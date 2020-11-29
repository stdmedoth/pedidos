void mp_popup_add_mp(int pos, GtkWidget *grid);
void mp_popup_change_qnt(GtkSpinButton *spin_button, gpointer user_data);
struct _cfe_pgto *get_mp_popup(GtkWidget *parent);

#define MAX_PGTO_QNT 10
#define MAX_CREDEN_QNT 50
int mp_tipospag_qnt=0;
char **tipospag_ids;
char **tipospag_nomes;

int mp_creden_qnt=0;
char **creden_ids;
char **creden_nomes;

int mp_tipospag_pos[MAX_PGTO_QNT];

GtkWidget **mp_popup_code_combo;
GtkWidget **mp_popup_valor_entry;
GtkWidget **mp_popup_creden_combo;
GtkWidget *mp_popup_qnt_entry;
