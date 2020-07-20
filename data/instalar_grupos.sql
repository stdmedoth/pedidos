-- MySQL dump 10.13  Distrib 5.6.6-m9, for Win32 (x86)
--
-- Host: localhost    Database: erp
-- ------------------------------------------------------
-- Server version	5.6.6-m9-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `grupos`
--

DROP TABLE IF EXISTS `grupos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `grupos` (
  `code` int(11) NOT NULL AUTO_INCREMENT,
  `pai` int(11) DEFAULT '0',
  `nome` varchar(50) DEFAULT 'Grupo Sem Nome',
  `nivel` int(11) DEFAULT '1',
  PRIMARY KEY (`code`)
) ENGINE=InnoDB AUTO_INCREMENT=68 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `grupos`
--

LOCK TABLES `grupos` WRITE;
/*!40000 ALTER TABLE `grupos` DISABLE KEYS */;
INSERT INTO `grupos` VALUES (1,1,'RAIZ',1),(2,1,'Papelão',1),(3,2,'Cinza',2),(4,2,'Face Branca',2),(5,2,'Bolacha de Chopp',2),(6,2,'Folha Avulsa',2),(7,1,'Percalux',1),(8,7,'Liso',2),(9,8,'1,30 Larg. - 25 MT',3),(10,8,'1,30 Larg - 50 MT',3),(11,8,'1,30 Larg - Avulso',3),(12,7,'Metalizado',2),(13,12,' 1,30 Larg./25M',3),(14,12,'1,30 Larg - Avulso',3),(15,7,'Bicolor',2),(16,7,'Ouro',2),(17,7,'Bronze',2),(18,15,'1,30 Larg./25M',3),(19,16,'1,30 Larg./25M',3),(20,17,'1,30 Larg./25M',3),(21,15,'1,30 Larg. - Avulso',3),(22,16,'1,30 Larg. - Avulso',3),(23,17,'1,30 Larg. - Avulso',3),(24,1,'Cabeceado',1),(25,24,' Fita Algodão',2),(26,24,'Filho Acetinado',2),(27,25,'50M -  PCT',3),(28,25,'100M - PCT',3),(29,25,'Metro Diverso - PCT',3),(30,1,'Cola',1),(31,30,'Artecola',2),(32,31,'Litro',3),(33,31,'Galão 5 Litro',3),(34,31,'Balde 10KG',3),(35,1,'Linha ',1),(37,35,'N° 30',2),(38,37,'Capa Dura 2,500M ',3),(39,38,'Marca Cifa',4),(40,35,'N° 10',2),(41,40,'Capa Dura 300M',3),(42,41,'Marca Cifa',4),(43,35,'N° 4',2),(44,43,' Capa Dura 200M',3),(45,44,' Marca Cifa',4),(46,1,'Papel Offset',1),(48,47,'Pacote',3),(49,48,'250Folhas',4),(50,46,' Pacote C/ 250FOLHAS',2),(51,50,'TAM. 66 X 96',3),(52,1,'Película',2),(53,52,'Printek',3),(54,53,'10CM X 122M',4),(55,54,' DIV. Cores',5),(56,53,'15CM X 122M -',4),(57,56,'Ouro',4),(59,53,'20CM X 122M',4),(60,59,'Ouro',4),(61,1,'Resistência',1),(62,61,' HOT STAMP TR2',2),(63,62,'100/220VOLTS',3),(64,1,'Espiral',1),(65,64,'Preta',2),(66,64,'Trasparente',2),(67,64,'Cores',2);
/*!40000 ALTER TABLE `grupos` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-07-19 17:58:23
