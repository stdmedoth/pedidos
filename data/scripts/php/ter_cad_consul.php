<?php

	$VENDOR_DIR = "vendor/";
	require_once $VENDOR_DIR . 'autoload.php';

	use NFePHP\NFe\Convert;
	use NFePHP\NFe\Tools;
	use NFePHP\Common\Certificate;
	use NFePHP\NFe\Complements;
	use NFePHP\NFe\Common\Standardize;

	$config = [
   "atualizacao" => "2020-08-07 13:03:00",
   "tpAmb" => 1, // Se deixar o tpAmb como 2 você emitirá a nota em ambiente de homologação(teste) e as notas fiscais aqui não tem valor fiscal
   "razaosocial" => "V. A. DE S. SAVA CONGELADOS",
   "siglaUF" => "SP",
   "cnpj" => "30186940000188",
   "schemes" => "PL_009_V4",
   "versao" => "4.00",
   "tokenIBPT" => "AAAAAAA"
   ];

	$configJson = json_encode($config);
	include "acoes/dados.php";
	include "acoes/logger.php";
	$conteudo_certificado = file_get_contents('/usr/share/petitto/files/scripts/php/files/iceminas.pfx');
	$certificate = Certificate::readPfx($conteudo_certificado , '1234');
  $tools = new Tools($configJson, $certificate);
	$tools->model('55');

	$dados = ler_cadter_infos();

	if(!$dados){
		logger("Não foi possivel ler xml de infos");
		return ;
	}

	$cnpj =  $dados->cnpj->__toString();
	$uf = $dados->uf->__toString();
	$iest = '';
  $cpf = '';

	

	$response = $tools->sefazCadastro($uf, $cnpj, $iest, $cpf);

	$file = fopen("/usr/share/petitto/files/scripts/php/files/dados_retorno.xml","w");

	if(!$file){
		logger("Não foi possivel abrir xml de retorno");
		return ;
	}

	fprintf($file,$response);

	fclose($file);

?>
