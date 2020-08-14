int orc_pag_datas_fun(void){

  GDateTime  *gdate;
  GTimeZone *timezone;
  GtkTreeIter iter1;
  gchar *data_gchar;
  int ano,mes,dia;
  char *datas_list_char[MAX_PARC_QNT];
  char valor[MAX_PRECO_LEN];
  float parcela=0;

  gtk_widget_show_all(orc_pag_datas_fixed);

  data_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_pag_datas_entry));

  if(sscanf(data_gchar, "%d/%d/%d", &dia, &mes, &ano) == EOF)
  {
    popup(NULL,"Não foi possivel ler data");
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 1;
  }

  timezone = g_time_zone_new(NULL);

  if(orc_pag_dia_fixo_int == 0)
    orc_pag_init_int = dia;

  if(orc_pag_init_int<atoi(dia_sys)){
    mes++;
  }

  gdate = g_date_time_new(timezone,ano,mes,orc_pag_init_int,0,0,0);

  gtk_tree_store_clear(orc_pag_datas_model);

  orc_parcelas.parcelas_qnt = orc_pag_parc_qnt_int;
  orc_parcelas.total_geral = 0;
  for(int cont=0;cont<orc_pag_parc_qnt_int;cont++){

    if(!g_date_time_format(gdate,"%d/%m/%Y")){
      popup(NULL,"Operação impossível para esta data");
      return 1;
    }
    gtk_tree_store_append(orc_pag_datas_model,&iter1,NULL);

    if(cont==0){
      parcela = (orc_valores.valor_prds_liquido/orc_pag_parc_qnt_int) + orc_valores.valor_frete_liquido;
    }else{
      parcela = (orc_valores.valor_prds_liquido/orc_pag_parc_qnt_int);
    }

    sprintf(valor,"R$ %.2f",parcela);
    gtk_tree_store_set(orc_pag_datas_model,&iter1,0,cont+1,1,g_date_time_format(gdate,"%d/%m/%Y"),2,valor,-1);

    if(g_date_time_format(gdate,"%d/%m/%Y")){
      orc_parcelas.parcelas_data[cont] = malloc(strlen(g_date_time_format(gdate,"%d/%m/%Y")));
      strcpy(orc_parcelas.parcelas_data[cont],g_date_time_format(gdate,"%d/%m/%Y"));
    }

    orc_parcelas.parcelas_vlr[cont] = parcela;
    orc_parcelas.total_geral += orc_parcelas.parcelas_vlr[cont];

    if(orc_pag_tipo_int == 1)
      gdate = g_date_time_add_days(gdate,orc_pag_parc_int);
    else
    if(pag_tipo_int == 2)
      gdate = g_date_time_add_months(gdate,pag_parc_int);
  }

  gtk_tree_view_set_model(GTK_TREE_VIEW(orc_pag_datas_tree),(GtkTreeModel*) orc_pag_datas_model);

  return 0;
}
