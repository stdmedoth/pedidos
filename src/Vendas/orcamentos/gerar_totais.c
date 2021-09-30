static int gerar_total_geral(){

	char *muda_label;
	muda_label = malloc(sizeof(char*)*MAX_PRECO_LEN*3);
	total_geral_orc = 0;
	desconto_geral_orc = 0;

	orc_valores.valor_prds = 0;
	orc_valores.valor_total = 0;
	orc_valores.desconto_total = 0;
	orc_valores.valor_prds_desc = 0;
	orc_valores.valor_prds_liquido = 0;
	orc_valores.valor_frete_liquido = 0;

	for(int cont=1;cont<MAX_PROD_ORC;cont++)
	{
		if(ativos[cont].id == 1)
		{
			ativos[cont].total_f = ((ativos[cont].qnt_f)*(ativos[cont].preco_f))-(ativos[cont].desconto_f);

			total_geral_orc = total_geral_orc + ativos[cont].total_f;
			desconto_geral_orc = desconto_geral_orc + ativos[cont].desconto_f;
			if(total_geral_orc<0)
			{
				sprintf(muda_label,"R$ %.2f",total_geral_orc);
				gtk_label_set_text(GTK_LABEL(total_geral_orc_label),muda_label);

				sprintf(muda_label,"R$ %.2f",desconto_geral_orc);
				gtk_label_set_text(GTK_LABEL(desconto_geral_orc_label),muda_label);
				popup(NULL,"Total Negativo! Verifique o tipo de desconto");
				gtk_widget_grab_focus(desconto_prod_orc_entry[cont]);
				return 1;
			}
		}
	}
	orc_valores.valor_prds = total_geral_orc;
	orc_valores.valor_prds_desc = desconto_geral_orc;
	orc_valores.valor_prds_liquido = total_geral_orc - desconto_geral_orc;

	orc_valores.valor_frete_liquido =  orc_valores.valor_frete - orc_valores.desconto_frete;

	orc_valores.valor_total = orc_valores.valor_prds + orc_valores.valor_frete - (orc_valores.valor_prds_desc + orc_valores.desconto_frete);
	orc_valores.desconto_total = orc_valores.valor_prds_desc +  orc_valores.desconto_frete;

	if(!orc_transp_frete_pago_mudado && orc_transp_frete_pago_int && !alterando_orc &&!concluindo_orc){
		if( orc_valores.valor_prds_liquido >= orc_transp_frete_pago_vlr ){
			orc_transp_frete_gratis();
		}else{
			orc_transp_frete_ngratis();
		}
	}


	sprintf(muda_label,"R$ %.2f",orc_valores.valor_total);
	gtk_label_set_text(GTK_LABEL(total_geral_orc_label),muda_label);

	sprintf(muda_label,"R$ %.2f",orc_valores.desconto_total);
	gtk_label_set_text(GTK_LABEL(desconto_geral_orc_label),muda_label);

	sprintf(muda_label,"R$ %.2f",orc_valores.valor_frete);
	gtk_label_set_text(GTK_LABEL(frete_orc_label),muda_label);

	rec_tipo_condpag();

	return 0;
}
