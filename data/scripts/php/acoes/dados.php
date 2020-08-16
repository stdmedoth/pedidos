<?php

	function ler_cadter_infos(){
		global $DADOS_PATH;
		$DADOS_PATH = "C:\\petitto\\files\\scripts\\php\\files\\dados_emissor.xml";

		$xml = simplexml_load_file($DADOS_PATH);
		if(!$xml)
			return NULL;
		return $xml;
	}

?>
