USE eChan;

CREATE TABLE SqlUser (
id INT NOT NULL AUTO_INCREMENT,
username CHAR(12) NOT NULL,
password CHAR(50) NOT NULL,
email CHAR(30) NOT NULL,
PRIMARY KEY(id), UNIQUE ID(id)
);