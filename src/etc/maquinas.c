
struct _maquina *maquinas_criar_nova(){
  static struct _maquina maquina;
  struct _maquina *MaquinaPtr = &maquina;
  int hostname_len = 50;
  char *hostname = malloc(hostname_len);
  if(gethostname(hostname,hostname_len)){
    popup(NULL,"Não foi possível identificar máquina");
    return NULL;
  }
  GtkWidget *janela = gtk_dialog_new_with_buttons("Preencha os campos para identificação da máquina",NULL,4,"Criar",GTK_RESPONSE_ACCEPT,"Cancelar",GTK_RESPONSE_CANCEL,NULL);
  gtk_window_set_title(GTK_WINDOW(janela),"Registrando Máquina");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"user-availables");
  gtk_window_set_position(GTK_WINDOW(janela),GTK_WIN_POS_CENTER_ON_PARENT);
  gtk_window_set_keep_above(GTK_WINDOW(janela),TRUE);
  gtk_window_set_position(GTK_WINDOW(janela),3);

  GtkWidget *nome_frame = gtk_frame_new("Nome");
  GtkWidget *ip_frame = gtk_frame_new("IP");
  GtkWidget *hostname_frame = gtk_frame_new("Hostname");
  GtkWidget *ativa_frame = gtk_frame_new("Ativa?");

  GtkWidget *hostname_entry = gtk_entry_new();
  GtkWidget *nome_entry = gtk_entry_new();
  GtkWidget *ip_entry = gtk_entry_new();
  GtkWidget *ativa_check = gtk_check_button_new();

  gtk_container_add(GTK_CONTAINER(hostname_frame),hostname_entry);
  gtk_entry_set_text(GTK_ENTRY(hostname_entry),hostname);

  gtk_container_add(GTK_CONTAINER(nome_frame),nome_entry);
  gtk_container_add(GTK_CONTAINER(ip_frame),ip_entry);
  gtk_container_add(GTK_CONTAINER(ativa_frame),ativa_check);

  GtkWidget *box = gtk_box_new(1,0);
  gtk_box_pack_start(GTK_BOX(box),hostname_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),nome_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),ip_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),ativa_frame,0,0,5);

  GtkWidget *fixed = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed),box,5,5);

  g_signal_connect(hostname_entry,"activate",G_CALLBACK(passar_campo),nome_entry);
  g_signal_connect(nome_entry,"activate",G_CALLBACK(passar_campo),ip_entry);
  g_signal_connect(ip_entry,"activate",G_CALLBACK(passar_campo),ativa_check);

	GtkWidget *fields = gtk_bin_get_child(GTK_BIN(janela));
  gtk_container_add(GTK_CONTAINER(fields),fixed);
  gtk_widget_show_all(janela);
  int resultado = gtk_dialog_run(GTK_DIALOG(janela));
  gchar *hostname_gchar, *nome_gchar, *ip_gchar;
  int ativo_int=0;
  char query[MAX_QUERY_LEN];
  MYSQL_RES *res;
  MYSQL_ROW row;
  switch (resultado) {
    case GTK_RESPONSE_ACCEPT:
      hostname_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(hostname_entry));
      nome_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(nome_entry));
      ip_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(ip_entry));
      if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ativa_check)))
        ativo_int = 1;
      if(!strlen(hostname_gchar) || !strlen(nome_gchar) || !strlen(ip_gchar)){
        popup(NULL,"Necessário preecher todos os campos!");
        gtk_widget_destroy(janela);
        return NULL;
      }
      sprintf(query,"insert into maquinas(hostname,nome,ip,ativa) values('%s', '%s', '%s', %i)", hostname_gchar, nome_gchar, ip_gchar, ativo_int);
      if(enviar_query(query)){
        popup(NULL,"Não foi possível criar máquina");
        gtk_widget_destroy(janela);
        return NULL;
      }
      maquina.nome = strdup(nome_gchar);
      maquina.hostname = strdup(hostname_gchar);
      maquina.ip = strdup(ip_gchar);
      maquina.ativa = ativo_int;
      gtk_widget_destroy(janela);
      return MaquinaPtr;
  }
  gtk_widget_destroy(janela);
  return NULL;
}

struct _maquina *maquinas_get_atual(){
  static struct _maquina maquina;
  struct _maquina *MaquinaPtr = &maquina;
  int hostname_len = 50;
  char *hostname = malloc(hostname_len);

  if(gethostname(hostname,hostname_len)){
    popup(NULL,"Não foi possível identificar máquina");
    return NULL;
  }
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  sprintf( query,"select * from maquinas where hostname = '%s'",hostname);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar máquina");
    return NULL;
  }
  if(!(row = mysql_fetch_row(res))){
    popup(NULL,"Máquina ainda não identificada no sistema");
    if(sessao_oper.nivel >= NIVEL_GERENCIAL){
      MaquinaPtr = maquinas_criar_nova();
      if(MaquinaPtr)
        return MaquinaPtr;
    }
    return NULL;
  }

  maquina.id = atoi(row[0]);
  maquina.nome = strdup(row[1]);
  maquina.ip = strdup(row[2]);
  maquina.hostname = strdup(row[3]);
  maquina.ativa = atoi(row[4]);

  return MaquinaPtr;
}
