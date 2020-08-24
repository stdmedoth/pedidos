struct{
  int id;
  GtkWidget *entry1;
  GtkWidget *entry2;
  char *datas;
  float vlrs;
}datas_lives_str[MAX_PARCELAS_QNT];

int concluir_datas_livres(){
  gchar *formatado;
  orc_parcelas.total_geral = 0;
  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];

  for(int cont=0;cont<orc_parc_lvr_qnt_int;cont++){
    char *data = malloc(MAX_DATE_LEN);

    if(orc_pag_dl_dts_vlrs_fun(datas_lives_str[cont].entry1, cont))
      return 1;
    if(orc_pag_dl_vlrs_fun(datas_lives_str[cont].entry2, cont))
      return 1;

    strcpy(data,datas_lives_str[cont].datas);
    formatado = formatar_data(data);
    if(!formatado){
      gtk_widget_grab_focus(datas_lives_str[cont].entry2);
      gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
      return 1;
    }
    orc_parcelas.parcelas_qnt = orc_parc_lvr_qnt_int;

    orc_parcelas.total_geral += datas_lives_str[cont].vlrs;
    if(orc_parcelas.total_geral>orc_valores.valor_total+MAX_DIF_VLR){
      gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
      gtk_widget_grab_focus(datas_lives_str[cont].entry2);
      popup(NULL,"Parcela ultrapassa valor do orçamento");
      return 1;
    }

    orc_parcelas.parcelas_data[cont] = malloc(MAX_DATE_LEN);
    strcpy(orc_parcelas.parcelas_data[cont],datas_lives_str[cont].datas);
    orc_parcelas.parcelas_vlr[cont] = datas_lives_str[cont].vlrs;

    if(cont==0){
      sprintf(query,"delete from orc_datas_livres where orcamento = %s",codigo_orc_gchar);
      if(enviar_query(query)){
        gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
        popup(NULL,"Erro ao remover parcelas antigas do orçamento");
        return 1;
      }
    }
    sprintf(query,"insert into orc_datas_livres(orcamento,pag_cond,posicao,data_vencimento,valor) values(%s,%i,%i,DATE_FORMAT('%s','%%d/%%m/%%y'),%.4f);",
    codigo_orc_gchar,
    orc_parcelas.pagcond_code,
    cont,
    datas_lives_str[cont].datas,
    datas_lives_str[cont].vlrs );

    if(enviar_query(query)){
      gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
      popup(NULL,"Erro ao enviar parcelas livres para banco");
      return 1;
    }

  }

  if(orc_parcelas.total_geral+MAX_DIF_VLR<orc_valores.valor_total){
    gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),2);
    popup(NULL,"Parcelas têm valor menor");
    return 1;
  }

  return 0;
}

int orc_pag_dl_dts_vlrs_fun(GtkEntry *entry, int pos){
  gchar *formatado;
  gchar *data = (gchar*)gtk_entry_get_text(entry);

  formatado = formatar_data(data);

  if(!formatado){
    return 1;
  }

  if(!datas_lives_str[pos].datas)
    datas_lives_str[pos].datas = malloc(MAX_DATE_LEN);

  strcpy(datas_lives_str[pos].datas,formatado);


  gtk_entry_set_text(entry,formatado);
  if(datas_lives_str[pos].entry2)
    gtk_widget_grab_focus(datas_lives_str[pos].entry2);
  else
    return 1;

  return 0;
}


int orc_pag_dl_vlrs_fun(GtkEntry *entry,int pos){

  float valor;
  gchar *val = (gchar*)gtk_entry_get_text(entry);

  if(!val)
    return 1;

  for(int cont=0;cont<strlen(val);cont++)
  {
    if(val[cont]==44){
      val[cont] = 46;
    }else
    if(!(val[cont] == 46)){
      if(!isdigit(val[cont])){
        popup(NULL,"Insira valor");
        return 1;
      }
    }
  }

  gchar *formatado = malloc(MAX_PRECO_LEN);

  if(val)
    valor = atof(val);
  else
  if(concluindo_orc)
    return 1;
  else{
    val = malloc(10);
    gtk_entry_set_text(entry,val);
  }

  datas_lives_str[pos].vlrs = valor;
  float valor_total=0;
  gchar *valor_gchar = malloc(MAX_PRECO_LEN);

  for(int cont=0;cont<orc_parc_lvr_qnt_int;cont++){
      gchar *value = (gchar*)gtk_entry_get_text(GTK_ENTRY(datas_lives_str[cont].entry2));
      if(!value){
        gtk_widget_grab_focus(datas_lives_str[cont].entry2);
        return 1;
      }
      datas_lives_str[cont].vlrs = atof(value);
      valor_total += datas_lives_str[cont].vlrs;
      sprintf(valor_gchar,"%.4f",orc_valores.valor_total - valor_total);
      gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_livres_rest),valor_gchar);
  }

  if(valor_total>orc_valores.valor_total+MAX_DIF_VLR){
    sprintf(valor_gchar,"%.4f",orc_valores.valor_total - valor_total);
    gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_livres_rest),valor_gchar);
    popup(NULL,"Parcela ultrapassa valor do orçamento");
    return 1;
  }

  if(valor_total+MAX_DIF_VLR<orc_valores.valor_total){
    sprintf(valor_gchar,"%.4f",orc_valores.valor_total - valor_total);
    gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_livres_rest),valor_gchar);
    popup(NULL,"Parcelas têm valor menor que orçamento");
    return 1;
  }

  orc_parcelas.valor_faltante = orc_valores.valor_total - valor_total;

  sprintf(valor_gchar,"%.4f",orc_valores.valor_total - valor_total);
  gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_livres_rest),valor_gchar);

  sprintf(formatado,"%.4f",valor);
  gtk_entry_set_text(entry,formatado);

  if(pos<MAX_PARCELAS_QNT)
    if(pos+1<=orc_pag_parc_qnt_int)
      gtk_widget_grab_focus(datas_lives_str[pos+1].entry1);

  return 0;
}


int orc_pag_datas_livres(){

  GtkWidget *orc_pag_datas_label1,
  *orc_pag_datas_label2;
  float parcela=0;
  char valor[MAX_PRECO_LEN];
  GtkWidget *orc_pag_datas_label2_fixed,
  *orc_pag_datas_label1_fixed;

  char *parcqnt_gchar;

  gtk_widget_set_sensitive(orc_pag_datas_parcqnt,TRUE);
  gtk_widget_set_name(orc_pag_datas_parcqnt,"");

  orc_pag_datas_label1 = gtk_label_new("Datas");
  orc_pag_datas_label2 = gtk_label_new("Valor");

  orc_pag_datas_label1_fixed = gtk_fixed_new();
  orc_pag_datas_label2_fixed = gtk_fixed_new();

  gtk_fixed_put(GTK_FIXED(orc_pag_datas_label1_fixed),orc_pag_datas_label1,20,20);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_label2_fixed),orc_pag_datas_label2,20,20);

  gtk_grid_remove_column(GTK_GRID(orc_pag_datas_grid),0);
  gtk_grid_remove_column(GTK_GRID(orc_pag_datas_grid),0);

  gtk_grid_insert_column(GTK_GRID(orc_pag_datas_grid),0);
  gtk_grid_insert_column(GTK_GRID(orc_pag_datas_grid),1);

  gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_label1_fixed,0,0,1,1);
  gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_label2_fixed,1,0,1,1);

  if(recebendo_prod_orc == 0){

    parcqnt_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(orc_pag_datas_parcqnt));

    if(parcqnt_gchar)
      orc_pag_parc_qnt_int = atoi(parcqnt_gchar);
    else
      orc_pag_parc_qnt_int=0;

  }

  if(orc_pag_parc_qnt_int==0){
    orc_pag_parc_qnt_int = 1;
    gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_parcqnt),"1");
  }

  orc_parc_lvr_qnt_int = orc_pag_parc_qnt_int;
  int notepage = gtk_notebook_get_current_page(GTK_NOTEBOOK(orc_notebook));

  if(!tipo_pag)
    tipo_pag=PAG_VIST;

  if(orc_parc_lvr_qnt_int>1){
    if(tipo_pag==PAG_VIST){
      tipo_pag=PAG_FAT;
      for(int cont=1;cont<=MAX_PROD_ORC;cont++)
      {
        if(ativos[cont].id==1)
        {
          if(ha_prods()){
            codigo_prod_orc(NULL,cont);
            qnt_prod_orc(NULL,cont);
          }
        }
      }
      gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),notepage);
    }
  }else{
    if(tipo_pag==PAG_FAT){
      tipo_pag=PAG_VIST;
      for(int cont=1;cont<=MAX_PROD_ORC;cont++)
      {
        if(ativos[cont].id==1)
        {
          if(ha_prods()){
            codigo_prod_orc(NULL,cont);
            qnt_prod_orc(NULL,cont);
          }
        }
      }
      gtk_notebook_set_current_page(GTK_NOTEBOOK(orc_notebook),notepage);
    }
  }

  for(int cont=0;cont<orc_parc_lvr_qnt_int;cont++){

    if(cont==0){
      parcela = (orc_valores.valor_prds_liquido/orc_parc_lvr_qnt_int) + orc_valores.valor_frete_liquido;
    }else{
      parcela = (orc_valores.valor_prds_liquido/orc_parc_lvr_qnt_int);
    }
    sprintf(valor,"%.4f",parcela);

    orc_pag_datas_entry1[cont] = gtk_entry_new();
    if(datas_lives_str[cont].datas)
      gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_entry1[cont]),datas_lives_str[cont].datas);
    /*else{
      datas_lives_str[cont].datas = malloc(MAX_DATE_LEN);
      strcpy(datas_lives_str[cont].datas,data_sys);
      gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_entry1[cont]),datas_lives_str[cont].datas);
    }*/
    gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_entry1[cont]),10);

    orc_pag_datas_entry2[cont] = gtk_entry_new();
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(orc_pag_datas_entry2[cont]),GTK_ENTRY_ICON_PRIMARY,"money");
    gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_entry2[cont]),10);
    gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_entry2[cont]),valor);

    orc_pag_vetor[cont] = cont;

    datas_lives_str[cont].id = cont;
    datas_lives_str[cont].entry1 = orc_pag_datas_entry1[cont];
    datas_lives_str[cont].entry2 = orc_pag_datas_entry2[cont];

    #pragma GCC diagnostic ignored "-Wint-conversion"
    g_signal_connect(orc_pag_datas_entry1[cont],"activate",G_CALLBACK(orc_pag_dl_dts_vlrs_fun),orc_pag_vetor[cont]);
    g_signal_connect(orc_pag_datas_entry2[cont],"activate",G_CALLBACK(orc_pag_dl_vlrs_fun),orc_pag_vetor[cont]);
    #pragma GCC diagnostic warning "-Wint-conversion"

    gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_entry1[cont],0,cont+1,1,1);
    gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_entry2[cont],1,cont+1,1,1);
  }

  gtk_widget_show_all(orc_pag_datas_livres_fixed);

  return 0;
}
