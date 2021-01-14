int init_logger(){
  g_timeout_add(2000, app_tracelog, NULL);
  return 0;
}

int app_tracelog(){
  FILE *tracelog_file = fopen(APP_TRACELOG, "w+");
  if(!tracelog_file){
    popup(NULL,"Não foi possível abrir o arquivo de tracelog");
    encerrando();
    return FALSE;
  }

  if(tracelog_function_name)
    fprintf(tracelog_file, "Função: %s()\n",(char*) NOT_NULL(tracelog_function_name));

  if(tracelog_wnd_name){
    fprintf(tracelog_file, "Ultima Janela: %s\n", (char*)NOT_NULL(tracelog_wnd_name));
  }

  fclose(tracelog_file);
  return G_SOURCE_CONTINUE ;
}

void tracelogger_set_func_name(gchar *func_name){
  if(func_name)
    tracelog_function_name = strdup(func_name);
}

void tracelogger_set_widget_name(gchar *widget_name){
  if(widget_name)
    tracelog_widget_name = strdup(widget_name);
}

void tracelogger_set_obj_name(gchar *obj_name){
  if(obj_name)
    tracelog_obj_name = strdup(obj_name);
}

void tracelogger_set_wnd_name(gchar *wnd_name){
  if(wnd_name)
    tracelog_wnd_name = strdup(wnd_name);
}
