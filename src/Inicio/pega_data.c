/* cria data para o sistema*/
char dia_sys[3];
char mes_sys[3];
char ano_sys[5];
char *data_sys;

int pegar_data()
{
	struct tm *tempo_struct;
	time_t tempo;
	time(&tempo);
	tempo_struct = localtime(&tempo);

	data_sys = malloc(sizeof(char*)*15); 
	if(tempo_struct->tm_mday < 10)
	{
		sprintf(dia_sys,"0%i",tempo_struct->tm_mday);
	}
	else
	{
		sprintf(dia_sys,"%i",tempo_struct->tm_mday);
	}
	if(tempo_struct->tm_mon < 10)
	{
		sprintf(mes_sys,"0%i",tempo_struct->tm_mon+1);
	}
	else
	{
		sprintf(mes_sys,"%i",tempo_struct->tm_mon+1);
	}
	sprintf(ano_sys,"%i",tempo_struct->tm_year+1900);
	sprintf(data_sys,"%s/%s/%s",dia_sys,mes_sys,ano_sys);
	return 0;
}
