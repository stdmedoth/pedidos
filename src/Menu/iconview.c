#include "cad_ico.c"
#include "est_ico.c"
#include "vnd_ico.c"
#include "cmp_ico.c"
#include "fin_ico.c"
#include "mkt_ico.c"
#include "rel_ico.c"
#include "tcn_ico.c"

void menu_icon_view_select(GtkIconView *icon_view, GtkTreePath *path, gpointer data){

  if(menu_notebook && GTK_IS_WIDGET(menu_notebook))
    menu_notebook_atual_pos = gtk_notebook_get_current_page(GTK_NOTEBOOK(menu_notebook));
  if(data && GTK_IS_WIDGET(data)){
    gtk_widget_destroy(data);
  }

}

gboolean desfocar_menu(GtkWidget *widget, GdkEventCrossing  *event, gpointer   user_data){
  
  if((event->mode == GDK_CROSSING_UNGRAB) || (event->mode == GDK_CROSSING_GTK_UNGRAB) ){
    if(widget && GTK_IS_WIDGET(widget)){
      gtk_widget_destroy(widget);
    }
  }

  return TRUE;
}


int menu_icon_views_wnd(){

  GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_container_set_border_width(GTK_CONTAINER(janela), 20);

  janelas_gerenciadas.vetor_janelas[REG_MENU_WND].reg_id = REG_MENU_WND;
  janelas_gerenciadas.vetor_janelas[REG_MENU_WND].aberta = 1;
  if(ger_janela_aberta(fixed_relats_wnd, &janelas_gerenciadas.vetor_janelas[REG_MENU_WND]))
    return 1;
  janelas_gerenciadas.vetor_janelas[REG_MENU_WND].janela_pointer = janela;


  gtk_widget_set_name(janela,"menu_iconview_wnd");
  gtk_window_set_position(GTK_WINDOW(janela),3);
  gtk_window_set_modal(GTK_WINDOW(janela),TRUE);
  gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
  gtk_window_set_decorated(GTK_WINDOW(janela),FALSE);
  gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
  gtk_window_set_title(GTK_WINDOW(janela),"Menu de Opções");
  gtk_window_set_icon_name(GTK_WINDOW(janela),"text-x-generic");


  menu_notebook = gtk_notebook_new();
  GtkWidget *principal = gtk_box_new(0,0);
  GtkWidget *cadastros = cad_menu_get_icon_view();
  GtkWidget *compras = cmp_menu_get_icon_view();
  GtkWidget *estoques = est_menu_get_icon_view();
  GtkWidget *vendas = vnd_menu_get_icon_view();
  GtkWidget *marketing = mkt_menu_get_icon_view();
  GtkWidget *financeiro = fin_menu_get_icon_view();
  GtkWidget *relatorios = rel_menu_get_icon_view();
  GtkWidget *tecnicos = tcn_menu_get_icon_view();

  gtk_box_pack_start(GTK_BOX(principal), gtk_image_new_from_file(LOGO), 0,0,0);
  gtk_box_pack_start(GTK_BOX(principal), gtk_label_new(cad_emp_strc.sobre), 0,0,5);

  gtk_notebook_append_page(GTK_NOTEBOOK(menu_notebook),principal, gtk_label_new("Pedidos"));

  if(ativar.cadastro)
		gtk_notebook_append_page(GTK_NOTEBOOK(menu_notebook),cadastros, gtk_label_new("Cadastros"));

  if(ativar.compras)
		gtk_notebook_append_page(GTK_NOTEBOOK(menu_notebook),compras, gtk_label_new("Compras"));

  if(ativar.faturamento)
		gtk_notebook_append_page(GTK_NOTEBOOK(menu_notebook),vendas, gtk_label_new("Vendas"));

  if(ativar.estoque)
		gtk_notebook_append_page(GTK_NOTEBOOK(menu_notebook),estoques, gtk_label_new("Materiais"));

  if(ativar.financeiro)
		gtk_notebook_append_page(GTK_NOTEBOOK(menu_notebook),financeiro, gtk_label_new("Financeiro"));

  if(ativar.marketing)
		gtk_notebook_append_page(GTK_NOTEBOOK(menu_notebook),marketing, gtk_label_new("Marketing"));

  if(ativar.relatorios)
		gtk_notebook_append_page(GTK_NOTEBOOK(menu_notebook),relatorios, gtk_label_new("Relatórios"));

  if(ativar.tecnicos)
		gtk_notebook_append_page(GTK_NOTEBOOK(menu_notebook),tecnicos, gtk_label_new("Técnico"));

  gtk_notebook_set_tab_pos (GTK_NOTEBOOK(menu_notebook),GTK_POS_RIGHT);
  gtk_notebook_set_show_border (GTK_NOTEBOOK(menu_notebook),TRUE);
  gtk_notebook_set_scrollable (GTK_NOTEBOOK(menu_notebook),TRUE);
  gtk_notebook_popup_enable (GTK_NOTEBOOK(menu_notebook));

  gtk_notebook_set_current_page (GTK_NOTEBOOK(menu_notebook), menu_notebook_atual_pos);
  gtk_notebook_set_group_name (GTK_NOTEBOOK(menu_notebook), "menu_principal");

  gtk_container_add(GTK_CONTAINER(janela),menu_notebook);

  gtk_widget_grab_focus(menu_notebook);

  gtk_widget_add_events(janela, GDK_FOCUS_CHANGE_MASK );
  gtk_widget_add_events(janela, GDK_LEAVE_NOTIFY_MASK );
  gtk_widget_set_can_focus (janela, TRUE);

  g_signal_connect(GTK_WIDGET(janela),"leave-notify-event",G_CALLBACK(desfocar_menu),NULL);

  g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_MENU_WND]);
  g_signal_connect(GTK_WIDGET(janela),"key_press_event",G_CALLBACK(tecla_menu),NULL);
  g_signal_connect(janela,"destroy",G_CALLBACK(chama_menu),NULL);
  gtk_widget_show_all(janela);
  return 0;
}
