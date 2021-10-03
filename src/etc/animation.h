typedef struct DATA { GTimer *timer; GtkWidget *window; int w, h; }
  DataStruct;

gboolean timerEvent(void *dataset) ;

int gtk_window_set_transition_animation(GtkWidget *window);
