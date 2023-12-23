.print Question 2 - dchu
--Find the id and title of questions that have the text "relational database" either in title or both terms "relational" and "database" appear in tags
SELECT posts.pid,posts.title FROM posts
WHERE pid IN
(
    (SELECT pid FROM tags
    WHERE lower(tag) =  'database'
    INTERSECT
    SELECT pid FROM tags
    WHERE lower(tag) = 'relational')
)
OR lower(posts.title) LIKE '%relational database%'
AND pid IN (--is question
    SELECT pid FROM questions
)

;
