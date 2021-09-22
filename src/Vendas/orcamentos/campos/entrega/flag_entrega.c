int orc_flag_entrega(){

  if(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(orc_flag_entrega_check))){
    //orc_srv_transp_cancelar_fun();
    gtk_widget_hide(orc_entrega_campos_widget);
    orc_com_entrega = 0;
  }else{
    gtk_widget_show_all(orc_entrega_campos_widget);
    orc_com_entrega = 1;
  }

  return 0;
}
