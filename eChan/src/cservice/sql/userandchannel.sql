USE clsk;

INSERT INTO SqlUser (username, password, email) 
VALUES ('clsk', 'UUwPqZv7afbb6e4033b50cf6988d003a963c4e11', 'alan.alvarez@us.army.mil');

INSERT INTO SqlChannel (name)
VALUES ('*');

INSERT INTO SqlChannel (name)
VALUES ('#coders');

INSERT INTO SqlChannelAccess (channel_id, username_id, level)
VALUES (1, 1, 1000);

INSERT INTO SqlChannelAccess (channel_id, username_id, level)
VALUES (2, 1, 500);

