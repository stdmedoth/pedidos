int rel_ico(void)
{

	int cont,cont2=0,linha=0;

	//imagem dos icones
	rel_prd_ico = gtk_image_new_from_file(REL_PROD_IMG);
	rel_ter_ico = gtk_image_new_from_file(REL_TER_IMG);
	rel_est_ico = gtk_image_new_from_file(REL_SLD_IMG);

	//label dos icones
	rel_prd_lbl = gtk_label_new("Relatório Produtos");
	rel_ter_lbl = gtk_label_new("Relatório Terceiros");
	rel_est_lbl = gtk_label_new("Relatório Movimentos");

	//caixas onde ficarao os icones
	//cria eventos para cada botao
	for(cont=0;cont<REL_ICO_QNT;cont++)
	{
		rel_box[cont] = gtk_box_new(1,0);
		//sprintf(name,"icone%i",cont);
		gtk_widget_set_name(rel_box[cont],"icone");
		eventos[cont] = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(eventos[cont]),rel_box[cont]);
		if(cont2==ICOL)
		{
			linha++;
			cont2=0;
		}
		gtk_box_pack_start(GTK_BOX(relatoriosl[linha]),eventos[cont],0,0,45);
		//memset(name,0x0,strlen(name));
		cont2++;
	}

	//icone relatorio produto
    gtk_box_pack_end(GTK_BOX(rel_box[0]),rel_prd_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(rel_box[0]),rel_prd_ico,0,0,0);

	//icone relatorio terceiro
	gtk_box_pack_end(GTK_BOX(rel_box[1]),rel_ter_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(rel_box[1]),rel_ter_ico,0,0,0);

	//icone relatorio estoque
	gtk_box_pack_end(GTK_BOX(rel_box[2]),rel_est_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(rel_box[2]),rel_est_ico,0,0,0);

	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(relat_prod_fun),NULL);
	//g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(NULL),NULL);

	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(relat_ter_fun),NULL);
	//g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(NULL),NULL);

	g_signal_connect(eventos[2],"button_press_event",G_CALLBACK(relat_sld_fun),NULL);
	//g_signal_connect(eventos[2],"button_press_event",G_CALLBACK(NULL),NULL);

	return 0;
}
