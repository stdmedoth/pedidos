int cotacao_cancelar_fun(){

  char task[12];
  cotac_alterando = 0;
  cotac_concluindo = 0;
  cotac_excluindo = 0;
  cotac_gerresultado = 0;
  sprintf(task,"%i",tasker("cotacoes"));
  gtk_entry_set_text(GTK_ENTRY(cotac_code_entry),task);
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(cotac_descricao_view));
  gtk_text_buffer_set_text(buffer,"",0);
  gtk_combo_box_set_active(GTK_COMBO_BOX(cotac_status_combo),0);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cotac_publica_check),FALSE);
  gtk_entry_set_text(GTK_ENTRY(cotac_partc_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cotac_data_entry),"");
  gtk_entry_set_text(GTK_ENTRY(cotac_validade_entry),"");
  gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cotac_partc_combo),0,"nulo","Escolher");
  gtk_combo_box_set_active(GTK_COMBO_BOX(cotac_partc_combo),0);

  struct _Terceiros *Participantes = cotac_get_participantes();

  gtk_combo_box_text_remove_all(GTK_COMBO_BOX_TEXT(cotac_partc_combo));
  gtk_combo_box_text_insert(GTK_COMBO_BOX_TEXT(cotac_partc_combo),0,"nulo","Escolher");
  gtk_combo_box_set_active(GTK_COMBO_BOX(cotac_partc_combo),0);

  if(Participantes){
    for(int participantes_pos=0; participantes_pos<Participantes->qnt; participantes_pos++){
      int participante_index = Participantes->terceiro[participantes_pos].index;
      g_print("Limpando itens do fornecedor %i\n",Participantes->terceiro[participantes_pos].code);
      cotac_container_exists[participante_index] = 0;
      for(int cont=0;cont<MAX_COTAC_ITENS;cont++){
        if(cotac_ativo[participante_index][cont]){
          cotac_ativo[participante_index][cont] = 0;
          cotac_produto_inserido[participante_index][cont] = 0;
          gtk_grid_remove_row(GTK_GRID(cotac_itens_grid[participante_index]),0);
        }
      }
      cotac_container_exists[participante_index] = 0;
      gtk_grid_remove_column(GTK_GRID(cotac_partc_itens),0);
    }
    gtk_grid_insert_column(GTK_GRID(cotac_partc_itens),0);
  }

  return 0;
}
