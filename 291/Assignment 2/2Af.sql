.print Question 2 - dchu
--Find the id and title of questions that have the text "relational database" either in title or both terms "relational" and "database" appear in tags
SELECT p.pid,p.title FROM posts p, questions q, tags t1,tags t2
WHERE p.title LIKE '%relation database%' OR ( t1.tag = 'relational' AND t2.tag = 'database' )
;
