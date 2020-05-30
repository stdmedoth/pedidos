int preco_prod_orc(GtkWidget *widget,int posicao)
{
	preco_prod_orc_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(preco_prod_orc_entry[posicao]));
	ativos[posicao].preco_f = 0; 

	if(strlen(preco_prod_orc_gchar)<=0)
	{	
		preco_alterado[posicao] = 0;
		valor_orig[posicao] = 0;
		popup(NULL,"O preco deve ser inserido");
		gtk_widget_grab_focus(preco_prod_orc_entry[posicao]);
		return 1;
	}
	for(int pos=0;pos<=strlen(preco_prod_orc_gchar);pos++)
	{
		if(preco_prod_orc_gchar[pos]==46||preco_prod_orc_gchar[pos]==44)
		{	
			#ifdef __linux__
			preco_prod_orc_gchar[pos] = 46;
			#endif
			#ifdef WIN32
			preco_prod_orc_gchar[pos] = 44;
			#endif
		}
	}
	ativos[posicao].preco_f = atof(preco_prod_orc_gchar);
	strcpy(ativos[posicao].preco_c,preco_prod_orc_gchar);
	critica_real(ativos[posicao].preco_c,preco_prod_orc_entry[posicao]);
	
	g_print("float preco %.2f\n",ativos[posicao].preco_f);
	gtk_widget_grab_focus(qnt_prod_orc_entry[posicao]);
	return 0;
}
