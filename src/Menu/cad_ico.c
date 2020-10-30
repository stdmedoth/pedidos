#include "cad_ico.h"

int cad_ico(void)
{

	int cont,cont2=0,linha=0;

	//imagem dos icones
	prd_ico = gtk_image_new_from_file(PROD_IMG);
	ter_ico = gtk_image_new_from_file(TERC_IMG);
	opr_ico = gtk_image_new_from_file(OPR_IMG);
	trs_ico = gtk_image_new_from_file(TRS_IMG);
	und_ico = gtk_image_new_from_file(UND_IMG);
	vin_ico = gtk_image_new_from_file(VINC_IMG);
	grp_ico = gtk_image_new_from_file(GRP_IMG);
	pag_ico = gtk_image_new_from_file(PAG_IMG);
	crel_ico = gtk_image_new_from_file(REL_IMG);
	ceps_ico = gtk_image_new_from_file(CAD_CEP_IMG);
	bnc_ico = gtk_image_new_from_file(BANCOS_IMG);

	//label dos icones
	prd_lbl = gtk_label_new("Novo Produto");
	ter_lbl = gtk_label_new("Novo Terceiro");
	opr_lbl = gtk_label_new("Novo Operador");
	trs_lbl = gtk_label_new("Nova Transação");
	und_lbl = gtk_label_new("Nova Unidade Medida");
	vin_lbl = gtk_label_new("Verificar vinculos");
	grp_lbl = gtk_label_new("Grupo de Produtos");
	pag_lbl = gtk_label_new("Cond. Pagamento");
	crel_lbl = gtk_label_new("Novo Relatório");
	ceps_lbl = gtk_label_new("Códigos Postais");
	bnc_lbl = gtk_label_new("Bancos");

	//caixas onde ficarao os icones
	//cria eventos para cada botao
	for(cont=0;cont<CAD_ICO_QNT;cont++)
	{
		cad_box[cont] = gtk_box_new(1,0);
		gtk_container_set_border_width(GTK_CONTAINER(cad_box[cont]),1);

		gtk_widget_set_name(cad_box[cont],"icone");

		eventos[cont] = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(eventos[cont]),cad_box[cont]);

		if(cont2==ICOL)
		{
			linha++;
			cont2=0;
		}
		gtk_box_pack_start(GTK_BOX(cadastrosl[linha]),eventos[cont],0,0,45);
		cont2++;
	}

	//icone cadastro produto
  gtk_box_pack_end(GTK_BOX(cad_box[0]),prd_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cad_box[0]),prd_ico,0,0,0);

	//icone cadastro terceiro
	gtk_box_pack_end(GTK_BOX(cad_box[1]),ter_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cad_box[1]),ter_ico,0,0,0);

	//icone cadastro operadores
	gtk_box_pack_end(GTK_BOX(cad_box[2]),opr_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cad_box[2]),opr_ico,0,0,0);

	//icone cadastro de unidades
	gtk_box_pack_end(GTK_BOX(cad_box[3]),und_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cad_box[3]),und_ico,0,0,0);

	//icone grupos
	gtk_box_pack_end(GTK_BOX(cad_box[4]),grp_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cad_box[4]),grp_ico,0,0,0);

	//icone condicao pagamento
	gtk_box_pack_end(GTK_BOX(cad_box[5]),pag_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cad_box[5]),pag_ico,0,0,0);

	//icone novo relatorio
	gtk_box_pack_end(GTK_BOX(cad_box[6]),crel_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cad_box[6]),crel_ico,0,0,0);

	//icone novo cep
	gtk_box_pack_end(GTK_BOX(cad_box[7]),ceps_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cad_box[7]),ceps_ico,0,0,0);

	//icone novo banco
	gtk_box_pack_end(GTK_BOX(cad_box[8]),bnc_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cad_box[8]),bnc_ico,0,0,0);

	//sinais para chamada da opçao...
	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(inicializar_prod),NULL);
	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(cad_prod),NULL);

	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(inicializar_ter),NULL);
	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(cad_terc),NULL);

	g_signal_connect(eventos[2],"button_press_event",G_CALLBACK(cad_oper),NULL);

	g_signal_connect(eventos[3],"button_press_event",G_CALLBACK(cad_und),NULL);

	g_signal_connect(eventos[4],"button_press_event",G_CALLBACK(cad_grupo),NULL);

	g_signal_connect(eventos[5],"button_press_event",G_CALLBACK(cad_pag),NULL);

	g_signal_connect(eventos[6],"button_press_event",G_CALLBACK(cad_relat),NULL);

	g_signal_connect(eventos[7],"button_press_event",G_CALLBACK(cad_cep),NULL);

	g_signal_connect(eventos[8],"button_press_event",G_CALLBACK(cad_bancos_fun),NULL);

	return 0;
}
