.print Question 3 - dchu
--find the id and title of questions that are not answered within three days after their postings. 
SELECT posts.id,posts.title  FROM posts
WHERE (
    SELECT JuilanDay(pdate) - JuilanDay() FROM posts

) 
;

--test
--SELECT posts.pid,posts.title FROM posts
--WHERE (JuilanDay(pdate) - (
--    SELECT 
--) )
--;