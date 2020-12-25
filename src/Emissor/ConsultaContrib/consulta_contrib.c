#include "consultar.c"
#include "criar_xml.c"

int consulta_contrib_wnd(struct _terc_infos *contrib){

  GtkWidget *janela = gtk_dialog_new_with_buttons(
    "Consultar Contribuintes",
    NULL,
    GTK_DIALOG_MODAL,
    "OK",  GTK_RESPONSE_ACCEPT,
    "Cancelar", GTK_RESPONSE_REJECT,
    NULL);

  GtkWidget *label = gtk_label_new("Insira o CNPJ e a UF");
  GtkWidget *cnpj_entry = gtk_entry_new();
  GtkWidget *uf_entry = gtk_entry_new();
  GtkWidget *entry_boxs = gtk_box_new(0,0);
  gtk_entry_set_width_chars(GTK_ENTRY(cnpj_entry),20);
  gtk_entry_set_width_chars(GTK_ENTRY(uf_entry),5);
  gtk_entry_set_placeholder_text(GTK_ENTRY(cnpj_entry), "00.000.000/0001-00");
  gtk_entry_set_placeholder_text(GTK_ENTRY(uf_entry), "XX");
  gtk_box_pack_start(GTK_BOX(entry_boxs), cnpj_entry ,0,0,0);
  gtk_box_pack_start(GTK_BOX(entry_boxs), uf_entry ,0,0,0);
  g_signal_connect(cnpj_entry, "activate", G_CALLBACK(passar_campo), uf_entry );
  g_signal_connect(uf_entry, "activate", G_CALLBACK(passar_campo), gtk_dialog_get_widget_for_response(GTK_DIALOG(janela), GTK_RESPONSE_ACCEPT) );

  GtkWidget *box = gtk_dialog_get_content_area(GTK_DIALOG(janela));
  gtk_box_pack_start(GTK_BOX(box), label,0,0,0);
  gtk_box_pack_start(GTK_BOX(box), entry_boxs,0,0,0);

  gchar *cnpj, *formated_cnpj;
  gchar *uf, *formated_uf;
  if(contrib->doc && strlen(contrib->doc)){
    gtk_entry_set_text(GTK_ENTRY(cnpj_entry), contrib->doc);
  }

  gtk_widget_show_all(janela);
  int resultado = gtk_dialog_run (GTK_DIALOG(janela));
  switch(resultado){
    case GTK_RESPONSE_ACCEPT:
      cnpj = (gchar*)gtk_entry_get_text(GTK_ENTRY(cnpj_entry));
      formated_cnpj = strdup(format_only_num(cnpj));
      uf = (gchar*)gtk_entry_get_text(GTK_ENTRY(uf_entry));
      formated_uf = strdup(formatar_littobig(uf));
      if(!strlen(formated_cnpj)){
        popup(NULL,"CNPJ não inserido");
        gtk_widget_destroy(janela);
        return 1;
      }
      if(!strlen(uf)){
        popup(NULL,"UF não inserida");
        gtk_widget_destroy(janela);
        return 1;
      }

      if(consulta_contrib_consulta(formated_cnpj, formated_uf, contrib)){
        gtk_widget_destroy(janela);
        return 1;
      }

      gtk_widget_destroy(janela);
      return 0;

    case GTK_RESPONSE_REJECT:
      gtk_widget_destroy(janela);
      return 1;
  }
  return 1;
}
