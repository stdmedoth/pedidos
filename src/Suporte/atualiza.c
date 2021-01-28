int suporte_princ_exclui_post(GtkWidget *button, int posicao){
  char query[MAX_QUERY_LEN];

  if(posicao>=MAX_POST_QNT || posicao<=0){
    popup(NULL,"Ponteiro para o quadro não foi encontrado");
    return 1;
  }

  sprintf(query,"delete from suporte_posts where code = %i",posicao);
  if(enviar_query(query)!=0){
    popup(NULL,"Não foi possivel deletar post");
    g_print("%s\n",query);
    return 1;
  }

  if(sup_posts_qnt>1)
    gtk_grid_remove_row(GTK_GRID(suport_grid),posicao);
  else
    gtk_grid_remove_column(GTK_GRID(suport_grid),0);

  sup_posts_qnt--;
  return 0;
}

int suporte_princ_atualiza(GtkWidget *entry, int posicao){
  MYSQL_RES *res;
  MYSQL_ROW row;
  GtkTextBuffer *buffer;
  GtkTextIter inicio,fim;
  char *text, query[MAX_QUERY_LEN];
  int status=0, prioridade=0, tipo=0;

  gchar *title = (gchar*)gtk_entry_get_text(GTK_ENTRY(titulo_list[posicao]));
  if(!title){
    title = malloc(2);
    strcpy(title,"");
  }

  status = gtk_combo_box_get_active(GTK_COMBO_BOX(sup_status_combo[posicao]))+1;
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(descr_list[posicao]));
  gtk_text_buffer_get_bounds(buffer,&inicio,&fim);
  text = gtk_text_buffer_get_text(buffer,&inicio,&fim,TRUE);
  prioridade = gtk_spin_button_get_value(GTK_SPIN_BUTTON(sup_priorit_spin[posicao]));
  tipo =  gtk_combo_box_get_active(GTK_COMBO_BOX(sup_tipo_combo[posicao]))+1;

  if(!text){
    text = malloc(2);
    strcpy(text,"");
  }

  sprintf(query,"select * from suporte_posts where code = %i",posicao);

  if(!(res = consultar(query)))
    return 1;

  if((row = mysql_fetch_row(res))==NULL){
    sprintf(query,"insert into suporte_posts(code,operador,titulo,descricao,data,status,tipo,prioridade) values (%i,%i,'%s','%s',NOW(),%i,%i,%i)",posicao,sessao_oper->operador->code,title, text,status,tipo,prioridade);
    if(enviar_query(query)!=0){
      popup(NULL,"Não foi possivel escrever post");
      g_print("%s\n",query);
      return 1;
    }
    gtk_widget_grab_focus(descr_list[posicao]);
    return 0;
  }else{
    sprintf(query,"update suporte_posts set titulo = '%s', descricao = '%s', status = %i, tipo = %i, prioridade = %i where code = %i",title, text,status,tipo,prioridade,posicao);
    if(enviar_query(query)!=0){
      popup(NULL,"Não foi possivel atualizar o post");
      g_print("%s\n",query);
      return 1;
    }
    if(descr_list[posicao])
      gtk_widget_grab_focus(descr_list[posicao]);
  }

  post_recarregar_posts();
  popup(NULL,"Post atualizado");
  return 0;
}
