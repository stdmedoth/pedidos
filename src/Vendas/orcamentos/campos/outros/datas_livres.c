int orc_pag_datas_livres(){
  GtkWidget **entrys_box;
  GtkWidget *orc_pag_datas_livres_label1,
  *orc_pag_datas_livres_label2;
  gtk_widget_show_all(orc_pag_datas_livres_fixed);

  GtkWidget *orc_pag_datas_livres_label2_fixed,
  *orc_pag_datas_livres_label1_fixed;

  entrys_box = malloc(sizeof(GtkBox*)*MAX_PARCELAS_QNT);
  orc_pag_datas_livres_label1 = gtk_label_new("Datas");
  orc_pag_datas_livres_label2 = gtk_label_new("Valor");

  orc_pag_datas_livres_label1_fixed = gtk_fixed_new();
  orc_pag_datas_livres_label2_fixed = gtk_fixed_new();

  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_label1_fixed),orc_pag_datas_livres_label1,20,20);
  gtk_fixed_put(GTK_FIXED(orc_pag_datas_livres_label2_fixed),orc_pag_datas_livres_label2,20,20);

  gtk_grid_remove_column(GTK_GRID(orc_pag_datas_livres_grid),0);
  gtk_grid_remove_column(GTK_GRID(orc_pag_datas_livres_grid),0);

  gtk_grid_insert_column(GTK_GRID(orc_pag_datas_livres_grid),0);
  gtk_grid_insert_column(GTK_GRID(orc_pag_datas_livres_grid),1);

  gtk_grid_attach(GTK_GRID(orc_pag_datas_livres_grid),orc_pag_datas_livres_label1_fixed,0,0,1,1);
  gtk_grid_attach(GTK_GRID(orc_pag_datas_livres_grid),orc_pag_datas_livres_label2_fixed,1,0,1,1);

  orc_pag_parc_qnt_int = atoi(gtk_entry_get_text(GTK_ENTRY(orc_pag_datas_livres_parcqnt)));
  if(orc_pag_parc_qnt_int==0){
    orc_pag_parc_qnt_int = 1;
    gtk_entry_set_text(GTK_ENTRY(orc_pag_datas_livres_parcqnt),"1");
  }

  for(int cont=1;cont<=orc_pag_parc_qnt_int;cont++){
    orc_pag_datas_livres_entry1[cont] = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_livres_entry1[cont]),15);
    orc_pag_datas_livres_entry2[cont] = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(orc_pag_datas_livres_entry2[cont]),10);
    entrys_box[cont] = gtk_box_new(0,0);
    gtk_grid_attach(GTK_GRID(orc_pag_datas_livres_grid),orc_pag_datas_livres_entry1[cont],0,cont,1,1);
    gtk_grid_attach(GTK_GRID(orc_pag_datas_livres_grid),orc_pag_datas_livres_entry2[cont],1,cont,1,1);
  }

  gtk_widget_show_all(orc_pag_datas_livres_fixed);
  return 0;
}
