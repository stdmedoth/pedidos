int load_styles(){
	abrir_css(DESKTOP_STYLE);
	abrir_css(MAIN_STYLE);
	abrir_css(KANBAN_STYLE);
	abrir_css(PDV_STYLE);
	return 0;
}

int abrir_css(char *path){
	GdkDisplay *display;
	GtkCssProvider *fornecedor;
	GFile *arquivo;
	GError *erro=NULL;
	GdkScreen *screen;

	fornecedor = gtk_css_provider_new();
	arquivo    = g_file_new_for_path(path);
	if(!arquivo){
		popup(NULL,"Não foi possível abrir estilos\n");
		return 1;
	}

	screen = gdk_screen_get_default();
	if(screen){
		gtk_style_context_add_provider_for_screen(screen,GTK_STYLE_PROVIDER(fornecedor),GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		gtk_css_provider_load_from_file(fornecedor,arquivo,&erro);
		if(erro){
			g_print("erro no css: %i %s\n",erro->code,erro->message);
			return 1;
		}
	}

	g_object_unref(fornecedor);

	return 0;
}
