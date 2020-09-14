int gerar_orc_header(FILE *file){

  fprintf(file,"<!DOCTYPE html>\n");
  fprintf(file,"<html>\n");
  fprintf(file,"<head>\n");
  fprintf(file,"<meta charset=\"utf-8\"/>");
  fprintf(file,"<link href=\"%s\" rel=\"stylesheet\">\n",CSS_ORC);
  fprintf(file,"<title>Orcamento</title>\n");

  fprintf(file,"<div id=\"caixa-imp\">\n");
  fprintf(file,"<div id=\"div-titulo\">\n");
  fprintf(file,"<img id=\"logo-img\" src=\"%s\" alt=\"PETITTO\">\n",IMG_IMP_LOGO);
  fprintf(file,"</div>\n");
  fprintf(file,"</head>\n");
  return 0;
}
