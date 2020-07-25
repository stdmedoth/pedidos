int orc_pag_datas_fun(void){

  GDateTime  *gdate;
  GTimeZone *timezone;
  GtkTreeIter iter1;
  gchar *data_gchar;
  int ano,mes,dia;
  char *datas_list_char[MAX_PARC_QNT];

  data_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(orc_pag_datas_entry));

  if(sscanf(data_gchar, "%d-%d-%d", &ano, &mes, &dia) == EOF)
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

  for(int cont=0;cont<orc_pag_parc_qnt_int;cont++){

    if(!g_date_time_format(gdate,"%d/%m/%Y")){
      popup(NULL,"Operação impossível para esta data");
      return 1;
    }
    gtk_tree_store_append(orc_pag_datas_model,&iter1,NULL);

    gtk_tree_store_set(orc_pag_datas_model,&iter1,0,cont+1,1,g_date_time_format(gdate,"%d/%m/%Y"),2,"",-1);

    if(orc_pag_tipo_int == 1)
      gdate = g_date_time_add_days(gdate,orc_pag_parc_int);
    else
    if(pag_tipo_int == 2)
      gdate = g_date_time_add_months(gdate,pag_parc_int);
  }

  gtk_tree_view_set_model(GTK_TREE_VIEW(orc_pag_datas_tree),(GtkTreeModel*) orc_pag_datas_model);

  return 0;
}
