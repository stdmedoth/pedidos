#define MAX_RAZ_LEN 100
int name_terc()
{
	nomes_ter = (gchar *) gtk_entry_get_text(GTK_ENTRY(name_ter_field));
	if(strlen(nomes_ter)>MAX_RAZ_LEN)
	{
		popup(NULL,"Nome muito grande\nPor favor diminua");
		gtk_widget_grab_focus(GTK_WIDGET(name_ter_field));
		vet_erro[NOM_ERR]=1;
		return 1;
	}
	if(strlen(nomes_ter)<1&&criticar.nome!=0)
	{
		popup(NULL,"Por favor insira um nome para o terceiro");
		gtk_widget_grab_focus(GTK_WIDGET(name_ter_field));
		vet_erro[NOM_ERR]=1;
		return 1;
	}
	else
	{
		vet_erro[NOM_ERR]=0;
		gtk_widget_grab_focus(address_ter_field);
	}
	g_print("nome: %s\n",nomes_ter);
	return 0;
}