gboolean timerEvent(void *dataset) {
  enum { HalfTime=8, CycTime=2*HalfTime };
  gulong micros;
  DataStruct *data =dataset;
  double t = fabs(fmod (g_timer_elapsed (data->timer, &micros), CycTime));
  int x = (t*data->w)/HalfTime, y = (t*data->h)/HalfTime;
  gtk_window_move (GTK_WINDOW(data->window),
  t<HalfTime? x : 2*data->w-x, t<HalfTime? y : 2*data->h-y);
  return TRUE; /* Keep timeout running */
}


int gtk_window_set_transition_animation(GtkWidget *window){
  GdkScreen *gds;
  DataStruct data;
  data.timer = g_timer_new();
  data.window = window;
  gtk_window_set_default_size (GTK_WINDOW(data.window), 200, 150);
  gds = gdk_screen_get_default ();  /* Get pointer to screen  */
  data.w = gdk_screen_get_width (gds);  /* Find out screen width  */
  data.h = gdk_screen_get_height (gds); /* Find out screen height */
  g_timeout_add(3, timerEvent, &data);  /* Create .003 sec timer   */
  return 0;
}
