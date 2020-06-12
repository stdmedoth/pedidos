int vnd_ico(void)
{
	int cont,linha=0;

	//imagem dos icones
	orc_ico = gtk_image_new_from_file(ORC_IMG);
	ped_ico = gtk_image_new_from_file(PED_IMG);

	//label dos icones
	orc_lbl = gtk_label_new("Orçamentos");
	ped_lbl = gtk_label_new("Pedidos");

	//caixas onde ficarao os icones
	//cria eventos para cada botao
	for(cont=0;cont<=VND_ICO_QNT;cont++)
	{
		vnd_box[cont] = gtk_box_new(1,0);
		//sprintf(name,"icone%i",cont);
		gtk_widget_set_name(vnd_box[cont],"icone");
		eventos[cont] = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(eventos[cont]),vnd_box[cont]);
		if(cont==ICOL)
			linha++;
		gtk_box_pack_start(GTK_BOX(faturamentol[linha]),eventos[cont],0,0,40);
		//memset(name,0x0,strlen(name));
	}

	//icone orcamentos
    gtk_box_pack_end(GTK_BOX(vnd_box[0]),orc_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(vnd_box[0]),orc_ico,0,0,0);

	//icone pedidos
	gtk_box_pack_end(GTK_BOX(vnd_box[1]),ped_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(vnd_box[1]),ped_ico,0,0,0);


	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(vnd_orc),NULL);
	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(inicializar_orc),NULL);

	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(vnd_ped),NULL);
	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(inicializar_ped),NULL);

	return 0;
}
