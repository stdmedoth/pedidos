#include "vnd_ico.h"

int vnd_ico(void)
{
	int cont,linha=0;

	//imagem dos icones
	orc_ico = gtk_image_new_from_file(ORC_IMG);
	ped_ico = gtk_image_new_from_file(PED_IMG);
	trsp_ico = gtk_image_new_from_file(TRSP_IMG);
	cx_ico = gtk_image_new_from_file(CX_IMG);

	//label dos icones
	orc_lbl = gtk_label_new("Orçamentos");
	ped_lbl = gtk_label_new("Pedidos");
	cx_lbl = gtk_label_new("PDV");
	trsp_lbl = gtk_label_new("Transportes");

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

	//icone pdv
	gtk_box_pack_end(GTK_BOX(vnd_box[2]),cx_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(vnd_box[2]),cx_ico,0,0,0);

	//icone Transportes
	gtk_box_pack_end(GTK_BOX(vnd_box[3]),trsp_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(vnd_box[3]),trsp_ico,0,0,0);

	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(vnd_orc),NULL);

	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(vnd_ped),NULL);

	g_signal_connect(eventos[2],"button_press_event",G_CALLBACK(pdv_princ_wnd),NULL);

	g_signal_connect(eventos[3],"button_press_event",G_CALLBACK(trsp_cad_fun),NULL);

	return 0;
}
