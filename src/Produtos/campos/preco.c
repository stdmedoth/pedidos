int precos_prod_fun(){
  int critica;
  precos_prod =(gchar *) gtk_entry_get_text(GTK_ENTRY(preco_prod_field));
  if(strlen(precos_prod)>MAX_PRECO_LEN)
  {
    popup(NULL,"Preço muito grande");
    gtk_widget_grab_focus(preco_prod_field);
    return 1;
  }

  if(strlen(precos_prod)<=0){
    popup(NULL,"Por favor, insira um preço");
    gtk_widget_grab_focus(preco_prod_field);
    return 1;
  }

  critica = critica_real(precos_prod, preco_prod_field);
  if(critica!=0){
    gtk_widget_grab_focus(preco_prod_field);
    return 1;
  }
  gtk_widget_grab_focus(prod_ncm_entry);
  gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook_cad_prod),2);
  return 0;
}
