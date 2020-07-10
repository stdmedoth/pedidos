int pag_tipo_fun(){
  pag_tipo_int = gtk_combo_box_get_active(GTK_COMBO_BOX(pag_tipo_combo));
  if(!pag_tipo_int){
    popup(NULL,"Escolha o modelo de condições");
    return 1;
  }

  return 0;
}
