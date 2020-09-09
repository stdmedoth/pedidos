int orc_pag_datas_fun(void){

  GDateTime  *gdate;
  GTimeZone *timezone;
  GtkTreeIter iter1;
  gchar *data_gchar;
  int ano,mes,dia;
  char *datas_list_char[MAX_PARC_QNT];
  char valor[MAX_PRECO_LEN],parc_qnt[12];
  float parcela=0;
  GtkWidget *orc_pag_datas_label1,
  *orc_pag_datas_label2;
  GtkWidget *orc_pag_datas_label2_fixed,
  *orc_pag_datas_label1_fixed;

  data_gchar = malloc(MAX_DATE_LEN);
  strcpy(data_gchar,data_sys);

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

  orc_pag_datas_label1 = gtk_label_new("Datas");
  orc_pag_datas_label2 = gtk_label_new("Valor");

  orc_pag_datas_label1_fixed = gtk_fixed_new();
  orc_pag_datas_label2_fixed = gtk_fixed_new();

  gtk_grid_remove_column(GTK_GRID(orc_pag_datas_grid),0);
  gtk_grid_remove_column(GTK_GRID(orc_pag_datas_grid),0);

  gtk_grid_insert_column(GTK_GRID(orc_pag_datas_grid),0);
  gtk_grid_insert_column(GTK_GRID(orc_pag_datas_grid),1);

  gtk_fixed_put(GTK_FIXED(orc_pag_datas_label1_fixed),orc_pag_datas_label1,20,20);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_label2_fixed),orc_pag_datas_label2,20,20);

  gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_label1_fixed,0,0,1,1);
  gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_label2_fixed,1,0,1,1);

  orc_parcelas.parcelas_qnt = orc_pag_parc_qnt_int;
  orc_parcelas.total_geral = 0;

  sprintf(parc_qnt,"%i",orc_parcelas.parcelas_qnt);
  gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_parcqnt),parc_qnt);
  gtk_widget_set_sensitive(orc_pag_datas_parcqnt,FALSE);
  gtk_widget_set_name(orc_pag_datas_parcqnt,"entry_unsensetivate");

  for(int cont=0;cont<orc_parcelas.parcelas_qnt;cont++){

    if(!g_date_time_format(gdate,"%d/%m/%Y")){
      popup(NULL,"Operação impossível para esta data");
      return 1;
    }
    if(orc_pag_tipo_int == CONDPAG_DIAS)
      gdate = g_date_time_add_days(gdate,orc_pag_parc_int);
    else
    if(pag_tipo_int == CONDPAG_MESES)
      gdate = g_date_time_add_months(gdate,pag_parc_int);

    if(cont==0){
      parcela = (orc_valores.valor_prds_liquido/orc_pag_parc_qnt_int) + orc_valores.valor_frete_liquido;
    }else{
      parcela = (orc_valores.valor_prds_liquido/orc_pag_parc_qnt_int);
    }

    sprintf(valor,"R$ %.2f",parcela);

    if(g_date_time_format(gdate,"%d/%m/%Y")){
      orc_parcelas.parcelas_data[cont] = malloc(strlen(g_date_time_format(gdate,"%d/%m/%Y")));
      strcpy(orc_parcelas.parcelas_data[cont],g_date_time_format(gdate,"%d/%m/%Y"));
    }

    orc_parcelas.parcelas_vlr[cont] = parcela;
    orc_parcelas.total_geral += orc_parcelas.parcelas_vlr[cont];

    orc_pag_datas_entry1[cont] = gtk_entry_new();
    gtk_widget_set_sensitive(orc_pag_datas_entry1[cont],FALSE);
    gtk_widget_set_name(orc_pag_datas_entry1[cont],"entry_unsensetivate");
    gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_entry1[cont]),10);
    gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_entry1[cont]),orc_parcelas.parcelas_data[cont]);

    orc_pag_datas_entry2[cont] = gtk_entry_new();
    gtk_widget_set_sensitive(orc_pag_datas_entry2[cont],FALSE);
    gtk_widget_set_name(orc_pag_datas_entry2[cont],"entry_unsensetivate");
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(orc_pag_datas_entry2[cont]),GTK_ENTRY_ICON_PRIMARY,"money");
    gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_entry2[cont]),10);
    gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_entry2[cont]),valor);

    gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_entry1[cont],0,cont+1,1,1);
    gtk_grid_attach(GTK_GRID(orc_pag_datas_grid),orc_pag_datas_entry2[cont],1,cont+1,1,1);

    if(orc_pag_tipo_int == CONDPAG_DADATA)
      gdate = g_date_time_add_days(gdate,orc_pag_parc_int);

  }

  gtk_widget_show_all(orc_pag_datas_grid);
  return 0;
}
