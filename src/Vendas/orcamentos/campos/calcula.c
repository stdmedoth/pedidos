int calcula_prod_orc(GtkWidget *widget, int posicao){

  char query[MAX_QUERY_LEN];
  int tipodesc;

  MYSQL_RES *vetor;
  MYSQL_ROW campos,row;

  ativos[posicao].qnt_f = 0;

  if(codigo_prod_orc(NULL,posicao)){
    g_print("Erro ao passar pelo código do produto\n");
    return 1;
  }

  if(orc_prod_calc_saldo(posicao)){
    g_print("Erro ao calcular saldo\n");
    return 1;
  }

  int prod_code = atoi(codigo_prod_orc_gchar);

  if(!tipo_pag){
    if(preco_prod_orc_calc){
      popup(NULL,"Selecione o tipo de pagamento");
      gtk_widget_grab_focus(orc_pag_cond_entry);
      return 1;
    }
  }

  if(orig_preco_prod_orc(NULL,posicao)){
    g_print("Erro ao passar por origem preço produto\n");
    return 1;
  }

  if(tipo_pag != PAG_FAT && tipo_pag != PAG_VIST){
    popup(NULL,"Selecione o tipo de pagamento");
    gtk_widget_grab_focus(orc_pag_cond_entry);
    return 1;
  }

  switch(valor_orig[posicao]){

    case VLR_ORIG_NUL:
      if(produto_inserido[posicao] == 1 && preco_prod_orc_calc){
        popup(NULL,"Selecione a origem do preço");
      }
      g_print("valor origem zerados\n");
      gtk_widget_grab_focus(orig_preco_prod_orc_combo[posicao]);
      return 1;

    case VLR_ORIG_PROD:
      sprintf(query, "select preco from produtos where code = %s", codigo_prod_orc_gchar);

      if(!(vetor = consultar(query))){
        return 1;
      }

      if(!(campos = mysql_fetch_row(vetor))){
        popup(NULL,"Não foi possível receber preço do produto");
        gtk_widget_grab_focus(orig_preco_prod_orc_combo[posicao]);
        return 1;
      }
      gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[posicao]),strdup(campos[0]));
      break;

    case VLR_ORIG_CLI:
      if(codigo_cli_orc()!=0){
        g_print("Erro no código do cliente\n");
        return 1;
      }

      if(codigo_prod_orc(NULL,posicao)!=0){
        g_print("Erro no código do produto\n");
        return 1;
      }

      if(tipo_pag==PAG_FAT)
        sprintf(query, "select valor_fat from preco_cliente where cliente = %s and produto = %s  ",cliente_orc_gchar , codigo_prod_orc_gchar);

      if(tipo_pag==PAG_VIST)
        sprintf(query, "select valor_vist from preco_cliente where cliente = %s and produto = %s  ",cliente_orc_gchar , codigo_prod_orc_gchar);

      vetor = consultar(query);
      if(vetor == NULL){
        popup(NULL,"Não foi possível  consultar preços por clientes");
        return 1;
      }

      if(!(campos = mysql_fetch_row(vetor)))
      {
        popup(NULL,"Produto sem preço vinculado ao cliente");
        gtk_widget_grab_focus(orig_preco_prod_orc_combo[posicao]);
        return 1;
      }

      gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[posicao]),strdup(campos[0]));
      break;

    case VLR_ORIG_OPER:

      break;

    default:
      if(tipo_pag==PAG_FAT)
        sprintf(query, "select valor_fat from precos where code = %s", orig_preco_prod_orc_gchar);

      if(tipo_pag==PAG_VIST)
        sprintf(query, "select valor_vist from precos where code = %s", orig_preco_prod_orc_gchar);

      vetor = consultar(query);
      if(vetor == NULL){
        popup(NULL,"Não foi possível  consultar preços por tabela");
        return 1;
      }

      if(!(campos = mysql_fetch_row(vetor))){
        popup(NULL,"Produto sem preço vinculado à tabela");
        gtk_widget_grab_focus(orig_preco_prod_orc_combo[posicao]);
        return 1;
      }

      gtk_entry_set_text(GTK_ENTRY(preco_prod_orc_entry[posicao]),strdup(campos[0]));
      break;

  }

  if(!qnt_prod_orc_calc){
    qnt_prod_orc(NULL,posicao);
  }else{
    qnt_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(qnt_prod_orc_entry[posicao]));
  }

  if(!preco_prod_orc_calc){
    preco_prod_orc(NULL,posicao);
  }else{
    preco_prod_orc_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(preco_prod_orc_entry[posicao]));
  }


  if(orc_prod_calc_saldo(posicao))
    return 1;

  if(!recebendo_prod_orc){

    if(orc_estoque.produtos[prod_code]->mov_qnt){
      if(orc_estoque.produtos[prod_code]->saldo_liquido < 0){
        if(orcamentos.criticar.prod_saldo){
          popup(NULL,"Produto com saldo insuficiente");
          return 1;
        }
      }

      if(orc_estoque.produtos[prod_code]->saldo_liquido <= orc_estoque.produtos[prod_code]->saldo_min && aviso_estoque[posicao] == 0){
        if(orcamentos.criticar.prod_saldo_limite){
          popup(NULL,"Aviso de saldo mínimo");
          aviso_estoque[posicao] = 1;
        }
      }
    }
    else{
      if(orcamentos.criticar.prod_movimento){
        popup(NULL,"Sem nenhum movimento");
          return 1;
      }
    }
  }

  if(!preco_prod_orc_calc){
    preco_prod_orc(preco_prod_orc_entry[posicao],posicao);
    critica_real(preco_prod_orc_gchar,preco_prod_orc_entry[posicao]);
  }else{
    preco_prod_orc_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(preco_prod_orc_entry[posicao]));
    if(!strlen(preco_prod_orc_gchar))
      preco_prod_orc_gchar = "0";
  }

  if(!qnt_prod_orc_calc){
    qnt_prod_orc(qnt_prod_orc_entry[posicao],posicao);
    critica_real(qnt_prod_orc_gchar,qnt_prod_orc_entry[posicao]);
  }else{
    qnt_prod_orc_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(qnt_prod_orc_entry[posicao]));
    if(!strlen(qnt_prod_orc_gchar))
      qnt_prod_orc_gchar = "0";
  }

  tipodesc = gtk_combo_box_get_active(GTK_COMBO_BOX(tipodesconto_prod_orc_combo[posicao]));

  ativos[posicao].qnt_f = atof(qnt_prod_orc_gchar);
  strcpy(ativos[posicao].qnt_c,qnt_prod_orc_gchar);
  critica_real(ativos[posicao].qnt_c,qnt_prod_orc_entry[posicao]);


  ativos[posicao].preco_f = atof(preco_prod_orc_gchar);
  strcpy(ativos[posicao].preco_c,preco_prod_orc_gchar);
  critica_real(ativos[posicao].preco_c,preco_prod_orc_entry[posicao]);

  desconto_prod_orc(desconto_prod_orc_entry[posicao],posicao);

  if(tipodesc==0){
    ativos[posicao].desconto_f = atof(desconto_prod_orc_gchar);
    strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
    critica_real(&(ativos[posicao].desconto_c[0]),desconto_prod_orc_entry[posicao]);
  }

  if(tipodesc==1){
    ativos[posicao].desconto_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))*(atof(desconto_prod_orc_gchar)/100);
    strcpy(ativos[posicao].desconto_c,desconto_prod_orc_gchar);
    critica_real(&(ativos[posicao].desconto_c[0]),desconto_prod_orc_entry[posicao]);
  }

  ativos[posicao].total_f = ((ativos[posicao].qnt_f)*(ativos[posicao].preco_f))-ativos[posicao].desconto_f;

  sprintf(total_prod_orc_gchar,"%.2f",ativos[posicao].total_f);
  gtk_entry_set_text(GTK_ENTRY(total_prod_orc_entry[posicao]),total_prod_orc_gchar);

  critica_real(total_prod_orc_gchar,total_prod_orc_entry[posicao]);
  strcpy(ativos[posicao].total_c,total_prod_orc_gchar);

  if(gerar_total_geral()){

    return 1;
  }

  if(ativos[posicao+1].id && codigo_prod_orc_entry[posicao+1])
    gtk_widget_grab_focus(codigo_prod_orc_entry[posicao+1]);
  else
    gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);

  preco_alterado[posicao] = 1;

  return 0;
}
