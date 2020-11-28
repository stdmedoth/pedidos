create table if not exists grupos( code int primary key auto_increment,
  pai int default 0,
  nome varchar(50) default 'Grupo Sem Nome',
  nivel int default 1 );

create table if not exists unidades( code int primary key auto_increment,
  nome varchar(50) default '',
  sigla varchar(10) default '',
  multiplo int default 1,
  medida int default 0);

create table pis_cofins(
   code int not null primary key,
   cst varchar(2) not null,
   descricao varchar(126) not null
);

CREATE TABLE IF NOT EXISTS `IcmsInterestadual` (
  `code` int(11) NOT NULL AUTO_INCREMENT,
  `origem` varchar(2) NOT NULL,
  `destino` varchar(2) NOT NULL,
  `icms` decimal(10,2) NOT NULL,
  PRIMARY KEY (`code`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=730 ;

CREATE TABLE IF NOT EXISTS `ncm` (
  `code` INT(16) NOT NULL AUTO_INCREMENT ,
  `cod_ncm` VARCHAR(8) NOT NULL ,
  `nome_ncm` VARCHAR(128) NOT NULL ,
  PRIMARY KEY (`code`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;

CREATE INDEX `descricao` ON `ncm` (`nome_ncm` ASC) ;

create table prod_origem(
  code int not null primary key,
  idOrigem int not null,
  nome varchar(200),
  aliquota float
);

create table cst_cson(
  code int not null primary key,
  charIdTrib varchar(3) not null,
  nome varchar(200),
  regime int not null
);

CREATE TABLE  produtos(
  code int(11) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  nome varchar(150) DEFAULT 'Produto Sem Nome',
  peso float DEFAULT '0',
  preco float DEFAULT '0',
  unidades int(11) DEFAULT '1',
  unidades_atacado int(11) DEFAULT '1',
  fornecedor int(11) DEFAULT '1',
  grupo int(11) DEFAULT '1',
  grupo_nivel int(11) DEFAULT '2',
  ncm int NOT NULL ,
  icmscst int NOT NULL ,
  piscst int NOT NULL ,
  pisaliq float not null,
  cofinscst int NOT NULL,
  cofinsaliq float not null,
  origem int NOT NULL,
  observacoes varchar(500) DEFAULT '',
  FOREIGN KEY (unidades) REFERENCES unidades(code),
  FOREIGN KEY (fornecedor) REFERENCES terceiros(code),
  FOREIGN KEY (grupo) REFERENCES grupos(code),
  FOREIGN KEY (ncm) REFERENCES ncm(code),
  FOREIGN KEY (icmscst) REFERENCES cst_cson(code),
  FOREIGN KEY (piscst) REFERENCES pis_cofins(code),
  FOREIGN KEY (cofinscst) REFERENCES pis_cofins(code),
  FOREIGN KEY (origem) REFERENCES prod_origem(code)
);

create table if not exists precos( code int primary key auto_increment,
  produto int default 1,
  valor_fat float default 0.0,
  valor_vist float default 0.0,
  foreign key(produto) references produtos(code));
