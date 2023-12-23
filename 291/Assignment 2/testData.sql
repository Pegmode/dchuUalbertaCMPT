-- Data prepapred by Davood Rafiei, drafiei@ualberta.ca
-- Published on Sept 27, 2020

-- Let's insert some tuples to our tables. This is just an initial set and 
-- we definitly need more data for testing our queries.

PRAGMA foreign_keys = ON;

insert into users values ('u100','Davood Rafiei','Edmonton','2020-01-10');
insert into users values ('u200','Joe Smith','Vancouver','2020-08-15');
insert into users values ('u300','Mary Brown','Edmonton','2020-06-04');

insert into badges values ('socratic question','gold');
insert into badges values ('stellar question', 'gold');
insert into badges values ('great answer','gold');
insert into badges values ('popular answer','gold');
insert into badges values ('fanatic user','gold');
insert into badges values ('legendary user','gold');
insert into badges values ('good question','silver');
insert into badges values ('good answer','silver');
insert into badges values ('enthusiast user','silver');
insert into badges values ('nice question','bronze');
insert into badges values ('nice answer','bronze');
insert into badges values ('commentator user','bronze');

insert into ubadges values ('u200','2020-09-06','stellar question');

insert into posts values ('p100',date('now','-30 days'),'What is a relational database?','What is the term referred to and what are the benefits?','u200');
insert into posts values ('p200',date('now','-29 days'),'introduction to relational databases','This is a post that introduce the relational databases including SQL','u100');

insert into tags values ('p100','relational');
insert into tags values ('p100','database');
insert into tags values ('p200','relational');
insert into tags values ('p200','sql');

insert into votes values ('p200',1,date('now','-20 days'),'u200');

insert into questions values ('p100',null);
insert into answers values ('p200','p100');
