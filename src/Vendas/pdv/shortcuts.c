int pdv_atalhos_list_wnd(){


    return 0;
}

gboolean pdv_bind_atalhos(GtkWidget *widget, GdkEventKey *event, gpointer   user_data){

  //if(pdv_venda_atual->operacao_atual != PDV_ADD_ITEM_OPER && pdv_venda_atual->operacao_atual != PDV_REM_ITEM_OPER){
    switch (event->keyval) {
      case GDK_KEY_a:
        pdv_add_item_fun();
        return TRUE;
      case GDK_KEY_r:
        pdv_rem_item_fun(NULL, pdv_itens_treeview);
        return TRUE;
      case GDK_KEY_p:
        pdv_psq_item_fun();
        return TRUE;

      case GDK_KEY_f:
        pdv_fecha_cupom_fun();
        return TRUE;
    }
  //}
  return FALSE;
}
