USE eChan;

CREATE TABLE SqlChannelAccess (
id INT NOT NULL AUTO_INCREMENT,
username_id INT NOT NULL,
channel_id INT NOT NULL,
level INT NOT NULL,
PRIMARY KEY(id), UNIQUE ID(id));
