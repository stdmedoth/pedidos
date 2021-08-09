CREATE TABLE IF NOT EXISTS `ncm` (
  `code` INT(16) NOT NULL AUTO_INCREMENT ,
  `cod_ncm` VARCHAR(8) NOT NULL ,
  `nome_ncm` VARCHAR(128) NOT NULL ,
  PRIMARY KEY (`code`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;
CREATE INDEX IF NOT EXISTS `descricao` ON `ncm` (`nome_ncm` ASC) ;
