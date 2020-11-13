#include "mkt_ico.h"

int mkt_ico(void)
{

	int cont,cont2=0,linha=0;
	//imagem dos icones

	//label dos icones

	//caixas onde ficarao os icones
	//cria eventos para cada botao
	/*
	for(cont=0;cont<MKT_ICO_QNT;cont++)
	{
		mkt_box[cont] = gtk_box_new(1,0);
		gtk_container_set_border_width(GTK_CONTAINER(mkt_box[cont]),1);

		gtk_widget_set_name(mkt_box[cont],"icone");

		eventos[cont] = gtk_event_box_new();
		gtk_container_add(GTK_CONTAINER(eventos[cont]),mkt_box[cont]);

		if(cont2==ICOL)
		{
			linha++;
			cont2=0;
		}
		gtk_box_pack_start(GTK_BOX(marketingl[linha]),eventos[cont],0,0,45);
		cont2++;
	}*/

	//icone cadastro produto
  //gtk_box_pack_end(GTK_BOX(cad_box[0]), ,0,0,0);
	//gtk_box_pack_end(GTK_BOX(cad_box[0]), ,0,0,0);

	//sinais para chamada da opçao...
	//g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(),NULL);
	//g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(),NULL);

	return 0;
}
