int ger_janela_aberta(GtkWidget *janela, janelas_info *struct_wnd){

  if(struct_wnd->reg_id == REG_PRINC_WIN)
    iniciar_gerenciador_janela();

  struct_wnd->aberta = 1;
  struct_wnd->qnt_aberta++;

  if(gerenciador_janela())
    return 1;

  if(struct_wnd->reg_id <= REG_WIN_QNT)
    g_print("Janela aberta: %s\n",janelas_nomes[struct_wnd->reg_id]);


  return 0;
}

int ger_janela_fechada(GtkWidget *janela, janelas_info *struct_wnd){

  if(struct_wnd->reg_id == REG_PRINC_WIN)
    iniciar_gerenciador_janela();

  struct_wnd->aberta = 0;
  struct_wnd->qnt_aberta--;

  if(gerenciador_janela())
    return 1;

  if(struct_wnd->reg_id <= REG_WIN_QNT)
    g_print("Janela fechada: %s\n",janelas_nomes[struct_wnd->reg_id]);

  return 0;
}

int iniciar_gerenciador_janela(){

  for(int cont=0;cont<REG_WIN_QNT;cont++){
    janelas_gerenciadas.vetor_janelas[cont].reg_id  = 0;
    janelas_gerenciadas.vetor_janelas[cont].qnt_aberta = 0;
    janelas_gerenciadas.vetor_janelas[cont].qnt_fechada = 0;
    janelas_gerenciadas.vetor_janelas[cont].aberta = 0;

    if(janelas_gerenciadas.vetor_janelas[cont].aberta)
        gtk_widget_destroy(janelas_gerenciadas.vetor_janelas[cont].janela_pointer);

    janelas_gerenciadas.vetor_janelas[cont].janela_pointer = NULL;
  }

  janelas_gerenciadas.principal.aberta = 0;
  janelas_gerenciadas.principal.qnt_aberta = 0;
  janelas_gerenciadas.fundo_inicializacao.aberta = 0;
  janelas_gerenciadas.fundo_inicializacao.qnt_aberta = 0;

  return 0;
}

int gerenciador_janela(){

  for(int cont=0;cont<REG_WIN_QNT;cont++){
      if(janelas_gerenciadas.vetor_janelas[cont].qnt_aberta>MAX_WND1_ABRT){
        janelas_gerenciadas.vetor_janelas[cont].qnt_aberta = 1;
        if(janelas_gerenciadas.vetor_janelas[cont].janela_pointer)
          if(GTK_WINDOW(janelas_gerenciadas.vetor_janelas[cont].janela_pointer)){
            gtk_window_present(GTK_WINDOW(janelas_gerenciadas.vetor_janelas[cont].janela_pointer));
            return 1;
          }
      }
  }

  return 0;
}
