int multiplo_und()
{
	mult_und = malloc(51);
	mult_und = (gchar *) gtk_entry_get_text(GTK_ENTRY(mult_und_field));
	if(strlen(mult_und)>8)
	{
		popup(NULL,"Valor muito grande");
		gtk_widget_grab_focus(mult_und_field);
		return 1;
	}
	else
	if(strlen(mult_und)<=0)
	{	
		popup(NULL,"Por favor, insira um Multiplo");
		gtk_widget_grab_focus(mult_und_field);
		return 1;
	}
	else
	{
		if(stoi(mult_und)==-1)
		{
			gtk_widget_grab_focus(mult_und_field);
			popup(NULL,"O multiplo deve\nser Numérico");
			g_print("Multiplo: %s\n",mult_und);
			return 1;
		}
		else
		{
		
			
//			gtk_widget_grab_focus(concluir);
		}
	}
	g_print("Multiplo: %s\n",mult_und);
	return 0;
}
