int tcn_ico(void)
{

	int cont,cont2=0,linha=0;

	//imagem dos icones
	emp_ico = gtk_image_new_from_file(CAD_EMP_IMG);
	rld_prod_ico = gtk_image_new_from_file(ATL_PROD_IMG);

	//label dos icones
	emp_lbl = gtk_label_new("Cadastro Empresa");
	rld_prod_lbl = gtk_label_new("Recarregar Produtos");

	//caixas onde ficarao os icones
	//cria eventos para tcna botao
	for(cont=0;cont<TCN_ICO_QNT;cont++)
	{
		tcn_box[cont] = gtk_box_new(1,0);
		gtk_container_set_border_width(GTK_CONTAINER(tcn_box[cont]),1);

		gtk_widget_set_name(tcn_box[cont],"icone");

		eventos[cont] = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(eventos[cont]),tcn_box[cont]);

		if(cont2==ICOL)
		{
			linha++;
			cont2=0;
		}
		gtk_box_pack_start(GTK_BOX(tecnicosl[linha]),eventos[cont],0,0,45);
		cont2++;
	}

	//icone tcnastro produto
  gtk_box_pack_end(GTK_BOX(tcn_box[0]),emp_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(tcn_box[0]),emp_ico,0,0,0);

	gtk_box_pack_end(GTK_BOX(tcn_box[1]),rld_prod_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(tcn_box[1]),rld_prod_ico,0,0,0);

	//sinais para chamada da opçao...
	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(cadastro_empresa),NULL);

	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(opc_reload_nome_grp),NULL);

	return 0;
}
