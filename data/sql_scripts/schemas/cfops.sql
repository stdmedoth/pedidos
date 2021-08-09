CREATE TABLE if not exists cfops(
  _GRUPO_CFOP_ VARCHAR(2000),
  CFOP DOUBLE,
  DESCRIO_CFOP VARCHAR(2000),
  Incio_Vigncia datetime default '2021-01-01'
);
