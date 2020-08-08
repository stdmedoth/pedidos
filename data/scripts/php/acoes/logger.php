<?php
  function logger($conteudo){

    $file = fopen("/usr/share/petitto/files/scripts/php/files/emissao.log","a+");

    if(!$file){
      return ;
    }

    fprintf($file,$conteudo);
    fclose($file);
  }

?>
