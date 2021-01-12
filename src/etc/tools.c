#include "sql_tools.c"

void carregar_interface(){
  while (g_main_context_pending(NULL))
    g_main_context_iteration(NULL,FALSE);
  return ;
}

gchar *get_db_formated_date(gchar *date_row){
  int dia, mes, ano;
	if(sscanf(date_row, "%d-%d-%d", &ano, &mes, &dia)!=3){
		return NULL;
	}
	GTimeZone *tz = g_time_zone_new(NULL);
	GDateTime *datetime = g_date_time_new(tz, ano, mes, dia, 0, 0, 0);

	return g_date_time_format(datetime, "%d/%m/%Y");

}

GtkWidget *get_pop_parents_wnd(){
  GtkWidget *parent=NULL;

  if(janelas_gerenciadas.principal.janela_pointer && GTK_IS_WINDOW(janelas_gerenciadas.principal.janela_pointer))
    parent = janelas_gerenciadas.principal.janela_pointer;
  else
  if(janelas_gerenciadas.fundo_inicializacao.janela_pointer && GTK_IS_WINDOW(janelas_gerenciadas.fundo_inicializacao.janela_pointer))
    parent = janelas_gerenciadas.fundo_inicializacao.janela_pointer;
  else
  if(janelas_gerenciadas.login.janela_pointer && GTK_IS_WINDOW(janelas_gerenciadas.login.janela_pointer))
    parent = janelas_gerenciadas.login.janela_pointer;
  else
  if(janelas_gerenciadas.fundo_inicializacao.janela_pointer && GTK_IS_WINDOW(janelas_gerenciadas.fundo_inicializacao.janela_pointer))
    parent = janelas_gerenciadas.fundo_inicializacao.janela_pointer;

  return parent;
}

int validar_sessao_criada(){

  if(!janelas_gerenciadas.aplicacao.criada || !janelas_gerenciadas.principal.aberta){

    return 0;
  }

  if(janelas_gerenciadas.principal.sys_close_wnd)
    return 0;

  if(sessao_oper.status_sessao == SESSAO_NULA){
    popup(get_pop_parents_wnd(),"Sessão com erro, o incidente será reportado");
		autologger("!!!!!!!!!!!!!!!Sistema utilizado sem uma sessao ativa!!!!!!!!!!!!!!!");
		encerrando();
		return 1;
	}

  GDateTime *atual = g_date_time_new_now_local();
  if(g_date_time_compare(atual, sessao_oper.expiracao) >=0 ){
    gchar *msg = malloc(100);
    sprintf(msg, "data atual = %s\n", g_date_time_format (atual, "%F %T"));
    file_logger(msg);
    sprintf(msg, "data expiracao = %s\n", g_date_time_format (sessao_oper.expiracao, "%F %T"));
    file_logger(msg);
    fechar_sessao();
		popup(janelas_gerenciadas.login.janela_pointer,"Sessão expirada!");
    autologger("Sessão expirada");
		return 1;
	}

  return 0;
}


void icon_view_select(GtkIconView *icon_view, GtkTreePath *path, gpointer data){
  GtkTreeIter iter;
  char *posicao;
  GdkPixbuf *pixbuf;
  int identificacao=0;
  g_print("recebendo valor do treeicon\n");

  if(gtk_tree_model_get_iter(GTK_TREE_MODEL(data),&iter,path)){
    gtk_tree_model_get(GTK_TREE_MODEL(data),&iter,
      0,&posicao,
      1,&pixbuf,
      2,&identificacao,
      -1);
  }
  else{
    g_print("Não foi possivel encontrar iter\n");
  }

  if(janelas_gerenciadas.vetor_janelas[identificacao].fun)
    janelas_gerenciadas.vetor_janelas[identificacao].fun();

  g_print("IconView posicao: %s\n",posicao);
}


int comparar_datas(gchar *primeira, gchar *segunda){
  int dia1=0, mes1=0, ano1=0;
  int dia2=0, mes2=0, ano2=0;

  if(sscanf( primeira,"%d/%d/%d", &dia1, &mes1, &ano1)!=3)
    return DEFAULT_ERROR_CODE;

  if(sscanf( segunda, "%d/%d/%d", &dia2, &mes2, &ano2)!=3)
    return DEFAULT_ERROR_CODE;

  GTimeZone *tz1 = g_time_zone_new(NULL);
  GDateTime *gdt1 = g_date_time_new(tz1,ano1,mes1,dia1,0,0,0);
  if(!gdt1)
    return DEFAULT_ERROR_CODE;

  GTimeZone *tz2 = g_time_zone_new(NULL);
  GDateTime *gdt2 = g_date_time_new(tz2,ano2,mes2,dia2,0,0,0);
  if(!gdt2)
    return DEFAULT_ERROR_CODE;

  return g_date_time_compare(gdt1, gdt2);
}

xmlNodePtr get_tag_by_namepath(xmlDoc *doc, char *namepath){
  xmlNodePtr root = xmlDocGetRootElement(doc);
  xmlXPathContextPtr contxt = xmlXPathNewContext(doc);
  xmlXPathObjectPtr node_contxt= xmlXPathEval((xmlChar*)namepath,contxt);

  //xmlXPathRegisterNs(node_contxt,  BAD_CAST "CadConsultaCadastro4", BAD_CAST "http://www.portalfiscal.inf.br/nfe/wsdl/CadConsultaCadastro4");
  //xmlXPathRegisterNs(node_contxt,  BAD_CAST "nfe", BAD_CAST "http://www.portalfiscal.inf.br/nfe");

  xmlNodePtr node=NULL;
  if(node_contxt &&
    node_contxt->nodesetval &&
    node_contxt->nodesetval->nodeNr &&
    node_contxt->nodesetval->nodeTab){

    node = node_contxt->nodesetval->nodeTab[0];
  }

  return node;
}

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


gchar *get_full_ender_from_cep(gchar *cep, int num){

  MYSQL_RES *res;
  MYSQL_ROW row;
  char query[MAX_QUERY_LEN];
  gchar *ender = NULL;
  sprintf(query,"select l.descricao, l.descricao_bairro, c.descricao, l.UF  from logradouro as l inner join cidade as c on l.id_cidade = c.id_cidade where CEP = '%s'",cep);
  if(!(res = consultar(query))){
    popup(NULL,"Erro ao consultar endereços");
    return NULL;
  }

  if((row = mysql_fetch_row(res))){

    gchar *logr = NULL;
    gchar *cnum = NULL;
    gchar *bairro = NULL;
    gchar *cidade = NULL;
    gchar *uf = NULL;

    if(row[0]){
      logr = malloc(strlen( row[0] ) );
      sprintf(logr,"%s",row[0]);
    }else{
      logr = strdup("");
    }

    if(num){
      cnum = malloc(12);
      sprintf(cnum,"%i",num);
    }else{
      cnum = strdup("");
    }

    if(row[1]){
      bairro = malloc(strlen( row[1] ) );
      sprintf(bairro,"%s",row[1]);
    }else{
      bairro = strdup("");
    }

    if(row[2]){
      cidade = malloc(strlen( row[2] ) );
      sprintf(cidade,"%s",row[2]);
    }else{
      cidade = strdup("");
    }

    if(row[3]){
      uf = malloc(strlen( row[3] ) );
      sprintf(uf,"%s",row[3]);
    }else{
      uf = strdup("");
    }
    ender = malloc(strlen(logr) + strlen(cnum) + strlen(bairro) + strlen(cidade) + strlen(uf) + 10);
    sprintf(ender, "%s,%s,%s,%s,%s", logr, cnum, bairro, cidade, uf);
  }

  return ender;
}

int treeview_id_exists(GtkTreeView *treeview, int id){

  gchar *id_char = malloc(12);
  GtkTreeIter iter;
  GtkTreeStore *model = (GtkTreeStore *) gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
  if(!model){
    return 0;
  }
  if(!gtk_tree_model_iter_children(GTK_TREE_MODEL(model), &iter, NULL)){
    return 0;
  }

  do{
    gtk_tree_model_get (GTK_TREE_MODEL(model), &iter,
      0, &id_char, -1);

    int id_int = atoi(id_char);
    if(id_int == id){
      return 1;
    }
  }while(gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &iter));

  return 0;
}

char  *format_only_num(char *text){

  if(!text)
    return NULL;

  int cont2=0;
  char *formated_text = malloc(strlen(text)+1);
  strcpy(formated_text,"");

  for(int cont=0;cont<strlen(text);cont++){
    if(isdigit(text[cont])){
      formated_text[cont2] = text[cont];
      cont2++;
    }
  }
  formated_text[cont2] = '\0';

  return formated_text;
}

char *formatar_littobig(char *string){
  for(int cont=0;cont<strlen(string);cont++){
    if(isalpha(string[cont]) && islower(string[cont]))
      string[cont] -= 32;
  }
  return string;
}

void checkcellrenderer ( GtkCellRendererToggle *cell )
{
    int active = gtk_cell_renderer_toggle_get_active ( cell );
    if ( active ){
        gtk_cell_renderer_toggle_set_active (GTK_CELL_RENDERER_TOGGLE ( cell ), FALSE );
    }
    else{
        gtk_cell_renderer_toggle_set_active (GTK_CELL_RENDERER_TOGGLE ( cell ), TRUE) ;
    }
    return;
}

//abreviar palavras em um texto
char *abrevia_text(char *text) {

  if(!text)
    return NULL;

  int tamanho = strlen(text);
  char *token = strtok(text, " ");
  char *texto_todo=NULL;
  char *texto_todo2=NULL;

  while(token) {

    char *token2 = strdup(token);
    if(strlen(token2)>5){
      token2[5] = '.';
      token2[6] = '\0';
    }

    if(texto_todo2){
      texto_todo2 = realloc(texto_todo2, strlen(texto_todo) + strlen(token2) + 2);
      sprintf(texto_todo2, "%s %s", texto_todo, token2);
    }
    else{
      texto_todo2 = malloc( strlen(token2) + 2 );
      sprintf(texto_todo2, "%s ",token2);
    }

    texto_todo = strdup(texto_todo2);

    printf("\n%s", texto_todo);
    token = strtok(NULL, " ");
  }
  return texto_todo;
}


//converte float para char
char *floattochar(float floatnum){
  char *number = malloc(12);
  sprintf(number, "%.2f", floatnum);
  return number;
}

//converte inteiro para char
char *inttochar(int intnum){
  char *number = malloc(12);
  sprintf(number, "%i", intnum);
  return number;
}

//Função abaixo substitui ocorrencia de string em um texto
// retirado de https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/ em novembro de 2020
char* replaceWord(const char* s, const char* oldW,
                  const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;

            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}


void passar_campo(GtkWidget *widget,gpointer widget2)
{
	gtk_widget_grab_focus(widget2);
}

int is_texto(char *texto){
  for(int cont=0;cont<strlen(texto);cont++){
    if(isalpha(texto[cont])){
      return 1;
    }
    if(isalnum(texto[cont])){
      return 1;
    }
  }
  return 0;
}

char *text_to_html(char *texto){

  char *string = strdup(texto);
  int posicoes[strlen(string)], qnt=0;

  for(int cont=0;cont<strlen(string);cont++){
    g_print("%i : %i - '%c'\n",cont, string[cont], string[cont]);
    if( string[cont] == 10 ){
      posicoes[cont] = 1;
      qnt++;
    }else{
      posicoes[cont] = 0;
    }
  }

  int real_length = strlen(string)+qnt*4;
  int cont2=0;
  char *string2 = malloc(real_length);

  for(int cont=0;cont<strlen(string);cont++){

    if( posicoes[cont] ){
      string2[cont2] = '<';
      cont2++;
      string2[cont2] = 'b';
      cont2++;
      string2[cont2] = 'r';
      cont2++;
      string2[cont2] = '>';
      cont2++;
      continue;
    }

    string2[cont2] = string[cont];
    cont2++;
  }
  string2[cont2] = '\0';

  return string2;
}

void doc_gerar_header(FILE *file, char *title){
  if(!file)
    return ;
  fprintf(file,"<!DOCTYPE html>\n");
  fprintf(file,"<html>\n");
  fprintf(file,"<head>\n");
  fprintf(file,"<meta charset=\"utf-8\"/>");
  fprintf(file,"<link href=\"%s\" rel=\"stylesheet\">\n",CSS_ORC);
  fprintf(file,"<title>%s</title>\n",title);

  fprintf(file,"<div id=\"div-titulo\">\n");
  fprintf(file,"<img id=\"logo-img\" src=\"%s\" \n",IMG_IMP_LOGO);
  fprintf(file,"</div>\n");
  fprintf(file,"</head>\n");
  fprintf(file,"<div id=\"caixa-imp\">\n");
  return ;
}

char  *string_to_int(char *string){
  int cont2=0;
  char *formated_string = strdup(string);
  strcpy(formated_string,"");

  for(int cont=0;cont<strlen(string);cont++){
    if(isdigit(string[cont])){
      formated_string[cont2] = string[cont];
      cont2++;
    }
  }

	formated_string[cont2] = '\0';
  return formated_string;
}

char *status_tit_str(int status){

  switch (status) {
    case STAT_QUITADO:
      return "Baixado";
    case STAT_PARC_BAIXA:
      return "Baixado Parcialmente";
    case STAT_PENDENTE:
      return "Pendente";
  }

  return "Sem Status Definido";
}

char *formatar_data(char *data){

	int dia=0, mes=0, ano=0;
	int formats_qnt=4;

	if(!data || !strlen(data)){
    data = strdup( data_sys );
  }

	char *format = string_to_int(data);
	if(!format)
		return NULL;

	//possiveis formatos de data
	char *formats[] = {"%2d%2d%4d",
                    "%2d%2d%2d",
                    "%1d%1d%4d",
                    "%1d%1d%2d"};

	for(int cont=0;cont<formats_qnt;cont++){
			if(sscanf(format,formats[cont],&dia,&mes,&ano)==3){
        if(ano<1900)
          ano += 2000;
				GTimeZone *tz = g_time_zone_new(NULL);
				GDateTime *gdatetime = g_date_time_new(tz,ano,mes,dia,0,0,0);
				if(gdatetime){
					return g_date_time_format(gdatetime,"%d/%m/%Y");
				}
			}
	}

	popup(NULL,"Formato de data não identificado");
	return NULL;
}

void receber_psq_code_space(GtkTreeView *treeview, GtkTreePath *path,  GtkTreeViewColumn *column, GtkWidget *window)
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *codigo;
	codigo = malloc(MAX_CODE_LEN);

	/*if(GTK_TREE_VIEW(button))
	{
		treeview = GTK_TREE_VIEW(button);
	}*/

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));
	if(!gtk_tree_selection_get_selected(selection, &model, &iter))
		return ;
	gtk_tree_model_get (model, &iter, 0, &codigo, -1);

	if(pesquisa_global_alvo){
		gtk_entry_set_text(GTK_ENTRY(pesquisa_global_alvo),codigo);
		gtk_widget_activate(GTK_WIDGET(pesquisa_global_alvo));
	}

	gtk_widget_destroy(window);
}

void auto_hmover_scroll(GtkWidget *widget, GdkRectangle *null, GtkWidget *scroll_window){
	GtkAdjustment *ajuste = gtk_scrolled_window_get_hadjustment(GTK_SCROLLED_WINDOW(scroll_window));
	gtk_adjustment_set_value(ajuste, gtk_adjustment_get_upper(ajuste));
	return ;
}

void auto_vmover_scroll(GtkWidget *widget, GdkRectangle *null, GtkWidget *scroll_window){
	GtkAdjustment *ajuste = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll_window));
	gtk_adjustment_set_value(ajuste, gtk_adjustment_get_upper(ajuste));
	return ;
}

void button_mover_scroll(GtkButton *button, GtkWidget *scroll_window){

	GtkAdjustment *ajuste = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scroll_window));
	gtk_adjustment_set_value(ajuste, gtk_adjustment_get_upper(ajuste));
	return ;

}

char *get_elem_from_path(char *path){
	char *new_path;
	new_path = malloc(strlen(path));
	int cont1=0;
	for(int cont2=0;cont2<=strlen(path);cont2++){
		new_path[cont1] = path[cont2];

		cont1++;

		if(path[cont2] == '\\'||path[cont2] == '/')
			cont1 = 0;
	}

	return new_path;
}

void get_filename_to_entry(GtkFileChooserButton *fchooser, GtkEntry *entry){
		gtk_entry_set_text(entry,gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fchooser)));
}

void encerrando()
{
	int err;
	char query[MAX_QUERY_LEN];
	char *enc_infos;
	enc_infos = malloc(MAX_LOG_DESC);

	//enviar aqui todas informacoes importantes para o banco
	sprintf(query,"insert into wnd_logger(id_janela,nome_janela,estado,qnt_aberta,operador,tempo) values(%i,'%s',%i,%i,%i,NOW())",
  REG_CORRECT_FINAL,
  "Encerrando...",
  0,
  0,
  sessao_oper.code);
	err = mysql_query(&conectar,query);
	if(err!=0)
	{
		popup(NULL,"Não foi possivel salvar status da sessão\n");
		file_logger(query);
		file_logger((char*)mysql_error(&conectar));
	}

	//sprintf(enc_infos,"Finalizando aplicacao");

	//autologger(enc_infos);

	gtk_main_quit();
	return ;
}


void esconder_widget_callback(GtkWidget *widget,gpointer *ponteiro){
  if(ponteiro)
    if(GTK_IS_WIDGET(ponteiro))
      gtk_widget_hide(GTK_WIDGET(ponteiro));
}

int close_window_callback(GtkWidget *widget,gpointer *ponteiro){
	if(ponteiro)
		if(GTK_IS_WIDGET(ponteiro))
			gtk_widget_destroy(GTK_WIDGET(ponteiro));
	return 0;
}

char *randomizar_string(){

		int i;
    char *res = malloc(RANDOM_STRING_SIZE + 1);

    srand(time( NULL ));
    for(i = 0; i < RANDOM_STRING_SIZE; i++) {
        res[i] = (char) (rand()%(122-97))+97;
    }

    res[i] = '\0';
    return res;
}


int file_logger(char *string){
	FILE *logger;

	logger = fopen(LOGGER,"a+");

	if(logger)
		fprintf(logger,"%s\n",string);
	else{
    if(erro_logger>=2)
      exit(1);

    erro_logger++;
		popup(NULL,"Não foi possivel atualizar logs, verifique com suporte");
		return 1;
	}
  erro_logger=0;
	fclose(logger);
	return 0;
}

int autologger(char *string)
{
	char *string1, *string2,*unvulned_query;
  GDateTime *data = g_date_time_new_now(g_time_zone_new(NULL));
	logging = 1;
	string1 = malloc(MAX_QUERY_LEN+strlen(string) + strlen(g_date_time_format(data,"%F %T")));
	string2 = malloc(MAX_QUERY_LEN+strlen(string));

	sprintf(string1,"%s - %s",g_date_time_format(data,"%F %T"), string);
  //ainda um pouco pesado, vou melhorar...

/*
	for(int cont=0;cont<strlen(string1);cont++){
		if(string1[cont] == '\n')
			string1[cont] = ' ';
		if(string1[cont] == '\0' || string1[cont] == -1)
			break;
	}
	unvulned_query = malloc(strlen(string1)*2);

	if(primeira_conexao!=0)
		mysql_real_escape_string(&conectar,unvulned_query,string1,strlen(string1));

	sprintf(string2,"insert into logs(descricao,data) values('%s',CURRENT_TIMESTAMP());",unvulned_query);

	if(strlen(string2)>MAX_LOG_DESC)
		string2[MAX_LOG_DESC] = '\0';

	if(enviar_query(string2)!=0)
		g_print("Log não pode ser enviado\n%s\n",string2);
*/
  file_logger(string1);
//	file_logger(string2);

	logging = 0;
	return 0;
}


int tasker(char *table)
{
	char task[8];
	MYSQL connect;

	MYSQL_RES *result_vetor;
	MYSQL_ROW campos;

	int err=0,task_num=0;
	char query[MAX_QUERY_LEN];

	sprintf(query,"select MAX(code) from %s;",table);
	result_vetor = consultar(query);

	if(result_vetor == NULL)
	{
		popup(NULL,"Não foi possivel receber o id do servidor");
		return 1;
	}

	campos = mysql_fetch_row(result_vetor);
	if(campos==NULL)
	{
		return 1;
	}

	if(campos[0])
		task_num = atoi(campos[0]);

	if(task_num==-1)
	{
		return 1;
	}
	return (task_num+1);
}

char *tipo_ter_num_to_str(int num){
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	int cont=1;
	tipo_ter_list = malloc(MAX_TIPOS_TER*MAX_TIPO_TER);

	if(!tipo_ter_load){
			sprintf(query,"select nome from tipo_terceiros order by code");
			if(!(res = consultar(query))){
				popup(NULL,"Erro ao consultar tipo de terceiro");
				tipo_ter_load = 0;
				return NULL;
			}
			while((row = mysql_fetch_row(res))){
				tipo_ter_list[cont] = malloc(MAX_TIPO_TER);
				strcpy(tipo_ter_list[cont],row[0]);
				if(cont>=MAX_TIPOS_TER){
					popup(NULL,"Tipos de terceiros excedeu limite");
					return NULL;
				}
				cont++;
			}
			tipo_ter_load=1;
	}

	g_print("valor numerico '%i' '%s'\n",num, tipo_ter_list[num]);
	return tipo_ter_list[num];
}

char *ped_status_from_int(int code){
	switch (code) {
		case 0:
			return "Pendente";

		case STATUS_PED_EMIT:
			return "Emitido";

		case STATUS_PED_CAN:
			return "Cancelado";
	}
	return "";
}

char **get_csv_line(char *line){

  int v_=0,v=0,pos=0;
  int length[200];
  for(int cont=0;cont<strlen(line);cont++){
    if(line[cont] == ';')
      v_++;
  }

  char **vetor = malloc( strlen(line) * v_);
  vetor[0] = malloc(strlen(line));
  strcpy(vetor[0],"");
  for(int cont=0;cont<strlen(line);cont++){

    if(line[cont] == ';'){

      vetor[v][pos] = '\0';
      v++;
      pos = 0;
      vetor[v] = malloc(strlen(line));
      strcpy(vetor[v],"");
      continue;

    }

    vetor[v][pos] = line[cont];
    pos++;
  }
  return vetor;

}
