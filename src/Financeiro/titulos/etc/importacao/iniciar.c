int import_tits_iniciar(){

  imprt_tits_path_gchar = (gchar*)gtk_entry_get_text(GTK_ENTRY(imprt_tits_entry));
  if(!strlen(imprt_tits_path_gchar)){
    popup(NULL,"Insira o caminho do arquivo");
    return 1;
  }
  FILE *arquivo = fopen(imprt_tits_path_gchar,"r");
  if(!arquivo){
    popup(NULL,"Não foi possível abrir arquivo");
    return 1;
  }
  char *fv_path = malloc(strlen(REL_FIX_FIN_PATH)+strlen("consultar.html"));
  sprintf(fv_path,"%sconsultar.html",REL_FIX_FIN_PATH);
  FILE *f_vericador = fopen(fv_path,"w");
  if(!f_vericador){
    popup(NULL,"Não foi possível abrir arquivo para escrita");
    return 1;
  }

  //imprt_titulos = malloc( sizeof(struct _imprt_titulos *) * MAX_IMP_TITS);

  int pos = 0;
  char *linha = malloc(500);

  char *data = malloc(20);
  char *nome = malloc(200);
  char *valor = malloc(20);
  float total_recebido=0;
  float total_pago=0;
  float total_saldo=0;
  int result=0;

  char html_header[] = "<!DOCTYPE html>"
  "<html>"
    "<head>"
      "<meta charset=\"utf-8\"/>"
      "<title>Relatório de Títulos à Pagar</title>"
      "<link href=\"../../styles/relatorios.css\" rel=\"stylesheet\">"
    "</head>";

  imprt_tits_tipo_int = gtk_combo_box_get_active(GTK_COMBO_BOX(imprt_tits_tipo_combo));
  fprintf(f_vericador,"%s",html_header);
  fprintf(f_vericador,"<body>");
  fprintf(f_vericador,"<div style='background: Gainsboro;'>");
  fprintf(f_vericador,"<h1>Importação de extrato</h1>");
  fprintf(f_vericador,"<p>%s</p>",data_sys);
  fprintf(f_vericador,"</div>");

  fprintf(f_vericador,"<table class='tabela-conteudo'>\n");
  while(fgets(linha,500,arquivo)){
    char **vetor = get_csv_line(linha);

    if(pos >= MAX_IMP_TITS)
      break;
    //struct _imprt_titulos new_tit;
    //imprt_titulos[pos] = &new_tit;

    if(vetor){
      fprintf(f_vericador,"<tr>\n");
      if(vetor[0])
        data = vetor[0];
      if(vetor[1])
        nome = vetor[1];
      if(vetor[2])
        valor = vetor[2];

      if(strlen(nome)>20)
        nome[20] = '\0';

      if(imprt_tits_tipo_int == TP_TIT_PAG){
        if(atof(valor)>=0){
          continue;
        }
      }else
      if(imprt_tits_tipo_int == TP_TIT_REC){
        if(atof(valor)<0){
          continue;
        }
      }


      fprintf(f_vericador,"<td>\n");
      if(nome)
        fprintf(f_vericador,"Nome: %s\n",nome);
      else
        fprintf(f_vericador,"Nome não identificado\n");
      fprintf(f_vericador,"</td>\n");

      fprintf(f_vericador,"<td>\n");
      if(data)
        fprintf(f_vericador,"Data: %s\n",data);
      else
        fprintf(f_vericador,"Data não identificada\n");
      fprintf(f_vericador,"</td>\n");

      fprintf(f_vericador,"<td>\n");
      if(simp_critica_real(valor)){
        fprintf(f_vericador,"Valor a Receber: %.2f (Verifique!)\n",atof(valor));
        fprintf(f_vericador,"<td>\n");
        continue;
      }

      if(atof(valor)>=0){
        total_recebido += atof(valor);
        fprintf(f_vericador,"Valor Recebido: %.2f\n",atof(valor));
      }
      else{
        total_pago += atof(valor);
        fprintf(f_vericador,"Valor Pago: %.2f\n",atof(valor));
      }

      fprintf(f_vericador,"<td>\n");
      pos++;
    }
    else{
      fprintf(f_vericador,"Não identificado %s\n",linha);
    }
    fprintf(f_vericador,"</tr>\n");
    strcpy(nome,"");
    strcpy(data,"");
    strcpy(valor,"");

  }
  fprintf(f_vericador,"<table class='tabela-conteudo'>");
  fprintf(f_vericador,"<tr><td><b>Total Recebido: R$ %.2f</b></td></tr>",total_recebido);
  fprintf(f_vericador,"<tr><td><b>Total Pago: R$ %.2f</b></td></tr>",total_pago);
  total_saldo = total_recebido + total_pago;
  fprintf(f_vericador,"<tr><td><b>Saldo Total: R$ %.2f</b></td></tr>",total_saldo);
  fprintf(f_vericador,"</table>");

  fprintf(f_vericador,"</table>\n");
  fprintf(f_vericador,"</body>");
  fprintf(f_vericador,"</html>");

  fclose(f_vericador);
  fclose(arquivo);
  escolher_finalizacao(fv_path);
  return 0;
}
