char *req_prod_get_prior_name(int prior){
  switch (prior) {
    case REQ_BAIXA_PRIOR:
      return "Prioridade baixa";
    case REQ_MEDIA_PRIOR:
      return "Prioridade Média";
    case REQ_ALTA_PRIOR:
      return "Prioridade Alta";
  }
  return "Status não identificado";
}
int req_prod_priori_fun(){
  req_prod_prori_int = gtk_combo_box_get_active(GTK_COMBO_BOX(req_prod_prori_combo));

  return 0;
}
