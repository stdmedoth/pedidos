
struct _maquina *maquinas_criar_nova(){
  struct _maquina maquina;
  struct _maquina *MaquinaPtr = &maquina;
  int hostname_len = 50;
  char *hostname = malloc(hostname_len);
  if(gethostname(hostname,hostname_len)){
    popup(NULL,"Não foi possível identificar máquina");
    return NULL;
  }
  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *hostname_frame = gtk_frame_new("Hostname");
  GtkWidget *nome_frame = gtk_frame_new("Nome");
  GtkWidget *ativa_frame = gtk_frame_new("Ativa?");

  GtkWidget *hostname_entry = gtk_entry_new();
  GtkWidget *nome_entry = gtk_entry_new();
  GtkWidget *ativa_check = gtk_check_button_new();

  gtk_container_add(GTK_CONTAINER(hostname_frame),hostname_entry);
  gtk_entry_set_text(GTK_ENTRY(hostname_entry),hostname);
  gtk_container_add(GTK_CONTAINER(nome_frame),nome_entry);
  gtk_container_add(GTK_CONTAINER(ativa_frame),ativa_check);

  GtkWidget *caixa_opcoes = gtk_box_new(0,0);
  GtkWidget *frame_opcoes = gtk_frame_new("Ações");
  GtkWidget *confirmar_button = gtk_button_new_with_label("Confirmar");
  GtkWidget *cancelar_button = gtk_button_new_with_label("Cancelar");
  GtkWidget *excluir_button = gtk_button_new_with_label("Excluir");

  gtk_box_pack_start(GTK_BOX(caixa_opcoes),confirmar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),cancelar_button,0,0,5);
  gtk_box_pack_start(GTK_BOX(caixa_opcoes),excluir_button,0,0,5);
  gtk_container_add(GTK_CONTAINER(frame_opcoes),caixa_opcoes);

  GtkWidget *box = gtk_box_new(1,0);
  gtk_box_pack_start(GTK_BOX(box),hostname_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),nome_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),ativa_frame,0,0,5);
  gtk_box_pack_start(GTK_BOX(box),frame_opcoes,0,0,5);

  GtkWidget *fixed = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed),box,5,5);

  g_signal_connect(hostname_entry,"activate",G_CALLBACK(passar_campo),nome_entry);
  g_signal_connect(nome_entry,"activate",G_CALLBACK(passar_campo),ativa_check);

  gtk_container_add(GTK_CONTAINER(janela),fixed);
  gtk_widget_show_all(janela);
  return MaquinaPtr;
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
    if(sessao_oper.nivel){
      maquinas_criar_nova();
    }
    return NULL;
  }

  maquina.id = atoi(row[0]);
  strcpy(maquina.nome,row[1]);
  strcpy(maquina.ip,row[2]);
  strcpy(maquina.hostname,row[3]);
  maquina.ativa = atoi(row[4]);

  return MaquinaPtr;
}
