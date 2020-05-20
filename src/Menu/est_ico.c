int estq_ico()
{

	int cont;
//	gchar *name;
//	name = malloc(15);
	
	//imagem dos icones
	est_ico = gtk_image_new_from_file(ESTO_IMG);
	sld_ico = gtk_image_new_from_file(SALD_IMG);
	
	//label dos icones
    est_lbl = gtk_label_new("Novo Estoque");
	sld_lbl = gtk_label_new("Saldo Estoque");
	
	//caixas onde ficarao os icones
	//cria eventos para cada botao
	for(cont=0;cont<=EST_ICO_QNT;cont++)
	{
		est_box[cont] = gtk_box_new(1,0);
//		sprintf(name,"icone%i",cont);
		gtk_widget_set_name(est_box[cont],"icone");
		eventos[cont] = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(eventos[cont]),est_box[cont]);
		gtk_box_pack_start(GTK_BOX(estoquel[0]),eventos[cont],0,0,40);
//		memset(name,0x0,strlen(name));
	}
        
	//icone estoque
	gtk_box_pack_end(GTK_BOX(est_box[0]),est_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(est_box[0]),est_ico,0,0,0);

	gtk_box_pack_end(GTK_BOX(est_box[1]),sld_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(est_box[1]),sld_ico,0,0,0);	
	
	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(cad_est),NULL);
	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(cad_est_sld),NULL);
	return 0;
}

