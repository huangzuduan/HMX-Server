-- --------------------------------------------------------
-- 主机:                           127.0.0.1
-- 服务器版本:                        5.6.33-log - MySQL Community Server (GPL)
-- 服务器操作系统:                      Win64
-- HeidiSQL 版本:                  9.3.0.5120
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- 导出 hmx_admin 的数据库结构
CREATE DATABASE IF NOT EXISTS `hmx_admin` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `hmx_admin`;

-- 导出  表 hmx_admin.user 结构
CREATE TABLE IF NOT EXISTS `user` (
  `uid` int(11) NOT NULL DEFAULT '0',
  `name` char(32) NOT NULL,
  `pass` char(32) NOT NULL,
  `logintime` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 正在导出表  hmx_admin.user 的数据：~0 rows (大约)
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT IGNORE INTO `user` (`uid`, `name`, `pass`, `logintime`) VALUES
	(0, 'admin', '202cb962ac59075b964b07152d234b70', 1476176982);
/*!40000 ALTER TABLE `user` ENABLE KEYS */;


-- 导出 hmx_data 的数据库结构
CREATE DATABASE IF NOT EXISTS `hmx_data` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `hmx_data`;

-- 导出  表 hmx_data.chatmsg 结构
CREATE TABLE IF NOT EXISTS `chatmsg` (
  `char_id` bigint(20) NOT NULL,
  `newcount` int(20) NOT NULL,
  `totalcount` int(20) NOT NULL,
  `bin_data` blob
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 正在导出表  hmx_data.chatmsg 的数据：~0 rows (大约)
/*!40000 ALTER TABLE `chatmsg` DISABLE KEYS */;
/*!40000 ALTER TABLE `chatmsg` ENABLE KEYS */;

-- 导出  表 hmx_data.itemslots 结构
CREATE TABLE IF NOT EXISTS `itemslots` (
  `char_id` bigint(20) NOT NULL,
  `capacity` int(11) NOT NULL,
  `usecapacity` int(11) NOT NULL,
  `bin_data` blob,
  PRIMARY KEY (`char_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 正在导出表  hmx_data.itemslots 的数据：~0 rows (大约)
/*!40000 ALTER TABLE `itemslots` DISABLE KEYS */;
/*!40000 ALTER TABLE `itemslots` ENABLE KEYS */;

-- 导出  表 hmx_data.levelsort 结构
CREATE TABLE IF NOT EXISTS `levelsort` (
  `sortid` int(11) NOT NULL,
  `uid` bigint(20) NOT NULL,
  `name` char(32) NOT NULL,
  `level` int(11) NOT NULL,
  `bin_data` blob,
  PRIMARY KEY (`sortid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='等级排行榜';

-- 正在导出表  hmx_data.levelsort 的数据：~0 rows (大约)
/*!40000 ALTER TABLE `levelsort` DISABLE KEYS */;
/*!40000 ALTER TABLE `levelsort` ENABLE KEYS */;

-- 导出  表 hmx_data.quest 结构
CREATE TABLE IF NOT EXISTS `quest` (
  `char_id` bigint(20) NOT NULL COMMENT '角色ID',
  `main_last_id` int(11) NOT NULL DEFAULT '10001' COMMENT '上个完成主任务id',
  `bin_data` blob,
  PRIMARY KEY (`char_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='任务';

-- 正在导出表  hmx_data.quest 的数据：~0 rows (大约)
/*!40000 ALTER TABLE `quest` DISABLE KEYS */;
/*!40000 ALTER TABLE `quest` ENABLE KEYS */;

-- 导出  表 hmx_data.relation 结构
CREATE TABLE IF NOT EXISTS `relation` (
  `id` bigint(20) DEFAULT NULL,
  `state` tinyint(4) DEFAULT NULL,
  `myuid` bigint(20) DEFAULT NULL,
  `friuid` bigint(20) DEFAULT NULL,
  `createtime` int(11) DEFAULT NULL,
  `dealreltime` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 正在导出表  hmx_data.relation 的数据：~0 rows (大约)
/*!40000 ALTER TABLE `relation` DISABLE KEYS */;
/*!40000 ALTER TABLE `relation` ENABLE KEYS */;

-- 导出  表 hmx_data.user 结构
CREATE TABLE IF NOT EXISTS `user` (
  `ID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `ACCID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `NAME` char(33) NOT NULL,
  `LEVEL` smallint(6) unsigned NOT NULL DEFAULT '0',
  `VIP` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `STATUS` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `SCENEID` bigint(20) unsigned NOT NULL DEFAULT '0',
  `MAPID` int(10) unsigned NOT NULL DEFAULT '0',
  `ROLETYPE` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `EXP` int(10) unsigned NOT NULL DEFAULT '0',
  `POSX` int(10) unsigned NOT NULL DEFAULT '0',
  `POSY` int(10) unsigned NOT NULL DEFAULT '0',
  `GOLD` int(10) unsigned NOT NULL DEFAULT '0',
  `SILVER` int(10) unsigned NOT NULL DEFAULT '0',
  `COPPER` int(10) unsigned NOT NULL DEFAULT '0',
  `LASTLOGIN` int(10) unsigned NOT NULL DEFAULT '0',
  `COUNTRY` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `TEAMID` int(10) unsigned NOT NULL DEFAULT '0',
  `INFO` blob,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 正在导出表  hmx_data.user 的数据：~0 rows (大约)
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT IGNORE INTO `user` (`ID`, `ACCID`, `NAME`, `LEVEL`, `VIP`, `STATUS`, `SCENEID`, `MAPID`, `ROLETYPE`, `EXP`, `POSX`, `POSY`, `GOLD`, `SILVER`, `COPPER`, `LASTLOGIN`, `COUNTRY`, `TEAMID`, `INFO`) VALUES
	(100000001, 1, '李雅静', 100, 0, 0, 40104, 104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _binary 0x1000000000000000080000000000000000000000);
/*!40000 ALTER TABLE `user` ENABLE KEYS */;


-- 导出 hmx_login 的数据库结构
CREATE DATABASE IF NOT EXISTS `hmx_login` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `hmx_login`;

-- 导出  表 hmx_login.account 结构
CREATE TABLE IF NOT EXISTS `account` (
  `ID` bigint(20) unsigned NOT NULL,
  `USERNAME` char(33) NOT NULL,
  `PASSWORD` char(33) NOT NULL,
  `CREATETIME` int(10) unsigned NOT NULL,
  `LASTLOGIN` int(10) unsigned NOT NULL,
  `STATE` tinyint(3) unsigned NOT NULL,
  `TYPE` tinyint(3) unsigned NOT NULL,
  `INFO` blob
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 正在导出表  hmx_login.account 的数据：~1 rows (大约)
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT IGNORE INTO `account` (`ID`, `USERNAME`, `PASSWORD`, `CREATETIME`, `LASTLOGIN`, `STATE`, `TYPE`, `INFO`) VALUES
	(1, 'Ph4Gh4Me2Yl5Lf1Xf2Rc1Sc3Gg1Wk5Nq', 'Du9Wf9Fo3Vs3Tk1Pr8Pg2Xr9Nr9Ys5Mw', 0, 0, 0, 0, _binary 0x1000000000000000080000000100000000000000),
	(3, 'Cy0Yy8Qp0Vi0Ef3Mz3Im6Ka6Vw4Re3Zk', 'Yc9Fx5Ls4Yp6Fa1Po2Ef7Zb2Oe1Uv7Va', 0, 0, 0, 0, _binary 0x1000000000000000080000000100000000000000),
	(4, 'Bo0Gp4Ey7Fp7Np3Jv9Vi1Ya6Ye3Wq1Qr', 'Qp4Xu3Jl2Ov6Ow6Xw9Ms1Cb9Co0Sf7Kv', 0, 0, 0, 0, _binary 0x1000000000000000080000000100000000000000),
	(8, 'At7Dk7Ly9Yh1Ix9Sw3Kk4Fn2Xx3Rz7Mn', 'Mg8Oo6Et9Yh7Ko8Ug9Qr8Dd8Ut2Io5Wa', 0, 0, 0, 0, _binary 0x1000000000000000080000000100000000000000);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
