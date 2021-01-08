#include "Assistente.h"

GtkWidget *assistente_get_page(int page_num){

  char *apresentacao_txt = "Olá! Vamos configurar o seu sistema?";
  char *db_config_txt = "Preencha as configurações do banco de dados";
  char *conclusao_txt = "Processo Finalizado";

  GtkWidget *page;
  GtkWidget *descr_label;

  GtkWidget *bd_server_frame;
  GtkWidget *bd_server_entry;

  GtkWidget *bd_user_frame;
  GtkWidget *bd_user_entry;

  GtkWidget *bd_pass_frame;
  GtkWidget *bd_pass_entry;

  GtkWidget *bd_box;

  switch (page_num) {
    case APRESENTACAO_PAGE:
      page = gtk_box_new(0,0);
      descr_label = gtk_label_new(apresentacao_txt);
      gtk_box_pack_start(GTK_BOX(page), descr_label,0,0,5);
      return page;

    case BD_CONFIG_PAGE:
      page = gtk_box_new(0,0);
      descr_label = gtk_label_new(db_config_txt);

      bd_server_entry = gtk_entry_new();
      bd_server_frame = gtk_frame_new("Endereço do Servidor");
      gtk_container_add(GTK_CONTAINER(bd_server_frame), bd_server_entry);

      bd_user_entry = gtk_entry_new();
      bd_user_frame = gtk_frame_new("Usuário");
      gtk_container_add(GTK_CONTAINER(bd_user_frame), bd_user_entry);

      bd_pass_entry = gtk_entry_new();
      bd_pass_frame = gtk_frame_new("Senha");
      gtk_container_add(GTK_CONTAINER(bd_pass_frame), bd_pass_entry);

      bd_box = gtk_box_new(1,0);
      gtk_box_pack_start(GTK_BOX(bd_box), bd_server_frame,0,0,5);
      gtk_box_pack_start(GTK_BOX(bd_box), bd_user_frame,0,0,5);
      gtk_box_pack_start(GTK_BOX(bd_box), bd_pass_frame,0,0,5);

      gtk_box_pack_start(GTK_BOX(page), descr_label,0,0,5);
      gtk_box_pack_start(GTK_BOX(page), bd_box,0,0,5);

      return page;

    case EMPRESA_CONFIG_PAGE:
      page = gtk_box_new(0,0);
      descr_label = gtk_label_new(apresentacao_txt);
      gtk_box_pack_start(GTK_BOX(page), descr_label,0,0,5);
      return page;

    case CONCLUSAO_PAGE:
      page = gtk_box_new(0,0);
      descr_label = gtk_label_new(conclusao_txt);
      gtk_box_pack_start(GTK_BOX(page), descr_label,0,0,5);
      return page;
  }

  return NULL;
}

int assistente_init(){
  if(!(assistente_wnd = assistente_render_wnd())){
    return 1;
  }

  g_signal_connect(assistente_wnd, "cancel", G_CALLBACK(gtk_main_quit), NULL);
  return 0;
}

GtkWidget *assistente_render_wnd(){

  GtkWidget *wnd = gtk_assistant_new();

  GtkWidget *apres = assistente_get_page(APRESENTACAO_PAGE);
  gtk_assistant_insert_page (GTK_ASSISTANT(wnd), apres, APRESENTACAO_PAGE);
  gtk_assistant_set_page_complete (GTK_ASSISTANT(wnd), apres, TRUE);

  GtkWidget *bdconfig = assistente_get_page(BD_CONFIG_PAGE);
  gtk_assistant_insert_page (GTK_ASSISTANT(wnd), bdconfig, BD_CONFIG_PAGE);

  GtkWidget *concl = assistente_get_page(CONCLUSAO_PAGE);
  gtk_assistant_insert_page (GTK_ASSISTANT(wnd), concl, CONCLUSAO_PAGE);

  gtk_widget_show_all(wnd);
  return wnd;
}
