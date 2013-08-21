drop database if exists `MobileDream_XXAL`;
create database `MobileDream_XXAL` character set utf8 collate utf8_general_ci;
use `MobileDream_XXAL`;
/*create a table for save account info*/
create table `xxal_account` (
    `account` varchar(50) not NULL,
    `id` INT unsigned not NULL AUTO_INCREMENT,
    `passwd` varchar(50) not NULL,
    `mobile` varchar(50) NULL,
    `email` varchar(50) NULL,
    primary key (`account`),
    unique index `mobile` (`mobile`),
    unique index `email` (`email`),
    unique index `id` (`id`),
    index `account` (`account`)
)

comment='create a table for save account info'
collate='utf8_general_ci'
engine=InnoDB
row_formwi=default
