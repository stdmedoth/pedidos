#define MAX_DATE_LEN 15

char dia_sys[MAX_DATE_LEN/3];
char mes_sys[MAX_DATE_LEN/3];
char ano_sys[MAX_DATE_LEN/3];
char data_sys[MAX_DATE_LEN];

GtkWidget *desktop_calendar;
GtkWidget *desktop_calendar_entry;

void get_sysdata_from_calendar(GtkCalendar *calendar, gpointer data_entry);
void desktop_calendar_reset(GtkWidget *button, gpointer calendar);
GtkWidget *get_desktop_calendario();
int pegar_data();
