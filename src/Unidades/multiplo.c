int multiplo_und()
{
	mult_und = malloc(51);
	mult_und = (gchar *) gtk_entry_get_text(GTK_ENTRY(mult_field));
	if(strlen(mult_und)>8)
	{
		popup(NULL,"Valor muito grande");
		gtk_widget_grab_focus(mult_field);
		mult_und_err=1;
		return 1;
	}
	else
	if(strlen(mult_und)<=0)
	{	
		popup(NULL,"Por favor, insira um Multiplo");
		gtk_widget_grab_focus(mult_field);
		mult_und_err=1;
		return 1;
	}
	else
	{
		if(stoi(mult_und)==-1)
		{
			gtk_widget_grab_focus(mult_field);
			popup(NULL,"O multiplo deve\nser Numérico");
			g_print("Multiplo: %s\n",mult_und);
			preco_prod_err=1;
			return 1;
		}
		else
		{
		
			preco_prod_err=0;
			gtk_widget_grab_focus(concluir);
		}
	}
	g_print("Multiplo: %s\n",mult_und);
	return 0;
}
