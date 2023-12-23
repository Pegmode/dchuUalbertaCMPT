.print Question 3 - dchu
--find the id and title of questions that are not answered within three days after their postings. 
SELECT q.pid, pq.title
FROM questions q, posts pq
WHERE q.pid = pq.pid
    EXCEPT
    SELECT q.pid, pq.title
    FROM questions q, posts pq, answers a, posts pa
    WHERE a.qid = q.pid AND date(pa.pdate "+3 days") >= pq.pdate AND q.qid = pq.qid
;

