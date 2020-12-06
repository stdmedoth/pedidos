#include "mkt_ico.h"

int mkt_ico(void)
{

	int cont,cont2=0,linha=0;
	//imagem dos icones

	//label dos icones
	mkt_anal_ico = gtk_image_new_from_file(ANLS_MKT_IMG);
	mkt_anal_lbl = gtk_label_new("Análise");

	mkt_email_ico = gtk_image_new_from_file(MODELMAIL_IMG);
	mkt_email_lbl = gtk_label_new("Modelagem Emails");

	mkt_enviomail_ico = gtk_image_new_from_file(ENVMAIL_IMG);
	mkt_enviomail_lbl = gtk_label_new("Envio Emails");

	mkt_mailinglist_ico = gtk_image_new_from_file(MAILILIST_IMG);
	mkt_mailinglist_lbl = gtk_label_new("Lista de Distribuição");

	//caixas onde ficarao os icones
	//cria eventos para cada botao

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
	}

	//icone analise
	gtk_box_pack_end(GTK_BOX(mkt_box[0]), mkt_anal_lbl,0,0,0);
  gtk_box_pack_end(GTK_BOX(mkt_box[0]), mkt_anal_ico,0,0,0);

	//icone emails
	gtk_box_pack_end(GTK_BOX(mkt_box[1]), mkt_email_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(mkt_box[1]), mkt_email_ico,0,0,0);

	//icone lista de Distribuição
	gtk_box_pack_end(GTK_BOX(mkt_box[2]), mkt_mailinglist_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(mkt_box[2]), mkt_mailinglist_ico,0,0,0);

	//icone envio emails
	gtk_box_pack_end(GTK_BOX(mkt_box[3]), mkt_enviomail_lbl,0,0,0);
	gtk_box_pack_end(GTK_BOX(mkt_box[3]), mkt_enviomail_ico,0,0,0);



	//sinais para chamada da opçao...
	g_signal_connect(eventos[0],"button_press_event",G_CALLBACK(mkt_analise),NULL);
	g_signal_connect(eventos[1],"button_press_event",G_CALLBACK(mkt_email_models),NULL);
	g_signal_connect(eventos[2],"button_press_event",G_CALLBACK(mkt_cad_distrib_fun),NULL);
	g_signal_connect(eventos[3],"button_press_event",G_CALLBACK(mkt_models_envia_emails),NULL);

	return 0;
}
