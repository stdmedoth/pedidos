#include "cmp_ico.h"

int cmp_ico(void)
{

	int cont;
//	gchar *name;
//	name = malloc(15);

	//imagem dos icones
	sol_ico = gtk_image_new_from_file(SOL_IMG);
	cot_ico = gtk_image_new_from_file(COT_IMG);
	ord_ico = gtk_image_new_from_file(ORD_IMG);
	ent_nfe_ico = gtk_image_new_from_file(ENT_IMG);

	//label dos icones
	sol_lbl = gtk_label_new("Solicitações");
	cot_lbl = gtk_label_new("Cotações");
	ord_lbl = gtk_label_new("Ordem de compra");
	ent_nfe_lbl = gtk_label_new("Entrada de NF-e");


	//caixas onde ficarao os icones
	//cria eventos para cada botao
	for(cont=0;cont<=CMP_ICO_QNT;cont++)
	{
		cmp_box[cont] = gtk_box_new(1,0);
//		sprintf(name,"icone%i",cont);
		gtk_widget_set_name(cmp_box[cont],"icone");
		eventos[cont] = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(eventos[cont]),cmp_box[cont]);
		gtk_box_pack_start(GTK_BOX(comprasl[0]),eventos[cont],0,0,40);
//		memset(name,0x0,strlen(name));
	}

	//icone solicitacoes
  gtk_box_pack_end(GTK_BOX(cmp_box[0]),sol_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(cmp_box[0]),sol_ico,0,0,0);

	//icone cotacoes
  gtk_box_pack_end(GTK_BOX(cmp_box[1]),cot_lbl,0,0,0);
  gtk_box_pack_end(GTK_BOX(cmp_box[1]),cot_ico,0,0,0);

  //icone ordem de compra
  gtk_box_pack_end(GTK_BOX(cmp_box[2]),ord_lbl,0,0,0);
  gtk_box_pack_end(GTK_BOX(cmp_box[2]),ord_ico,0,0,0);

	//icone entradas
  gtk_box_pack_end(GTK_BOX(cmp_box[3]),ent_nfe_lbl,0,0,0);
  gtk_box_pack_end(GTK_BOX(cmp_box[3]),ent_nfe_ico,0,0,0);


	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(solicitacao),NULL);
	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(cotacao),NULL);
	g_signal_connect(eventos[2],"button_press_event",G_CALLBACK(ordem_cmp),NULL);
	g_signal_connect(eventos[3],"button_press_event",G_CALLBACK(entrada),NULL);
	return 0;
}
