DROP TABLE IF EXISTS Leagues;
DROP TABLE IF EXISTS Teams;
DROP TABLE IF EXISTS Players;

PRAGMA foreign_keys = ON;

CREATE TABLE Leagues (
  lID	INTEGER,
  name	TEXT,
  numberOfTeams  INTEGER,
  foundYear	INTEGER,
  PRIMARY KEY (lID)
);

CREATE TABLE Teams (
  tID     INTEGER,
  lost     INTEGER,
  won     INTEGER,
  goals INTEGER,
  lID      INTEGER,
  PRIMARY KEY (tID),
  FOREIGN KEY (lID) REFERENCES Leagues
);

CREATE TABLE Players (
  pID    INTEGER,
  name     TEXT,
  yearOfJoin INTEGER,
  tID     INTEGER,
  type TEXT,
  PRIMARY KEY (pID),
  FOREIGN KEY (tID) REFERENCES Teams
);

-- Leagues 
INSERT INTO Leagues VALUES (0, 'La Liga', 10, 1880);
INSERT INTO Leagues VALUES (1, 'Premier', 6, 1785);
INSERT INTO Leagues VALUES (2, 'Series a', 8, 1875);

-- Teams
INSERT INTO Teams VALUES (0, 3, 5, 12, 0);
INSERT INTO Teams VALUES (1, 1, 7, 17, 0);
INSERT INTO Teams VALUES (2, 0, 8, 20, 0);
INSERT INTO Teams VALUES (3, 4, 3, 6, 0);
INSERT INTO Teams VALUES (4, 4, 4, 11, 0);
INSERT INTO Teams VALUES (5, 6, 2, 4, 0);
INSERT INTO Teams VALUES (6, 5, 3, 8, 0);
INSERT INTO Teams VALUES (7, 4, 4, 9, 0);
INSERT INTO Teams VALUES (8, 1, 7, 7, 0);
INSERT INTO Teams VALUES (9, 8, 0, 0, 0);

INSERT INTO Teams VALUES (10, 2, 3, 4, 1);
INSERT INTO Teams VALUES (11, 1, 4, 5, 1);
INSERT INTO Teams VALUES (12, 0, 5, 12, 1);
INSERT INTO Teams VALUES (13, 1, 1, 3, 1);
INSERT INTO Teams VALUES (14, 1, 2, 2, 1);
INSERT INTO Teams VALUES (15, 2, 1, 1, 1);

INSERT INTO Teams VALUES (16, 3, 4, 4, 2);
INSERT INTO Teams VALUES (17, 4, 3, 7, 2);
INSERT INTO Teams VALUES (18, 1, 6, 10, 2);
INSERT INTO Teams VALUES (19, 6, 1, 0, 2);
INSERT INTO Teams VALUES (20, 2, 5, 5, 2);
INSERT INTO Teams VALUES (21, 5, 2, 4, 2);
INSERT INTO Teams VALUES (22, 7, 0, 1, 2);
INSERT INTO Teams VALUES (23, 0, 7, 15, 2);

-- Players
INSERT INTO Players VALUES (0, 'McDavid', 2004, 0, "defender");
INSERT INTO Players VALUES (1, 'Neal', 2002, 1, "defender");
INSERT INTO Players VALUES (2, 'Bear', 2000, 3, "defender");
INSERT INTO Players VALUES (3, 'Smith', 2000, 4, "attacker");
INSERT INTO Players VALUES (4, 'Hopkins', 2001, 7, "attacker");
INSERT INTO Players VALUES (5, 'Kassian', 1998, 9, "attacker");

INSERT INTO Players VALUES (6, 'Yamamto', 2003, 10, "attacker");
INSERT INTO Players VALUES (7, 'Bouchard', 2001, 11, "middle");
INSERT INTO Players VALUES (8, 'Graunlund', 1996, 12, "middle");
INSERT INTO Players VALUES (9, 'Haas', 1999, 13, "defender");
INSERT INTO Players VALUES (10, 'Sheahan', 2000, 14, "defender");
INSERT INTO Players VALUES (11, 'Koshinen', 2004, 15, "middle");

INSERT INTO Players VALUES (12, 'Persson', 2000, 16, "defender");
INSERT INTO Players VALUES (13, 'Khaira', 2003, 18, "defender");
INSERT INTO Players VALUES (14, 'Archibald', 1995, 20, "middle");
INSERT INTO Players VALUES (15, 'Chiasson', 2005, 21, "middle");
INSERT INTO Players VALUES (16, 'Russel', 2002, 23, "attacker");
