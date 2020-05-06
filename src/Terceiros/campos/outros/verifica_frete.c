int frete_frag_int;
int verifica_frete()
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(frete_pago_flag)))
	{
		frete_frag_int=1;
		gtk_widget_set_sensitive(frete_pago_entry,TRUE);
		gtk_widget_grab_focus(frete_pago_entry);
	}
	else
	{
		frete_frag_int=0;
		gtk_widget_set_sensitive(frete_pago_entry,FALSE);
		gtk_widget_grab_focus(concluir_ter_buttom);
	}
	return 0;
}
float vlr_frete_pago_float;
gchar *vlr_frete_pago_gchar;
int rec_vlr_frete()
{
	vlr_frete_pago_gchar = malloc(MAX_PRECO_LEN);
	
	vlr_frete_pago_gchar = (gchar*) gtk_entry_get_text(GTK_ENTRY(frete_pago_entry));
	g_print("Tamanho vlr_frete_pago_gchar %li\n",strlen(vlr_frete_pago_gchar));
	g_print("vlr_frete_pago_gchar %s\n",vlr_frete_pago_gchar);
	if(strlen(vlr_frete_pago_gchar)<=0)
	{
		verifica_frete();
		if(frete_frag_int==0)
		{
			vlr_frete_pago_gchar = malloc(MAX_PRECO_LEN);
			strcpy(vlr_frete_pago_gchar,"");
			return 0;
		}
		popup(NULL,"Digite o valor minimo para frete pago");
		return 1;
	}
	
	if(critica_real(vlr_frete_pago_gchar, frete_pago_entry)!=0)
		return 1;
	
	return 0;
}
