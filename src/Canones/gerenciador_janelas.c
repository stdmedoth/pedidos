int ger_janela_aberta(GtkWidget *janela, janelas_info *struct_wnd){
  g_print("Janela aberta: %s\n",janelas_nomes[struct_wnd->reg_id]);
  struct_wnd->aberta = 1;
  struct_wnd->qnt_aberta++;

  if(gerenciador_janela())
    return 1;

  return 0;
}

int ger_janela_fechada(GtkWidget *janela, janelas_info *struct_wnd){
  g_print("Janela fechada: %s\n",janelas_nomes[struct_wnd->reg_id]);
  struct_wnd->aberta = 0;
  struct_wnd->qnt_aberta--;

  if(gerenciador_janela())
    return 1;

  return 0;
}

int iniciar_gerenciador_janela(){
  for(int cont=0;cont<REG_WIN_QNT;cont++){
    janelas_gerenciadas.vetor_janelas[cont].reg_id  = 0;
    janelas_gerenciadas.vetor_janelas[cont].qnt_aberta = 0;
    janelas_gerenciadas.vetor_janelas[cont].qnt_fechada = 0;
    janelas_gerenciadas.vetor_janelas[cont].aberta = 0;
    janelas_gerenciadas.vetor_janelas[cont].janela_pointer = NULL;
  }
  return 0;
}

int gerenciador_janela(){

  for(int cont=0;cont<REG_WIN_QNT;cont++){
      if(janelas_gerenciadas.vetor_janelas[cont].qnt_aberta>MAX_WND1_ABRT){
        janelas_gerenciadas.vetor_janelas[cont].qnt_aberta = 1;
        gtk_window_activate_focus(GTK_WINDOW(janelas_gerenciadas.vetor_janelas[cont].janela_pointer));
        return 1;
      }
  }



  return 0;
}
