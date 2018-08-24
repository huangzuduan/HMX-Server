-- --------------------------------------------------------
-- 主机:                           127.0.0.1
-- 服务器版本:                        5.6.39-log - MySQL Community Server (GPL)
-- 服务器操作系统:                      Win64
-- HeidiSQL 版本:                  9.5.0.5196
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- 导出 hmx_config 的数据库结构
CREATE DATABASE IF NOT EXISTS `hmx_config` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `hmx_config`;

-- 导出  表 hmx_config.tb_invitation_activity_manager 结构
CREATE TABLE IF NOT EXISTS `tb_invitation_activity_manager` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '邀请活动主键自增ID',
  `product_id` varchar(36) DEFAULT NULL COMMENT '产品主键',
  `product_name` varchar(20) DEFAULT NULL COMMENT '产品名称',
  `title` varchar(30) NOT NULL COMMENT '邀请活动标题',
  `room_card` int(11) DEFAULT NULL COMMENT '奖励房卡',
  `status` int(11) DEFAULT NULL COMMENT '活动状态(0:启用,1:停用)',
  `create_time` bigint(20) DEFAULT NULL COMMENT '创建时间',
  PRIMARY KEY (`id`),
  KEY `FK_Reference_29` (`product_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='邀请活动管理';

-- 数据导出被取消选择。
-- 导出  表 hmx_config.tb_room_card_free_activity 结构
CREATE TABLE IF NOT EXISTS `tb_room_card_free_activity` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT COMMENT '免费房卡活动主键',
  `product_id` varchar(20) DEFAULT NULL COMMENT '产品ID',
  `product_name` varchar(20) DEFAULT NULL COMMENT '产品名称',
  `activity_name` varchar(20) DEFAULT NULL COMMENT '活动名称',
  `start_time` bigint(20) DEFAULT NULL COMMENT '开始时间',
  `end_time` bigint(20) DEFAULT NULL COMMENT '结束时间',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='房卡免费活动';

-- 数据导出被取消选择。
-- 导出  表 hmx_config.tb_share_activity_manager 结构
CREATE TABLE IF NOT EXISTS `tb_share_activity_manager` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '分享活动主键自增ID',
  `product_id` varchar(36) DEFAULT NULL COMMENT '产品主键',
  `product_name` varchar(20) DEFAULT NULL COMMENT '产品名称',
  `title` varchar(30) NOT NULL COMMENT '分享活动标题',
  `room_card` int(11) DEFAULT NULL COMMENT '奖励房卡',
  `status` int(11) DEFAULT NULL COMMENT '活动状态(0:启用,1:停用)',
  `create_time` bigint(20) DEFAULT NULL COMMENT '创建时间',
  PRIMARY KEY (`id`),
  KEY `FK_Reference_26` (`product_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='分享活动管理';

-- 数据导出被取消选择。

-- 导出 hmx_data 的数据库结构
CREATE DATABASE IF NOT EXISTS `hmx_data` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `hmx_data`;

-- 导出  表 hmx_data.tb_mail 结构
CREATE TABLE IF NOT EXISTS `tb_mail` (
  `id` bigint(20) NOT NULL,
  `type` smallint(6) NOT NULL,
  `from_id` bigint(20) NOT NULL,
  `from_name` varchar(255) NOT NULL,
  `to_id` bigint(20) NOT NULL,
  `to_name` varchar(255) NOT NULL,
  `title` varchar(255) NOT NULL,
  `content` varchar(255) NOT NULL,
  `room_cards` int(11) NOT NULL,
  `mark` smallint(6) NOT NULL,
  `create_time` bigint(20) NOT NULL,
  `fetch_time` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `create_time` (`create_time`),
  KEY `to_id` (`to_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_data.tb_mailsyslog 结构
CREATE TABLE IF NOT EXISTS `tb_mailsyslog` (
  `id` bigint(20) NOT NULL,
  `mail_id` bigint(20) NOT NULL,
  `uid` bigint(20) NOT NULL,
  `mark` smallint(6) NOT NULL,
  `create_time` bigint(20) NOT NULL,
  `fetch_time` bigint(20) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `create_time` (`create_time`),
  KEY `uid` (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_data.tb_rankscore 结构
CREATE TABLE IF NOT EXISTS `tb_rankscore` (
  `uid` bigint(20) NOT NULL,
  `name` varchar(255) NOT NULL,
  `value` int(11) NOT NULL,
  `sort` int(11) NOT NULL,
  `time` bigint(20) NOT NULL,
  `type` int(11) NOT NULL,
  `actor_addr` varchar(255) NOT NULL,
  KEY `sort` (`sort`),
  KEY `type` (`type`),
  KEY `value` (`value`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_data.tb_rankwins 结构
CREATE TABLE IF NOT EXISTS `tb_rankwins` (
  `uid` bigint(20) NOT NULL,
  `name` varchar(255) NOT NULL,
  `value` int(11) NOT NULL,
  `sort` int(11) NOT NULL,
  `time` bigint(20) NOT NULL,
  `type` int(11) NOT NULL,
  `actor_addr` varchar(255) NOT NULL,
  KEY `sort` (`sort`),
  KEY `type` (`type`),
  KEY `value` (`value`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_data.tb_role 结构
CREATE TABLE IF NOT EXISTS `tb_role` (
  `id` bigint(20) NOT NULL,
  `account` varchar(255) NOT NULL,
  `nickname` varchar(255) NOT NULL,
  `level` int(11) NOT NULL,
  `logo_icon` varchar(255) NOT NULL,
  `title` int(11) NOT NULL,
  `diamond` int(11) NOT NULL,
  `coin` int(11) NOT NULL,
  `sexual` int(11) NOT NULL,
  `room_card` int(11) NOT NULL,
  `total_games` int(11) NOT NULL,
  `win_games` int(11) NOT NULL,
  `con_games` int(11) NOT NULL,
  `his_max_score` int(11) NOT NULL,
  `his_max_con` int(11) NOT NULL,
  `week_max_score` int(11) NOT NULL,
  `top_wins_ymd` bigint(20) NOT NULL,
  `top_wins_total` int(11) NOT NULL,
  `top_score_ymd` bigint(20) NOT NULL,
  `top_score_total` int(11) NOT NULL,
  `blocktime` bigint(20) NOT NULL DEFAULT '0',
  `data` blob,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_data.tb_zhanji 结构
CREATE TABLE IF NOT EXISTS `tb_zhanji` (
  `record_id` bigint(20) NOT NULL,
  `room_id` int(11) NOT NULL,
  `room_info` blob NOT NULL,
  `role_info` blob NOT NULL,
  `time` bigint(20) NOT NULL,
  `innrecord` blob NOT NULL,
  `seat_total` blob NOT NULL,
  `inn_replay` blob NOT NULL,
  UNIQUE KEY `room_id` (`record_id`),
  KEY `time` (`time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。

-- 导出 hmx_log 的数据库结构
CREATE DATABASE IF NOT EXISTS `hmx_log` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `hmx_log`;

-- 导出  表 hmx_log.tb_login 结构
CREATE TABLE IF NOT EXISTS `tb_login` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` bigint(20) NOT NULL,
  `time` int(11) NOT NULL,
  `channel` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_log.tb_match_user 结构
CREATE TABLE IF NOT EXISTS `tb_match_user` (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增ID',
  `record_id` int(11) NOT NULL COMMENT '创建一场游戏记录ID',
  `record_time` int(11) NOT NULL COMMENT '创建一场游戏时间',
  `room_no` int(11) NOT NULL COMMENT '创建一场游戏房间号',
  `inn_id` int(11) NOT NULL COMMENT '第几局',
  `match_id` int(11) NOT NULL COMMENT '0日常记录，>0比赛记录',
  `inn_time` int(11) NOT NULL COMMENT '第几局结束时间',
  `huway` int(11) NOT NULL COMMENT '胡牌方式，查看配置表',
  `hutype` int(11) NOT NULL COMMENT '胡牌牌形，查看配置表',
  `huseat` int(11) NOT NULL COMMENT '胡牌的位置',
  `u_1_id` int(11) NOT NULL COMMENT '玩家ID',
  `u_1_score` int(11) NOT NULL COMMENT '玩家本局得分',
  `u_1_total` int(11) NOT NULL COMMENT '玩家当前总分',
  `u_1_angang` int(11) NOT NULL COMMENT '玩家暗杠次数',
  `u_1_minggang` int(11) NOT NULL COMMENT '玩家明杠次数',
  `u_1_goushouggang` int(11) NOT NULL COMMENT '玩家过手杠次数',
  `u_2_id` int(11) NOT NULL COMMENT '玩家ID',
  `u_2_score` int(11) NOT NULL COMMENT '玩家本局得分',
  `u_2_total` int(11) NOT NULL COMMENT '玩家当前总分',
  `u_2_angang` int(11) NOT NULL COMMENT '玩家暗杠次数',
  `u_2_minggang` int(11) NOT NULL COMMENT '玩家明杠次数',
  `u_2_goushouggang` int(11) NOT NULL COMMENT '玩家过手杠次数',
  `u_3_id` int(11) NOT NULL COMMENT '玩家ID',
  `u_3_score` int(11) NOT NULL COMMENT '玩家本局得分',
  `u_3_total` int(11) NOT NULL COMMENT '玩家当前总分',
  `u_3_angang` int(11) NOT NULL COMMENT '玩家暗杠次数',
  `u_3_minggang` int(11) NOT NULL COMMENT '玩家明杠次数',
  `u_3_goushouggang` int(11) NOT NULL COMMENT '玩家过手杠次数',
  `u_4_id` int(11) NOT NULL COMMENT '玩家ID',
  `u_4_score` int(11) NOT NULL COMMENT '玩家本局得分',
  `u_4_total` int(11) NOT NULL COMMENT '玩家当前总分',
  `u_4_angang` int(11) NOT NULL COMMENT '玩家暗杠次数',
  `u_4_minggang` int(11) NOT NULL COMMENT '玩家明杠次数',
  `u_4_goushouggang` int(11) NOT NULL COMMENT '玩家过手杠次数',
  `hupaitiles` blob COMMENT '鬼牌胡牌',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='日志表';

-- 数据导出被取消选择。
-- 导出  表 hmx_log.tb_moneylog 结构
CREATE TABLE IF NOT EXISTS `tb_moneylog` (
  `log_id` bigint(20) NOT NULL,
  `money_type` int(11) NOT NULL,
  `money_num` int(11) NOT NULL,
  `log_type` int(11) NOT NULL,
  `char_id` bigint(20) NOT NULL,
  `nickname` varchar(32) NOT NULL,
  `log_time` bigint(20) NOT NULL,
  `money_total` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`log_id`),
  KEY `char_id` (`char_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_log.tb_online_record 结构
CREATE TABLE IF NOT EXISTS `tb_online_record` (
  `time` bigint(20) NOT NULL COMMENT '记录的时间（时间戳）',
  `online_num` int(11) NOT NULL COMMENT '在线人数',
  `inroom_num` int(11) NOT NULL COMMENT '在房间人数',
  PRIMARY KEY (`time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_log.tb_register 结构
CREATE TABLE IF NOT EXISTS `tb_register` (
  `uid` bigint(20) NOT NULL,
  `time` bigint(20) NOT NULL,
  `channel` int(11) DEFAULT NULL,
  PRIMARY KEY (`uid`),
  UNIQUE KEY `uid` (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_log.tb_roomcard 结构
CREATE TABLE IF NOT EXISTS `tb_roomcard` (
  `order_no` varchar(255) NOT NULL,
  `user_id` int(11) NOT NULL,
  `room_card` int(11) NOT NULL,
  `is_add` smallint(6) NOT NULL,
  `time` bigint(20) NOT NULL,
  `from_uid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
-- 导出  表 hmx_log.tb_share 结构
CREATE TABLE IF NOT EXISTS `tb_share` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` bigint(20) DEFAULT NULL,
  `time` bigint(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 数据导出被取消选择。
/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
