int pag_datas_fun(void){

  GDateTime  *gdate;
  GTimeZone *timezone;
  GtkTreeIter iter1;
  gchar *data_gchar;
  int ano,mes,dia;
  char *datas_list_char[MAX_PARC_QNT];

  if(pag_cod_fun()!=0)
    return 1;
  if(pag_tipo_fun()!=0)
    return 1;
  if(pag_init_fun()!=0)
    return 1;
  if(pag_parc_fun()!=0)
    return 1;
  if(pag_parc_qnt_fun()!=0)
    return 1;

  data_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(pag_datas_entry));

  if(sscanf(data_gchar, "%d-%d-%d", &ano, &mes, &dia) == EOF)
  {
    g_print("Erro no parser de data: %s\n",strerror(errno));
    return 1;
  }

  timezone = g_time_zone_new(NULL);

  if(pag_dia_fixo_int == 0)
    pag_init_int = dia;

  gdate = g_date_time_new(timezone,ano,mes,pag_init_int,0,0,0);

  gtk_tree_store_clear(pag_datas_model);

  for(int cont=0;cont<pag_parc_qnt_int;cont++){

    if(!g_date_time_format(gdate,"%d/%m/%Y")){
      popup(NULL,"Operação impossível para esta data");
      return 1;
    }

    gtk_tree_store_append(pag_datas_model,&iter1,NULL);

    gtk_tree_store_set(pag_datas_model,&iter1,0,cont+1,1,g_date_time_format(gdate,"%d/%m/%Y"),-1);

    if(pag_tipo_int == 1)
      gdate = g_date_time_add_days(gdate,pag_parc_int);
    else
    if(pag_tipo_int == 2)
      gdate = g_date_time_add_months(gdate,pag_parc_int);

  }
  gtk_widget_grab_focus(pag_psq_datas_button);
  return 0;
}
