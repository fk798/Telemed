DROP DATABASE IF EXISTS pulseScan;

CREATE DATABASE pulseScan;

USE pulseScan;

CREATE TABLE users (
	ID INT NOT NULL AUTO_INCREMENT,
	name VARCHAR(255) NOT NULL,
    fileName INT NOT NULL,
    PRIMARY KEY (ID)
);

use pulseScan;

select * from users;