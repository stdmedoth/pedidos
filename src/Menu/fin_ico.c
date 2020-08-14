int fin_ico(void)
{

	int cont;
//	gchar *name;
//	name = malloc(15);

	//imagem dos icones
	rec_tit_ico = gtk_image_new_from_file(REC_TIT_IMG);
  pag_tit_ico = gtk_image_new_from_file(PAG_TIT_IMG);

	//label dos icones
  rec_tit_lbl = gtk_label_new("Títulos à Receber");
  pag_tit_lbl = gtk_label_new("Títulos à Pagar");

	//caixas onde ficarao os icones
	//cria eventos para cada botao
	for(cont=0;cont<=FIN_ICO_QNT;cont++)
	{
		fin_box[cont] = gtk_box_new(1,0);
//		sprintf(name,"icone%i",cont);
		gtk_widget_set_name(fin_box[cont],"icone");
		eventos[cont] = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(eventos[cont]),fin_box[cont]);
		gtk_box_pack_start(GTK_BOX(financeirol[0]),eventos[cont],0,0,40);
//		memset(name,0x0,strlen(name));
	}

	//icone titulos a receber
	gtk_box_pack_end(GTK_BOX(fin_box[0]),rec_tit_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(fin_box[0]),rec_tit_ico,0,0,0);

  //icone titulos a pagar
  gtk_box_pack_end(GTK_BOX(fin_box[1]),pag_tit_lbl,0,0,0);
  gtk_box_pack_end(GTK_BOX(fin_box[1]),pag_tit_ico,0,0,0);

	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(cad_titulos_receber),NULL);
	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(cad_titulos_pagar),NULL);
	return 0;
}
