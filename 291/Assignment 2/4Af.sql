.print Question 4 - dchu

SELECT u.uid
FROM users u, answers a, posts pa, questions q, posts pq
WHERE pq.pid = q.pid AND pa.pid = a.pid AND q.pid = a.qid AND pa.poster = pq.poster
GROUP BY pq.poster
HAVING count(distinct pq.pid) > 2;