USE eChan;

CREATE TABLE SqlChannel (
id INT NOT NULL AUTO_INCREMENT,
name CHAR(30) NOT NULL,
description CHAR(120),
owner CHAR(12) NOT NULL,
homepage CHAR(50),
PRIMARY KEY(id), UNIQUE ID(id)
);
