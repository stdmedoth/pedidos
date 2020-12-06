void mp_popup_add_mp(int pos, GtkWidget *grid){
  mp_popup_code_combo[pos] = gtk_combo_box_text_new();
  mp_popup_valor_entry[pos] = gtk_spin_button_new_with_range(1,1000,0.05);
  mp_popup_creden_combo[pos] = gtk_combo_box_text_new();
  mp_tipospag_pos[pos] = 1;

  for(int i=0;i<mp_tipospag_qnt;i++){
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(mp_popup_code_combo[pos]), tipospag_ids[i], tipospag_nomes[i]);
  }

  for(int i=0;i<mp_creden_qnt;i++){
		gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(mp_popup_creden_combo[pos]), creden_ids[i], creden_nomes[i]);
  }
  if(mp_tipospag_qnt){
    gtk_grid_attach(GTK_GRID(grid),mp_popup_code_combo[pos], 0, pos,1,1 );
    gtk_grid_attach(GTK_GRID(grid),mp_popup_valor_entry[pos], 1, pos,1,1 );
    gtk_combo_box_set_active(GTK_COMBO_BOX(mp_popup_code_combo[pos]),0);
  }
  if(mp_creden_qnt){
    gtk_grid_attach(GTK_GRID(grid),mp_popup_creden_combo[pos], 2, pos,1,1 );
    gtk_combo_box_set_active(GTK_COMBO_BOX(mp_popup_creden_combo[pos]),0);
  }
}

int mp_popup_get_livre_pos(){
  for(int i=0;i<MAX_PGTO_QNT;i++)
    if(mp_tipospag_pos[i])
      return i;

  return MAX_PGTO_QNT;
}

void mp_popup_change_qnt(GtkSpinButton *spin_button, gpointer user_data){
  gtk_grid_remove_column(GTK_GRID(user_data), 0);
  gtk_grid_remove_column(GTK_GRID(user_data), 0);
  gtk_grid_remove_column(GTK_GRID(user_data), 0);
  for(int i=0;i<MAX_PGTO_QNT;i++){
    mp_tipospag_pos[i] = 0;
  }

  int pag_qnt = gtk_spin_button_get_value(GTK_SPIN_BUTTON(mp_popup_qnt_entry));

  for(int i=1;i<=pag_qnt;i++){
    mp_popup_add_mp(i-1, user_data);
    gtk_widget_show_all(user_data);
  }
}

struct _cfe_pgto *get_mp_popup(GtkWidget *parent){
	GtkWidget *janela, *fields, *fixed, *grid, *scroll, *box;
	int resultado;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];

  tipospag_ids = malloc(MAX_PGTO_QNT * 12);
	tipospag_nomes = malloc(MAX_PGTO_QNT * MAX_NAME_LEN);

  creden_ids = malloc(MAX_CREDEN_QNT * 12);
  creden_nomes = malloc(MAX_CREDEN_QNT * MAX_NAME_LEN);

  mp_popup_code_combo = malloc(sizeof(GtkWidget *) * MAX_PGTO_QNT);
	mp_popup_valor_entry = malloc(sizeof(GtkWidget *) * MAX_PGTO_QNT);
  mp_popup_creden_combo = malloc(sizeof(GtkWidget *) * MAX_PGTO_QNT);
	mp_popup_qnt_entry = gtk_spin_button_new_with_range(1, MAX_PGTO_QNT, 1);
  GtkWidget *mp_popup_qnt_frame = gtk_frame_new("Qnt tipos Pagamentos");
  GtkWidget *mp_popup_qnt_fixed = gtk_fixed_new();
	struct _cfe_pgto *pgto = malloc(sizeof(struct _cfe_pgto ) * MAX_PGTO_QNT);
	janela = gtk_dialog_new_with_buttons("Concluir pagamento",NULL,GTK_DIALOG_MODAL,"Finalizar cupom",GTK_RESPONSE_ACCEPT,"Cancelar",GTK_RESPONSE_REJECT,NULL);
  if(parent)
		gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(parent));
  gtk_window_set_position(GTK_WINDOW(janela),3);
  fields = gtk_bin_get_child(GTK_BIN(janela));
  GtkWidget *box1 = gtk_box_new(1,0);
  GtkWidget *box2 = gtk_box_new(1,0);
  box = gtk_box_new(0,0);
  grid = gtk_grid_new();
  scroll = gtk_scrolled_window_new(NULL,NULL);
  fixed = gtk_fixed_new();

  gtk_container_add(GTK_CONTAINER(scroll), grid);
  gtk_widget_set_size_request(scroll, 500, 200);
  gtk_widget_set_size_request(scroll, 500, 200);
  gtk_widget_set_size_request(janela, 600, 200);
  gtk_container_add(GTK_CONTAINER(mp_popup_qnt_frame), mp_popup_qnt_entry);
  gtk_fixed_put(GTK_FIXED(mp_popup_qnt_fixed), mp_popup_qnt_frame ,20,20);

  gtk_box_pack_start(GTK_BOX(box1), mp_popup_qnt_fixed,0,0,5);

  gtk_box_pack_start(GTK_BOX(box2), scroll,0,0,5);

  gtk_box_pack_start(GTK_BOX(box), box1,0,0,5);
  gtk_box_pack_start(GTK_BOX(box), box2,0,0,5);

  gtk_fixed_put(GTK_FIXED(fixed), box,20,20);
  gtk_box_pack_start(GTK_BOX(fields), fixed,0,0,5);

	sprintf(query, "select * from meios_pagamento");
	if(! (res = consultar(query)) ){
		popup(NULL,"Não foi possível consultar meios de pagamento");
		return NULL;
	}
  for(int i=0;i<MAX_PGTO_QNT;i++){
    mp_tipospag_pos[i] = 0;
  }

  mp_tipospag_qnt=0;
	while ((row = mysql_fetch_row(res))){
		if(mp_tipospag_qnt >= MAX_PGTO_QNT)
			break;

		tipospag_ids[mp_tipospag_qnt] = malloc(12);
		tipospag_nomes[mp_tipospag_qnt] = malloc(MAX_NAME_LEN);

    sprintf(tipospag_ids[mp_tipospag_qnt], "%02i", atoi(row[0]));
		strcpy(tipospag_nomes[mp_tipospag_qnt], row[1]);
		mp_tipospag_qnt++;
	}

  sprintf(query, "select * from credenciadoras");
  if(! (res = consultar(query)) ){
    popup(NULL,"Não foi possível consultar credenciadoras");
    return NULL;
  }
  mp_creden_qnt = 0;
  while ((row = mysql_fetch_row(res))){
    if(mp_creden_qnt >= MAX_CREDEN_QNT)
      break;

    creden_ids[mp_creden_qnt] = malloc(12);
    creden_nomes[mp_creden_qnt] = malloc(MAX_NAME_LEN);
    strcpy(creden_ids[mp_creden_qnt], row[1]);
    strcpy(creden_nomes[mp_creden_qnt], row[2]);

    int abrevia_pos = 20;
    if(strlen(creden_nomes[mp_creden_qnt]) > abrevia_pos){
      creden_nomes[mp_creden_qnt][abrevia_pos] = '.';
      creden_nomes[mp_creden_qnt][abrevia_pos+1] = '\0';
    }

    mp_creden_qnt++;
  }

  mp_popup_add_mp(0, grid);
  gtk_widget_show_all(janela);
  g_signal_connect(mp_popup_qnt_entry, "value-changed", G_CALLBACK(mp_popup_change_qnt), grid);
  static int pag_qnt=0;
  gchar *text;
	resultado = gtk_dialog_run(GTK_DIALOG(janela));
	switch (resultado) {
		case GTK_RESPONSE_ACCEPT:
      pag_qnt = gtk_spin_button_get_value(GTK_SPIN_BUTTON(mp_popup_qnt_entry));

      for(int cont=0; cont < pag_qnt;cont++){
        if(mp_tipospag_pos[cont]){

          text = (gchar*)gtk_combo_box_get_active_id(GTK_COMBO_BOX(mp_popup_code_combo[cont]));
          if(text && strlen(text))
            pgto[cont].ccMP = strdup(text);
          else{
            popup(NULL,"Forma de pagamento inserida");
            gtk_widget_destroy(janela);
            return NULL;
          }

          text = (gchar*)gtk_entry_get_text(GTK_ENTRY(mp_popup_valor_entry[cont]));
          if(text && strlen(text))
            pgto[cont].cvMP = strdup(text);
          else{
            popup(NULL,"Valor não inserido");
            gtk_widget_destroy(janela);
            return NULL;
          }

          text = (gchar*) gtk_combo_box_get_active_id(GTK_COMBO_BOX(mp_popup_creden_combo[cont]));
          if(text && strlen(text))
            pgto[cont].cAdmC = strdup(text);
          else{
            popup(NULL,"Credenciadora não inserida");
            gtk_widget_destroy(janela);
            return NULL;
          }

          pgto[cont].icMP = atoi(pgto[cont].ccMP);
          pgto[cont].fvMP = atof(pgto[cont].cvMP);
        }
        pdv_venda_atual->cupom_atual->MPqnt = pag_qnt;
      }
      gtk_widget_destroy(janela);
      return pgto;
	}
  gtk_widget_destroy(janela);
  return NULL;
}
