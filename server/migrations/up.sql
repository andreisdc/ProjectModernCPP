PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS users
(
	id       integer primary key autoincrement,
	username text not null,
	password text not null
);

CREATE TABLE IF NOT EXISTS user_matches
(
	id        integer primary key autoincrement,
	player_id integer not null,
	score     integer not null,
	FOREIGN KEY (player_id) REFERENCES users (id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS past_matches
(
	id      integer primary key autoincrement,
	player1 integer,
	player2 integer,
	player3 integer,
	player4 integer,
	FOREIGN KEY (player1) REFERENCES user_matches (id) ON DELETE CASCADE,
	FOREIGN KEY (player2) REFERENCES user_matches (id) ON DELETE CASCADE,
	FOREIGN KEY (player3) REFERENCES user_matches (id) ON DELETE CASCADE,
	FOREIGN KEY (player4) REFERENCES user_matches (id) ON DELETE CASCADE
);
