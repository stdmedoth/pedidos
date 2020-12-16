int alterando_ter=0;

GtkWidget *concluir_ter_buttom,
*alterar_ter_buttom,
*psq_ter_button,
*cancelar_ter_buttom,
*excluir_ter_buttom;

#include "campos.c"
#include "cancela.c"
#include "altera.c"
#include "exclui.c"
#include "conclui.c"

int inicializar_ter()
{
	int i;

	for(i=0;i<=CAMPOS_QNT;i++)
		vet_erro[i] = 0;

	for(int cont=0;cont<MAX_CNTTS_QNT;cont++){
		cntt_exists[cont] = 0;
		cntts[cont].ativo = 0;
	}

	//char *
	codigos_ter = malloc(MAX_CODE_LEN);
	prods_ter = malloc(MAX_CODE_LEN);
	codigos_ter_nfe = malloc(MAX_CODE_LEN*2);
	doc_ter = malloc(CNPJ_S_LEN);
	nomes_ter = malloc(MAX_RAZ_LEN);
	endereco_ter = malloc(MAX_ADR_LEN);
	bairro_ter = malloc(MAX_CID_LEN);
	cep_ter = malloc(MAX_CEP_LEN);
	tipo_ter = malloc(MAX_TIPO_LEN);
	memset(tipo_ter,0x0,strlen(tipo_ter));
	observacoes_ter = malloc(MAX_OBS_LEN);
	prazo_ter = malloc(MAX_DATE_LEN);
	alterando_ter=0;
	//GtkWidget *
	produto_label = malloc(sizeof(GtkLabel*)*MAX_PROD);
	codigo_preco = malloc(sizeof(int*)*MAX_PROD);
	preco_entry = malloc(sizeof(GtkEntry*)*MAX_PROD);
	precos_caixas = malloc(sizeof(GtkBox*)*MAX_PROD);
	atualizar_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	remover_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	imagem_ok = malloc(sizeof(GtkImage*)*MAX_PROD);
	imagem_cancel = malloc(sizeof(GtkImage*)*MAX_PROD);
	imagem_dinheiro = malloc(sizeof(GtkImage*)*MAX_PROD);
	atualizar_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	remover_preco = malloc(sizeof(GtkButton*)*MAX_PROD);
	find_subgrupos_restrict = malloc(sizeof(struct duo_widget));
	return 0;
}

struct _terc_infos *terceiros_get_terceiro(int code){

	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[MAX_QUERY_LEN];
	struct _terc_infos *terceiros = malloc(sizeof(struct _terc_infos));
	terceiros->contatos = malloc(sizeof(struct _Contato)*MAX_CNTTS_QNT);

	sprintf(query,"select * from terceiros where code = %i", code);
  if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar dados da entrega");
    return NULL;
  }

	if((row = mysql_fetch_row(res))){
		terceiros->code = atoi(row[COD_TER_COL]);
		terceiros->razao = strdup(row[RAZ_TER_COL]);
		terceiros->ie = strdup(row[IE_TER_COL]);
		terceiros->doc = strdup(row[IE_TER_COL]);
		terceiros->tipo_terc = atoi(row[TIPI_TER_COL]);
		terceiros->cep = strdup(row[CEP_TER_COL]);
		terceiros->i_nro = atoi(row[REND_TER_COL]);
		terceiros->c_nro = strdup(row[REND_TER_COL]);
	}else{
		popup(NULL,"Cliente/Fornecedor não existente!");
    return NULL;
	}

	sprintf(query,"select * from logradouro where CEP = '%s'", terceiros->cep);
	if(!(res = consultar(query))){
    popup(NULL,"Não foi possível consultar logradouro da entrega");
    return NULL;
  }

	if((row = mysql_fetch_row(res))){
		terceiros->xLgr = strdup(row[CEP_DESCR_COL]);
		terceiros->xCpl = strdup(row[CEP_COMPLEM_COL]);
		terceiros->xBairro = strdup(row[CEP_DESCR_BAIRRO]);
		terceiros->xMun = strdup(row[CEP_DESCRCID_COL]);
		terceiros->UF = strdup(row[CEP_UF_COL]);
	}else{
		popup(NULL,"Cliente/Fornecedor sem endereço!");
    return NULL;
	}

	int contatos_qnt = 0;
	sprintf(query,"select * from contatos where terceiro = %i", code);
	if(!(res = consultar(query))){
		popup(NULL,"Não foi possível consultar contatos do terceiro");
		return NULL;
	}
	while((row = mysql_fetch_row(res))){
		terceiros->contatos[contatos_qnt].id = atoi(row[CTTO_ID_COL]);
		terceiros->contatos[contatos_qnt].nome = strdup(row[CTTO_NOME_COL]);
		terceiros->contatos[contatos_qnt].celular = strdup(row[CTTO_CEL_COL]);
		terceiros->contatos[contatos_qnt].telefone = strdup(row[CTTO_TEL_COL]);
		terceiros->contatos[contatos_qnt].email = strdup(row[CTTO_EMAIL_COL]);
		contatos_qnt++;
	}
	terceiros->contatos_qnt = contatos_qnt;
	return terceiros;
}

int  cad_terc()
{
	char task[20];
	sprintf(task,"%i",tasker("terceiros"));
	g_print("task %s\n",task);
	//linhas
	GError *gerro;
	GtkWidget *janela;
	GtkWidget *psq_ter_box;
	GtkWidget *vinculo_prod_frame, *vinculo_prod_box,*vinculo_prod_scroll;
	GtkWidget *precos_entrys;

	GtkWidget *horizontal_box_one,
	*horizontal_box_two,
	*horizontal_box_three,
	*horizontal_box_four,
	*horizontal_box_five,
	*horizontal_box_six,
	*horizontal_box_seven,
	*horizontal_box_eight,
	*horizontal_box_nine;

	GtkWidget *atualiza_ter_prc_button;
	GtkWidget *caixa_grande;
	//container/visual
	GtkWidget *fixed, *fixed2, *box,*vertical_box1, *vertical_box2, *separator;
	GtkWidget *fixed3, *box2,*vertical_box3;
	GtkWidget *fixed4 , *box3, *vertical_box4;
	GtkWidget *fixed5 ,*box4, *vertical_box5;
	GtkWidget *fixed6 ,*box5, *vertical_box6;
	GtkWidget *opcoes;
	GtkWidget *code, *code_ter_nfe_box, *doc, *inscr, *name, *address, *cep,*type, *address_num;
	GtkWidget *celular, *telefone,*acao, *email, *observacoes,*prazo;
	GtkWidget *observacoes_scroll;
	GtkWidget *bair_cid_uf_boxv1,*bair_cid_uf_boxv2,*bair_cid_uf_boxv3,*bair_cid_uf_boxh;
	GtkWidget *complmt_ter_box, *complmt_ter_label;
	GtkWidget *addr_log_num_box,*addr_log_num_fixed, *logr_address;
	GtkWidget *prazo_box;

	GtkWidget *ter_entrega_frame,*ter_endereco_frame;

	GtkWidget *ter_img_box,
	*ter_img_frame,
	*ter_img_buttons_box;

	GtkWidget *prod, *psq_prod_box,
	*prod_ter_label;

	janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(janela,"terceiros");
	gtk_window_set_position(GTK_WINDOW(janela),3);
	gtk_window_set_resizable(GTK_WINDOW(janela),FALSE);
	gtk_window_set_title(GTK_WINDOW(janela),"Terceiros");
	gtk_window_set_icon_name(GTK_WINDOW(janela),"avatar-default");
	gtk_window_set_transient_for(GTK_WINDOW(janela),GTK_WINDOW(janela_principal));
	gtk_container_set_border_width (GTK_CONTAINER (janela), 10);
	g_signal_connect(GTK_WINDOW(janela),"delete-event",G_CALLBACK(gtk_widget_destroy),&janela);


	/*registrando a janela para o reg_win*/
	janelas_gerenciadas.vetor_janelas[REG_CAD_TER].reg_id = REG_CAD_TER;
	janelas_gerenciadas.vetor_janelas[REG_CAD_TER].aberta = 1;
	if(ger_janela_aberta(janela, &janelas_gerenciadas.vetor_janelas[REG_CAD_TER]))
		return 1;
	janelas_gerenciadas.vetor_janelas[REG_CAD_TER].janela_pointer = janela;

	inicializar_ter();

	psq_ter_transp_button = gtk_button_new();
	psq_ter_transp_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_ter_transp_button),psq_ter_transp_img);
	psq_ter_transp_box = gtk_box_new(0,0);

	psq_ter_transpcep_button = gtk_button_new();
	psq_ter_transpcep_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_ter_transpcep_button),psq_ter_transpcep_img);
	psq_ter_transpcep_box = gtk_box_new(0,0);

	psq_ter_cep_button = gtk_button_new();
	psq_ter_cep_img = gtk_image_new_from_file(IMG_PESQ);
	gtk_button_set_image(GTK_BUTTON(psq_ter_cep_button),psq_ter_cep_img);
	psq_ter_cep_box = gtk_box_new(0,0);

	frete_pago_flag = gtk_check_button_new_with_label("Frete Pago?");
	vinc_transporte_flag = gtk_check_button_new_with_label("Preencher dados da entrega.");
	frete_pago_box = gtk_box_new(1,0);
	gtk_widget_set_name(frete_pago_box,"caixa");
	frete_pago_frame = gtk_frame_new("Valor mínimo para frete Pago");
	frete_pago_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(frete_pago_entry),"R$ 0.0");
	gtk_container_add(GTK_CONTAINER(frete_pago_frame),frete_pago_entry);
	gtk_box_pack_start(GTK_BOX(frete_pago_box),frete_pago_flag,0,0,0);
	gtk_box_pack_start(GTK_BOX(frete_pago_box),frete_pago_frame,0,0,0);

	ter_notebook = gtk_notebook_new();

	ter_principal_box = gtk_box_new(1,0);
	ter_contatos_box = gtk_box_new(1,0);
	ter_entrega_box = gtk_box_new(0,0);
	ter_financeiro_box = gtk_box_new(1,0);
	ter_outros_box = gtk_box_new(1,0);
	opcoes = gtk_box_new(0,0);
	caixa_grande = gtk_box_new(1,0);

	bair_cid_uf_boxv1 = gtk_box_new(1,0);
	bair_cid_uf_boxv2 = gtk_box_new(1,0);
	bair_cid_uf_boxv3 = gtk_box_new(1,0);
	bair_cid_uf_boxh = gtk_box_new(0,0);

	acao = gtk_box_new(0,0);
	acao_atual = gtk_label_new("Ação atual: ");
	acao_atual2 = gtk_label_new("Cadastrando");
	gtk_widget_set_name(acao_atual2,"acao_atual");
	gtk_box_pack_start(GTK_BOX(acao),acao_atual,0,0,0);
	gtk_box_pack_start(GTK_BOX(acao),acao_atual2,0,0,5);

	lista_vinc_label = gtk_label_new("Preços Vinculados:");
 	precos_scroll_caixa	 = gtk_box_new(1,0);
	precos_scroll_window = gtk_scrolled_window_new(NULL,NULL);

	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(precos_scroll_window),GTK_POLICY_ALWAYS,GTK_POLICY_ALWAYS);

	gtk_container_add(GTK_CONTAINER(precos_scroll_window),precos_scroll_caixa);

	gtk_box_pack_start(GTK_BOX(precos_scroll_caixa),lista_vinc_label,0,0,20);

	gtk_widget_set_size_request(precos_scroll_window,200,500);

	fixed = gtk_fixed_new();
	fixed2 = gtk_fixed_new();
	fixed3 = gtk_fixed_new();
	fixed4 = gtk_fixed_new();
	fixed5 = gtk_fixed_new();

	horizontal_box_one = gtk_box_new(0,0);
	horizontal_box_two = gtk_box_new(0,0);
	horizontal_box_three = gtk_box_new(0,0);
	horizontal_box_four = gtk_box_new(0,0);
	horizontal_box_five = gtk_box_new(0,0);
	horizontal_box_six = gtk_box_new(0,0);
	horizontal_box_seven = gtk_box_new(0,0);
	horizontal_box_eight = gtk_box_new(0,0);
	horizontal_box_nine = gtk_box_new(0,0);

	box = gtk_box_new(0,0);
	box2 = gtk_box_new(0,0);
	box3 = gtk_box_new(0,0);
	box4 = gtk_box_new(0,0);
	vertical_box1 = gtk_box_new(1,0);
	vertical_box2 = gtk_box_new(1,0);
	vertical_box3 = gtk_box_new(1,0);
	vertical_box4 = gtk_box_new(1,0);
	vertical_box5 = gtk_box_new(1,0);
	vertical_box6 = gtk_box_new(1,0);
	separator = gtk_separator_new(1);

	cnst_cad_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(cnst_cad_button),gtk_image_new_from_icon_name("emblem-web",GTK_ICON_SIZE_LARGE_TOOLBAR));

	doc_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(doc_combo),0,"Tipo Pessoa:");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(doc_combo),"1","Jurídica");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(doc_combo),"2","Física");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(doc_combo),"3","Sem CNPJ/CPF");
	gtk_combo_box_set_active(GTK_COMBO_BOX(doc_combo),0);

	code_label = gtk_label_new("Codigo: ");
	doc_label = gtk_label_new("Documento:");
	code_ter_nfe_label = gtk_label_new("Código para NF-e");
	name_label = gtk_label_new("Nome: ");
	inscr_label = gtk_label_new("IE/RG:");
	addr_log_num_box = gtk_box_new(0,0);
	addr_log_num_fixed = gtk_fixed_new();
	address_num = gtk_box_new(1,0);
	cep_label = gtk_label_new("Cep: ");
	address_label= gtk_label_new("Logradouro: ");
	cidade_label= gtk_label_new("Cidade: ");
	bairro_label = gtk_label_new("Bairro: ");
	address_num_label = gtk_label_new("Número: ");
	complmt_ter_label = gtk_label_new("Complemento: ");
	address_num_field = gtk_entry_new();
	uf_label = gtk_label_new("UF: ");
	uf_ter_field = gtk_entry_new();

	rua_combo = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(rua_combo),0,("Tipo:"));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"1",(tip_logds[0]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"2",(tip_logds[1]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"3",(tip_logds[2]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"4",(tip_logds[3]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"5",(tip_logds[4]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"6",(tip_logds[5]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"7",(tip_logds[6]));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(rua_combo),"8",("Outros"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(rua_combo),0);

	type_label = gtk_frame_new("Tipo Terceiro: ");

	concluir_ter_buttom = gtk_button_new_with_label("Concluir");
	alterar_ter_buttom = gtk_button_new_with_label("Alterar");
	cancelar_ter_buttom = gtk_button_new_with_label("Cancelar");
	excluir_ter_buttom = gtk_button_new_with_label("Excluir");

	code_ter_field = gtk_entry_new();
	psq_ter_button = gtk_button_new();
	psq_ter_box = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(psq_ter_box),code_ter_field,0,0,0);
	gtk_button_set_image(GTK_BUTTON(psq_ter_button),gtk_image_new_from_file(IMG_PESQ));
	gtk_box_pack_start(GTK_BOX(psq_ter_box),psq_ter_button,0,0,0);
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(code_ter_field),GTK_ENTRY_ICON_PRIMARY,"emblem-system");

	code_ter_nfe_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(code_ter_nfe_field),GTK_ENTRY_ICON_PRIMARY,"network-server");

	doc_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(doc_ter_field),GTK_ENTRY_ICON_PRIMARY,"user-info");

	inscr_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(inscr_ter_field),GTK_ENTRY_ICON_PRIMARY,"user-info");

	name_ter_field = gtk_entry_new();
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(name_ter_field),GTK_ENTRY_ICON_PRIMARY,"avatar-default");

	cep_ter_field = gtk_entry_new();
	address_ter_field = gtk_entry_new();
	cidade_ter_field = gtk_entry_new();
	bairro_ter_field = gtk_entry_new();
	complmt_ter_field = gtk_entry_new();

	gtk_entry_set_placeholder_text(GTK_ENTRY(cep_ter_field),"");
	gtk_entry_set_placeholder_text(GTK_ENTRY(complmt_ter_field),"Complemento");
	gtk_entry_set_icon_from_icon_name(GTK_ENTRY(address_ter_field),GTK_ENTRY_ICON_PRIMARY,"mark-location");
	gtk_entry_set_width_chars(GTK_ENTRY(address_ter_field),30);
	gtk_entry_set_width_chars(GTK_ENTRY(cep_ter_field),9);
	gtk_box_pack_start(GTK_BOX(psq_ter_cep_box),cep_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_ter_cep_box),psq_ter_cep_button,0,0,0);

	type_ter_field = gtk_combo_box_text_new();
	gtk_combo_box_text_insert_text(GTK_COMBO_BOX_TEXT(type_ter_field),0,("Escolha o tipo"));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(type_ter_field),"1",("Cliente"));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(type_ter_field),"2",("Fornecedor"));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(type_ter_field),"3",("Cliente e Fornecedor"));
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(type_ter_field),"4",("Transportadora"));
	gtk_combo_box_set_active(GTK_COMBO_BOX(type_ter_field),0);

	code = gtk_box_new(1,0);
	gtk_widget_set_name(code,"caixa");
	gtk_box_pack_start(GTK_BOX(code),code_label,0,0,0);
	gtk_box_pack_end(GTK_BOX(code),psq_ter_box,0,0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(code_ter_field),10);
	gtk_entry_set_text(GTK_ENTRY(code_ter_field),task);
	gtk_widget_set_size_request(code_ter_field,50,30);

	code_ter_nfe_box = gtk_box_new(1,0);
	gtk_widget_set_name(code_ter_nfe_box,"caixa");
	gtk_box_pack_start(GTK_BOX(code_ter_nfe_box),code_ter_nfe_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(code_ter_nfe_box),code_ter_nfe_field,0,0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(code_ter_nfe_field),10);
	gtk_entry_set_text(GTK_ENTRY(code_ter_nfe_field),"");
	gtk_widget_set_size_request(code_ter_nfe_field,50,30);

	doc = gtk_box_new(0,0);
	gtk_widget_set_name(doc,"caixa");
	gtk_box_pack_start(GTK_BOX(doc),doc_combo,0,0,0);
	gtk_box_pack_start(GTK_BOX(doc),doc_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(doc),cnst_cad_button,0,0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(doc_ter_field),30);

	inscr = gtk_box_new(1,0);
	gtk_widget_set_name(inscr,"caixa");
	gtk_box_pack_start(GTK_BOX(inscr),inscr_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(inscr),inscr_ter_field,0,0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(inscr_ter_field),25);

	name = gtk_box_new(1,0);
	gtk_widget_set_name(name,"caixa");
	gtk_box_pack_start(GTK_BOX(name),name_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(name),name_ter_field,0,0,0);
	gtk_entry_set_width_chars(GTK_ENTRY(name_ter_field),50);

	ter_endereco_frame = gtk_frame_new("Endereço Cliente");
	ter_entrega_frame = gtk_frame_new("Endereço Entrega");

	address = gtk_box_new(1,0);
	gtk_widget_set_name(address,"caixa");
	logr_address = gtk_box_new(1,0);
	complmt_ter_box = gtk_box_new(1,0);

	cep = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(cep),cep_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(cep),psq_ter_cep_box,0,0,0);
	gtk_box_pack_start(GTK_BOX(cep),rua_combo,0,0,10);
	gtk_box_pack_start(GTK_BOX(cep),vinc_transporte_flag,0,0,10);
	gtk_box_pack_start(GTK_BOX(address),cep,0,0,5);

	gtk_entry_set_width_chars(GTK_ENTRY(address_num_field),5);
	gtk_box_pack_start(GTK_BOX(address_num),address_num_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(address_num),address_num_field,0,0,0);
	gtk_fixed_put(GTK_FIXED(addr_log_num_fixed),address_num,0,0);

	gtk_box_pack_start(GTK_BOX(logr_address),address_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(logr_address),address_ter_field,0,0,0);

	gtk_box_pack_start(GTK_BOX(complmt_ter_box),complmt_ter_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(complmt_ter_box),complmt_ter_field,0,0,0);

	gtk_box_pack_start(GTK_BOX(addr_log_num_box),logr_address,0,0,5);
	gtk_box_pack_start(GTK_BOX(addr_log_num_box),addr_log_num_fixed,0,0,5);
	gtk_box_pack_start(GTK_BOX(addr_log_num_box),complmt_ter_box,0,0,5);

	gtk_box_pack_start(GTK_BOX(address),addr_log_num_box,0,0,0);

	gtk_container_add(GTK_CONTAINER(ter_endereco_frame),address);

	gtk_box_pack_start(GTK_BOX(bair_cid_uf_boxv1),bairro_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(bair_cid_uf_boxv1),bairro_ter_field,0,0,5);

	gtk_box_pack_start(GTK_BOX(bair_cid_uf_boxv2),cidade_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(bair_cid_uf_boxv2),cidade_ter_field,0,0,5);

	gtk_box_pack_start(GTK_BOX(bair_cid_uf_boxv3),uf_label,0,0,5);
	gtk_box_pack_start(GTK_BOX(bair_cid_uf_boxv3),uf_ter_field,0,0,5);

	gtk_box_pack_start(GTK_BOX(bair_cid_uf_boxh),bair_cid_uf_boxv1,0,0,10);
	gtk_box_pack_start(GTK_BOX(bair_cid_uf_boxh),bair_cid_uf_boxv2,0,0,10);
	gtk_box_pack_start(GTK_BOX(bair_cid_uf_boxh),bair_cid_uf_boxv3,0,0,10);

	gtk_entry_set_width_chars(GTK_ENTRY(uf_ter_field),5);

	gtk_box_pack_start(GTK_BOX(address),bair_cid_uf_boxh,0,0,5);

	type = gtk_box_new(1,0);

	gtk_widget_set_name(type,"caixa");
	gtk_container_add(GTK_CONTAINER(type_label),type_ter_field);
	gtk_box_pack_start(GTK_BOX(type),type_label,0,0,0);

	observacoes = gtk_box_new(1,0);
	observacoes_label = gtk_label_new("Observações");
	observacoes_ter_field = gtk_text_view_new();
	observacoes_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_name(observacoes,"caixa");
	gtk_box_pack_start(GTK_BOX(observacoes),observacoes_label,0,0,10);
	gtk_box_pack_start(GTK_BOX(observacoes),observacoes_ter_field,0,0,10);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(observacoes_scroll),GTK_POLICY_ALWAYS,GTK_POLICY_ALWAYS);

	gtk_container_add(GTK_CONTAINER(observacoes_scroll),observacoes);

	gtk_widget_set_size_request(observacoes_ter_field,500,150);
	gtk_widget_set_size_request(observacoes_scroll,500,150);
	gtk_widget_set_size_request(observacoes,500,150);

	prazo = gtk_box_new(1,0);
	gtk_widget_set_name(prazo,"caixa");
	prazo_ter_label = gtk_label_new("Prazo padrão");
	prazo_ter_field = gtk_entry_new();
	campo_nome_cond_ter = gtk_entry_new();
	gtk_entry_set_width_chars(GTK_ENTRY(prazo_ter_field),5);
	gtk_entry_set_width_chars(GTK_ENTRY(prazo_ter_field),8);
	prazo_box = gtk_box_new(0,0);
	psq_ter_cond_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_ter_cond_button),gtk_image_new_from_file(IMG_PESQ));
	gtk_box_pack_start(GTK_BOX(prazo),prazo_ter_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(prazo_box),prazo_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(prazo_box),psq_ter_cond_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(prazo_box),campo_nome_cond_ter,0,0,0);
	gtk_box_pack_start(GTK_BOX(prazo),prazo_box,0,0,0);

	ter_img_box = gtk_box_new(1,0);
	ter_img_buttons_box = gtk_box_new(0,0);
	ter_img_frame = gtk_frame_new("Insira uma imagem");
	ter_img_image = gtk_image_new_from_file(NULL);
	ter_img_button_inserir = gtk_button_new_with_label("Inserir");
	ter_img_button_retirar = gtk_button_new_with_label("Retirar");

	gtk_container_add(GTK_CONTAINER(ter_img_frame),ter_img_image);
	gtk_widget_set_size_request(GTK_WIDGET(ter_img_frame),200,200);
	gtk_widget_set_size_request(GTK_WIDGET(ter_img_image),200,200);
	gtk_box_pack_start(GTK_BOX(ter_img_buttons_box),ter_img_button_inserir,0,0,10);
	gtk_box_pack_start(GTK_BOX(ter_img_buttons_box),ter_img_button_retirar,0,0,10);

	gtk_box_pack_start(GTK_BOX(ter_img_box),ter_img_frame,0,0,10);
	gtk_box_pack_start(GTK_BOX(ter_img_box),ter_img_buttons_box,0,0,10);

	prod = gtk_box_new(1,0);

	psq_prod_box = gtk_box_new(0,0);

	prod_ter_label = gtk_label_new("Produto");

	prod_ter_field = gtk_entry_new();

	campo_nome_prod_ter = gtk_entry_new();

	psq_ter_prod_button = gtk_button_new();
	gtk_button_set_image(GTK_BUTTON(psq_ter_prod_button),gtk_image_new_from_file(IMG_PESQ));

	gtk_box_pack_start(GTK_BOX(psq_prod_box),prod_ter_field,0,0,0);
	gtk_box_pack_start(GTK_BOX(psq_prod_box),psq_ter_prod_button,0,0,0);
	gtk_box_pack_start(GTK_BOX(prod),prod_ter_label,0,0,0);
	gtk_box_pack_start(GTK_BOX(prod),campo_nome_prod_ter,0,0,0);
	gtk_widget_set_sensitive(campo_nome_prod_ter,FALSE);
	gtk_box_pack_start(GTK_BOX(prod),psq_prod_box,0,0,5);

	atualiza_ter_prc_button = gtk_button_new_with_label("Atualizar preços");
	gtk_button_set_image(GTK_BUTTON(atualiza_ter_prc_button),gtk_image_new_from_file(IMG_REC));

	grid1_ter_preco = gtk_grid_new();
	vinculo_prod_box = gtk_box_new(1,0);
	vinculo_prod_frame = gtk_frame_new("Vinculo Produto-Cliente");

	vinculo_prod_scroll = gtk_scrolled_window_new(NULL,NULL);
	gtk_container_add(GTK_CONTAINER(vinculo_prod_scroll),grid1_ter_preco);

	gtk_widget_set_size_request(vinculo_prod_scroll,600,200);
	gtk_widget_set_size_request(grid1_ter_preco,600,200);


	gtk_box_pack_start(GTK_BOX(horizontal_box_one),code,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_one),doc,0,0,0);

	gtk_box_pack_start(GTK_BOX(horizontal_box_two),inscr,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),type,0,0,0);
	gtk_box_pack_start(GTK_BOX(horizontal_box_two),code_ter_nfe_box,0,0,5);

	gtk_box_pack_start(GTK_BOX(horizontal_box_three),name,0,0,10);

	gtk_box_pack_start(GTK_BOX(horizontal_box_four),ter_endereco_frame,0,0,10);

	gtk_box_pack_start(GTK_BOX(horizontal_box_five),observacoes_scroll,0,0,20);

	contatos_qnt=0;
	contatos_box = do_editable_cells();

	if(contatos_box){
		gtk_widget_set_size_request(contatos_box,500,200);
		gtk_box_pack_start(GTK_BOX(horizontal_box_six),contatos_box,0,0,20);
	}

	gtk_box_pack_start(GTK_BOX(horizontal_box_seven),prazo,0,0,10);    //outros
	gtk_box_pack_start(GTK_BOX(horizontal_box_seven),frete_pago_box,0,0,10);

	GtkWidget *lista_titulos = titulos_get_widget(&titulos_cadter);

	gtk_box_pack_start(GTK_BOX(horizontal_box_eight),prod,0,0,10);
	gtk_box_pack_start(GTK_BOX(horizontal_box_eight),atualiza_ter_prc_button,0,0,10);

	precos_entrys = criar_precos_ter_wnd();
	if(precos_entrys)
		gtk_grid_attach(GTK_GRID(grid1_ter_preco),precos_entrys,0,0,1,1);
	gtk_box_pack_start(GTK_BOX(horizontal_box_nine),vinculo_prod_scroll,0,0,10);

	gtk_box_pack_start(GTK_BOX(vinculo_prod_box),horizontal_box_eight,0,0,10);
	gtk_box_pack_start(GTK_BOX(vinculo_prod_box),horizontal_box_nine,0,0,10);
	gtk_container_add(GTK_CONTAINER(vinculo_prod_frame),vinculo_prod_box);

	gtk_box_pack_start(GTK_BOX(opcoes),concluir_ter_buttom,0,0,10);
	gtk_box_pack_start(GTK_BOX(opcoes),alterar_ter_buttom,0,0,10);
	gtk_box_pack_start(GTK_BOX(opcoes),cancelar_ter_buttom,0,0,10);
	gtk_box_pack_start(GTK_BOX(opcoes),excluir_ter_buttom,0,0,10);

	gtk_widget_set_size_request(GTK_WIDGET(concluir_ter_buttom),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(alterar_ter_buttom),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(cancelar_ter_buttom),100,50);
	gtk_widget_set_size_request(GTK_WIDGET(excluir_ter_buttom),100,50);

	g_signal_connect(GTK_ENTRY(code_ter_field),"activate",G_CALLBACK(code_terc),NULL);
	g_signal_connect(GTK_ENTRY(code_ter_nfe_field),"activate",G_CALLBACK(code_ter_nfe),NULL);
	g_signal_connect(doc_combo,"changed",G_CALLBACK(mover_para_doc),NULL);
	g_signal_connect(GTK_ENTRY(doc_ter_field),"activate",G_CALLBACK(escolha_doc),NULL);
	g_signal_connect(GTK_ENTRY(inscr_ter_field),"activate",G_CALLBACK(inscr_terc),NULL);
	g_signal_connect(GTK_ENTRY(name_ter_field),"activate",G_CALLBACK(name_terc),NULL);
	g_signal_connect(GTK_ENTRY(cep_ter_field),"activate",G_CALLBACK(cep_terc),NULL);
	g_signal_connect(GTK_ENTRY(bairro_ter_field),"activate",G_CALLBACK(bairro_terc),NULL);
	g_signal_connect(GTK_ENTRY(address_ter_field),"activate",G_CALLBACK(address_terc),NULL);
	g_signal_connect(GTK_ENTRY(cidade_ter_field),"activate",G_CALLBACK(cidade_terc),NULL);
	g_signal_connect(GTK_ENTRY(uf_ter_field),"activate",G_CALLBACK(uf_terc),NULL);
	g_signal_connect(GTK_ENTRY(address_num_field),"activate",G_CALLBACK(numrua),NULL);
	g_signal_connect(GTK_ENTRY(complmt_ter_field),"activate",G_CALLBACK(complmnt_terc),NULL);

	g_signal_connect(type_ter_field,"changed",G_CALLBACK(escolha_tipo_ter),NULL);
	g_signal_connect(vinc_transporte_flag,"toggled",G_CALLBACK(vinc_transp),NULL);

	g_signal_connect(GTK_ENTRY(prazo_ter_field),"activate",G_CALLBACK(prazo_fun),NULL);
	g_signal_connect(GTK_CHECK_BUTTON(frete_pago_flag),"toggled",G_CALLBACK(verifica_frete),NULL);
	g_signal_connect(GTK_ENTRY(frete_pago_entry),"activate",G_CALLBACK(rec_vlr_frete),NULL);

	g_signal_connect(GTK_BUTTON(psq_ter_cep_button),"clicked",G_CALLBACK(psq_cep),cep_ter_field);

	g_signal_connect(psq_ter_cond_button,"clicked",G_CALLBACK(psq_pag_cond),prazo_ter_field);

	g_signal_connect(GTK_ENTRY(prod_ter_field),"activate",G_CALLBACK(produto_ter),NULL);

	g_signal_connect(GTK_BUTTON(concluir_ter_buttom),"clicked",G_CALLBACK(conclui_ter),NULL);
	g_signal_connect(GTK_BUTTON(alterar_ter_buttom),"clicked",G_CALLBACK(altera_ter),NULL);
	g_signal_connect(GTK_BUTTON(psq_ter_button),"clicked",G_CALLBACK(psq_ter),code_ter_field);
	g_signal_connect(GTK_BUTTON(cancelar_ter_buttom),"clicked",G_CALLBACK(cancelar_ter),NULL);
	g_signal_connect(GTK_BUTTON(excluir_ter_buttom),"clicked",G_CALLBACK(exclui_ter),NULL);
	g_signal_connect(GTK_BUTTON(cnst_cad_button),"clicked",G_CALLBACK(consulta_contrib_wnd),NULL);

	g_signal_connect(janela,"destroy",G_CALLBACK(ger_janela_fechada),&janelas_gerenciadas.vetor_janelas[REG_CAD_TER]);

	g_signal_connect(GTK_BUTTON(psq_ter_prod_button),"clicked",G_CALLBACK(psq_prod),prod_ter_field);
	g_signal_connect(GTK_BUTTON(atualiza_ter_prc_button),"clicked",G_CALLBACK(insere_preco_ter),NULL);

	//page 0
	gtk_widget_set_name(vertical_box1,"vertical_box1");
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_one,MARGEM_D,20);    //codigo cnpj
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_two,MARGEM_D,80);    //inscricao
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_three,MARGEM_D,140); //nome
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_four,MARGEM_D,200);  //cep/endereco tipo ter
	gtk_fixed_put(GTK_FIXED(fixed),horizontal_box_five,MARGEM_D,400);  //observacoes
	gtk_fixed_put(GTK_FIXED(fixed2),horizontal_box_six,MARGEM_D,20);   //contatos

	gtk_fixed_put(GTK_FIXED(fixed4),horizontal_box_seven,MARGEM_D,20); //outros
	if(lista_titulos)
		gtk_fixed_put(GTK_FIXED(fixed4),lista_titulos,MARGEM_D,200);
	gtk_fixed_put(GTK_FIXED(fixed5),vinculo_prod_frame,MARGEM_D,20); //produto e grupo vinculo

	gtk_box_pack_start(GTK_BOX(vertical_box1),acao,0,0,0);//campo dos dados em clientes
	gtk_box_pack_start(GTK_BOX(vertical_box1),fixed,0,0,0);

	gtk_box_pack_start(GTK_BOX(box),vertical_box1,0,0,0);
	gtk_box_pack_start(GTK_BOX(box),separator,0,0,10);


	gtk_box_pack_start(GTK_BOX(vertical_box2),fixed2,0,0,10);

	gtk_box_pack_start(GTK_BOX(box2),vertical_box2,0,0,0);

	box3 = entrega_campos();

	gtk_box_pack_start(GTK_BOX(vertical_box4),fixed4,0,0,10);

	gtk_box_pack_start(GTK_BOX(vertical_box5),fixed5,0,0,10);


	gtk_box_pack_start(GTK_BOX(box4),vertical_box4,0,0,0);

	box5 = gtk_box_new(0,0);
	gtk_box_pack_start(GTK_BOX(box5),vertical_box5,0,0,0);

	//pages on notebook
	gtk_box_pack_start(GTK_BOX(ter_principal_box),box,0,0,0);

	gtk_box_pack_start(GTK_BOX(ter_contatos_box),box2,0,0,0);

	gtk_box_pack_start(GTK_BOX(ter_entrega_box),box3,0,0,0);

	gtk_box_pack_start(GTK_BOX(ter_financeiro_box),box4,0,0,0);

	gtk_box_pack_start(GTK_BOX(ter_outros_box),box5,0,0,0);

	gtk_notebook_append_page(GTK_NOTEBOOK(ter_notebook),ter_principal_box,gtk_label_new("Principal"));
	gtk_notebook_append_page(GTK_NOTEBOOK(ter_notebook),ter_contatos_box,gtk_label_new("Contatos"));
	gtk_notebook_append_page(GTK_NOTEBOOK(ter_notebook),ter_entrega_box,gtk_label_new("Entrega"));
	gtk_notebook_append_page(GTK_NOTEBOOK(ter_notebook),ter_financeiro_box,gtk_label_new("Financeiro"));
	gtk_notebook_append_page(GTK_NOTEBOOK(ter_notebook),ter_outros_box,gtk_label_new("Outros"));

	gtk_box_pack_start(GTK_BOX(caixa_grande),ter_notebook,0,0,0);
	gtk_box_pack_start(GTK_BOX(caixa_grande),opcoes,0,0,10);

	gtk_container_add(GTK_CONTAINER(janela),caixa_grande);
	gtk_widget_set_sensitive(frete_pago_entry,FALSE);
	gtk_widget_set_sensitive(campo_nome_cond_ter,FALSE);

	gtk_widget_show_all(janela);
	vinc_transp();
	cancelar_ter();
	gtk_widget_grab_focus(doc_ter_field);
	return 0;
}
