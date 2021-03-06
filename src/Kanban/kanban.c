#include "kanban.h"
GtkWidget *kanban_get_checkboxs(int cartao_code){
  GtkWidget *check_boxs, *boxs;
  check_boxs = gtk_box_new(1,0);
  boxs = gtk_box_new(0,0);

  return boxs;
}

int kanban_rem_cart(GtkWidget *button, gpointer data){
  //remover o widget pelo nome (setar id no name do widget)

  return 0;
}

char *kanban_cart_get_titulo(int cart_code){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  sprintf(query,"select titulo from cartao where code = %i",cart_code);
  if(!(res = consultar(query))){
    return NULL;
  }
  if(!(row = mysql_fetch_row(res))){
    return NULL;
  }
  return row[0];
}

char *kanban_cart_get_data_entrega(int cart_code){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  sprintf(query,"select DATE_FORMAT(data_entrega,'%%d/%%m/%%Y') from cartao where code = %i",cart_code);
  if(!(res = consultar(query))){
    return NULL;
  }
  if(!(row = mysql_fetch_row(res))){
    return NULL;
  }
  return row[0];
}

char *kanban_cart_get_descricao(int cart_code){
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  sprintf(query,"select descricao from cartao where code = %i",cart_code);
  if(!(res = consultar(query))){
    return NULL;
  }
  if(!(row = mysql_fetch_row(res))){
    return NULL;
  }
  return row[0];
}

int kanban_add_cart(GtkWidget *button, gpointer data){
  //adicionar nome no widget para que seja possível remover

  GtkWidget *cartao_fixed = gtk_fixed_new();
  GtkWidget *cartao_box = gtk_box_new(1,0);
  gtk_widget_set_name(cartao_box,"cartao-box");
  GtkWidget *titulo_box = gtk_box_new(1,0);
  gtk_widget_set_name(titulo_box,"titulo-box");
  GtkWidget *data_entrega_box = gtk_box_new(1,0);
  gtk_widget_set_name(data_entrega_box,"data-entrega-box");
  GtkWidget *descricao_box = gtk_box_new(1,0);
  gtk_widget_set_name(descricao_box,"descricao-box");
  GtkWidget *opcoes_button = gtk_button_new();
  GtkWidget *opcoes_fixed = gtk_fixed_new();
  gtk_button_set_image(GTK_BUTTON(opcoes_button),gtk_image_new_from_icon_name("open-menu",GTK_ICON_SIZE_BUTTON));
  gtk_fixed_put(GTK_FIXED(opcoes_fixed),opcoes_button,20,0);
  GtkWidget *linha1 = gtk_box_new(0,0);

  int cart_code;
  if(data){
    char *id = malloc(strlen(data)+5);
    sscanf(data,"cartao-%s",id);
    cart_code = atoi(id);
  }else{
    cart_code = 0;
  }
  GtkWidget *checkboxs = kanban_get_checkboxs(cart_code);
  GtkWidget *titulo_wdt, *data_entrega_wdt, *descricao_wdt;
  gchar *titulo_gchar = kanban_cart_get_titulo(cart_code);

  titulo_wdt = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(titulo_wdt),"Título");
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(titulo_wdt),GTK_ENTRY_ICON_PRIMARY,"insert-text");

  if(titulo_gchar){
    gtk_entry_set_text(GTK_ENTRY(titulo_wdt),titulo_gchar);
    gtk_editable_set_editable(GTK_EDITABLE(titulo_wdt),FALSE);
  }

  gchar *data_entrega_gchar = kanban_cart_get_data_entrega(cart_code);
  data_entrega_wdt = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(data_entrega_wdt),"Data Entrega");
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(data_entrega_wdt),GTK_ENTRY_ICON_PRIMARY,"appointment-soon");

  if(data_entrega_gchar){
    gtk_entry_set_text(GTK_ENTRY(data_entrega_wdt),data_entrega_gchar);
    gtk_editable_set_editable(GTK_EDITABLE(data_entrega_wdt),FALSE);
  }

  gchar *descricao_gchar = kanban_cart_get_descricao(cart_code);

  descricao_wdt = gtk_text_view_new();
  GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(descricao_wdt));
  if(descricao_gchar){
    gtk_text_buffer_set_text(buffer, descricao_gchar, strlen(descricao_gchar));
  }else{
    descricao_gchar = malloc(2);
    strcpy(descricao_gchar,"");
    gtk_text_buffer_set_text(buffer, descricao_gchar, strlen(descricao_gchar));
  }
  gtk_widget_set_size_request(descricao_wdt,100,100);

  int pos = kanban_cart_get_free_pos();
  if(pos==-1){
    return 1;
  }
  kanban_carts_pos[pos] = 1;
  gtk_box_pack_start(GTK_BOX(titulo_box),titulo_wdt,0,0,5);
  gtk_box_pack_start(GTK_BOX(data_entrega_box),data_entrega_wdt,0,0,5);
  gtk_box_pack_start(GTK_BOX(descricao_box),descricao_wdt,0,0,5);

  gtk_box_pack_start(GTK_BOX(linha1),titulo_box,0,0,5);
  gtk_box_pack_start(GTK_BOX(linha1),opcoes_fixed,0,0,5);

  gtk_box_pack_start(GTK_BOX(cartao_box),linha1,0,0,5);
  gtk_box_pack_start(GTK_BOX(cartao_box),data_entrega_box,0,0,5);
  gtk_box_pack_start(GTK_BOX(cartao_box),descricao_box,0,0,5);
  gtk_box_pack_start(GTK_BOX(cartao_box),checkboxs,0,0,5);
  gtk_widget_set_size_request(cartao_box,250,250);
  gtk_fixed_put(GTK_FIXED(cartao_fixed), cartao_box, 20,20);

  gtk_grid_attach(GTK_GRID(cartoes_grid),cartao_fixed,pos,0,1,1);
  gtk_widget_show_all(cartoes_grid);
  return 0;
}

void kanban_cart_free_all_pos(){
  for(int cont=0;cont<MAX_CARTS_QNT;cont++){
    kanban_carts_pos[cont] = 0;
  }
}

int kanban_cart_get_free_pos(){
  for(int cont=0;cont<MAX_CARTS_QNT;cont++){
    if(!kanban_carts_pos[cont])
      return cont;
  }
  popup(NULL,"Limite máximo de cartões");
  return -1;
}

MYSQL_RES *kanban_get_cartoes(){
  MYSQL_RES *res;
  char query[MAX_QUERY_LEN];
  sprintf(query,"select * from cartao");
  return consultar(query);
}

int kanban_princ_wnd(){

  if(!app_is_ativo())
    return 1;

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWidget *caixa = gtk_box_new(1,0), *kanban_add_cart_fixed = gtk_fixed_new(), *fixed = gtk_fixed_new();

  /*registrando a janela para o reg_win*/
  janelas_gerenciadas.vetor_janelas[KANBAN_PRINC_WND].reg_id = KANBAN_PRINC_WND;
  janelas_gerenciadas.vetor_janelas[KANBAN_PRINC_WND].aberta = 1;
  if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[KANBAN_PRINC_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[KANBAN_PRINC_WND].janela_pointer = janela;

  kanban_add_cart_button = gtk_button_new_with_label("Adicionar novo cartão");
  gtk_widget_set_name(kanban_add_cart_button,"botao-style");
  cartoes_grid = gtk_grid_new();
  cartoes_box = gtk_box_new(0,0);
  cartoes_scroll = gtk_scrolled_window_new(NULL,NULL);

  gtk_widget_set_size_request(caixa,1000,300);
  gtk_widget_set_size_request(cartoes_box,1000,300);
  gtk_widget_set_size_request(cartoes_scroll,1000,300);

  MYSQL_RES *res = kanban_get_cartoes();
  MYSQL_ROW row;
  char *name = malloc(20);

  kanban_cart_free_all_pos();
  kanban_carts_qnt=0;
  if(res){
    while((row = mysql_fetch_row(res))){
      if(row[0]){
        sprintf(name,"cartao-%s",row[0]);
        kanban_add_cart(NULL,name);
        kanban_carts_qnt++;
      }
    }
  }

  gtk_fixed_put(GTK_FIXED(kanban_add_cart_fixed),kanban_add_cart_button,10,10);
  gtk_grid_attach(GTK_GRID(cartoes_grid),kanban_add_cart_fixed,MAX_CARTS_QNT,0,1,1);
  gtk_box_pack_start(GTK_BOX(cartoes_box),cartoes_grid,0,0,0);
  gtk_container_add(GTK_CONTAINER(cartoes_scroll),cartoes_box);
  gtk_box_pack_start(GTK_BOX(caixa),cartoes_scroll,0,0,0);
  gtk_fixed_put(GTK_FIXED(fixed),caixa,10,10);
  gtk_container_add(GTK_CONTAINER(janela),fixed);

  //g_signal_connect(janela,"size-allocate",G_CALLBACK(auto_hmover_scroll),cartoes_scroll);
  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[KANBAN_PRINC_WND]);
  g_signal_connect(kanban_add_cart_button,"clicked",G_CALLBACK(kanban_add_cart),NULL);

  gtk_widget_show_all(janela);
  return 0;
}
