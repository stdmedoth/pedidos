int suporte_princ_exclui_post(GtkWidget *button, int posicao){
  char query[MAX_QUERY_LEN];

  sprintf(query,"delete from suporte_posts where code = %i",posicao);
  if(enviar_query(query)!=0){
    popup(NULL,"Não foi possivel escrever título");
    return 1;
  }

  gtk_grid_remove_row(GTK_GRID(suport_grid),posicao);
  return 0;
}

int suporte_princ_atualiza_title(GtkWidget *entry, int posicao){
  MYSQL_RES *res;
  MYSQL_ROW row;

  char query[MAX_QUERY_LEN];

  gchar *title = (gchar*)gtk_entry_get_text(GTK_ENTRY(entry));
  if(!title){
    title = malloc(2);
    strcpy(title,"");
  }

  sprintf(query,"select * from suporte_posts where code = %i",posicao);

  if((res = consultar(query))==NULL)
    return 1;

  if((row = mysql_fetch_row(res))==NULL){
    sprintf(query,"insert into suporte_posts(code,operador,titulo,data,status) values (%i,%i,'%s',NOW(),1)",posicao,sessao_oper.code,title);
    if(enviar_query(query)!=0){
      popup(NULL,"Não foi possivel escrever título");
      return 1;
    }
    return 0;
  }

  sprintf(query,"update suporte_posts set titulo = '%s' where code = %i",title,posicao);
  if(enviar_query(query)!=0){
    popup(NULL,"Não foi possivel atualizar o título");
    return 1;
  }

  return 0;
}
int suporte_princ_atualiza_descr(GtkTextView *text_view, GdkEvent *event, int posicao){

  MYSQL_RES *res;
  MYSQL_ROW row;
  GtkTextBuffer *buffer;
  GtkTextIter inicio,fim;
  char query[MAX_QUERY_LEN],*text;

  buffer = gtk_text_view_get_buffer(text_view);
  gtk_text_buffer_get_bounds(buffer,&inicio,&fim);
  text = gtk_text_buffer_get_text(buffer,&inicio,&fim,TRUE);

  if(!text){
    text = malloc(2);
    strcpy(text,"");
  }

  sprintf(query,"select * from suporte_posts where code = %i",posicao);

  if((res = consultar(query))==NULL)
    return 1;

  if((row = mysql_fetch_row(res))==NULL){
    sprintf(query,"insert into suporte_posts(code,operador,descricao,data,status) values (%i,%i,'%s',NOW(),1)",posicao,sessao_oper.code,text);
    if(enviar_query(query)!=0){
      popup(NULL,"Não foi possivel escrever descricao");
      return 1;
    }
    return 0;
  }

  sprintf(query,"update suporte_posts set descricao = '%s' where code = %i",text,posicao);
  if(enviar_query(query)!=0){
    popup(NULL,"Não foi possivel atualizar a descricao");
    return 1;
  }

  return 0;
}
