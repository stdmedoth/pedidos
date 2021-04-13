void get_monitor_sizes(){
	GdkRectangle workarea = {0};
	GdkDisplay *display = gdk_display_get_default();
	GdkMonitor *monitor = gdk_display_get_primary_monitor(display);
	gdk_monitor_get_workarea(monitor, &workarea);

	monitor_width = workarea.width;
	monitor_heigth = workarea.height;
	
	desktop_width = monitor_width - 80;
	desktop_heigth = monitor_heigth - 32;
}