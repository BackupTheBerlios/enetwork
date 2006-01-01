USE eChan;

CREATE TABLE SqlChannel (
id INT NOT NULL AUTO_INCREMENT,
name CHAR(50) NOT NULL,
description CHAR(120),
owner CHAR(12) NOT NULL,
homepage CHAR(70),
PRIMARY KEY(id), UNIQUE ID(id)
);
