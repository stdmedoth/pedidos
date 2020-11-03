int precos_prod_fun(){
  int critica;
  precos_prod =(gchar *) gtk_entry_get_text(GTK_ENTRY(preco_prod_field));
  if(strlen(precos_prod)>MAX_PRECO_LEN)
  {
    popup(NULL,"Preço muito grande");
    gtk_widget_grab_focus(preco_prod_field);
    return 1;
  }

  if(strlen(precos_prod)<=0)
  {
    if(produtos.criticar.peso==0)
    {
      precos_prod = malloc(MAX_PRECO_LEN);
      strcpy(precos_prod,"");

      critica = critica_real(precos_prod, preco_prod_field);

      gtk_widget_grab_focus(fornecedor_prod_field);
      return 0;
    }

    popup(NULL,"Por favor, insira um Peso");
    gtk_widget_grab_focus(preco_prod_field);
    return 1;

  }
  else
  {
    critica = critica_real(precos_prod, preco_prod_field);

    if(critica!=0)
    {
      gtk_widget_grab_focus(preco_prod_field);
      return 1;
    }

    gtk_widget_grab_focus(prod_concluir_button);
  }
  return 0;
}
