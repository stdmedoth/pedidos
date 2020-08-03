int cad_ceps_code_fun(){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN],*code_task;
  code_task = malloc(MAX_CODE_LEN);

  cad_ceps_code_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(cad_ceps_code_entry));
  if(!strlen(cad_ceps_code_gchar)){
    popup(NULL,"Necessário código");

    sprintf(query,"select MAX(id_logradouro) from logradouro");
    if(!(res=consultar(query))){

      popup(NULL,"Não foi possivel receber task do logradouro");
      return 1;
    }
    if(!(row = mysql_fetch_row(res)))
        strcpy(code_task,"1");
      else
        strcpy(code_task,row[0]);

    gtk_entry_set_text(GTK_ENTRY(cad_ceps_code_entry),code_task);
    gtk_widget_grab_focus(cad_ceps_code_entry);
  }

  gtk_widget_grab_focus(cad_ceps_cep_entry);
  return 0;
}
