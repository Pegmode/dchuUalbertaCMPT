--Q1:
.print Q1:
SELECT AVG(t.goals)
FROM Teams t,Leagues l
WHERE t.lID = l.lID AND l.name = 'La Liga';

--Q2
.print Q2:
SELECT l.name,COUNT(DISTINCT p.pID)
FROM Leagues l,  Players p ,Teams t
WHERE p.type = 'defender' AND p.tID = t.tID AND t.lID = l.lID
GROUP BY l.lID;


--Q3
.print Q3:
SELECT p.tID,p.name,p.type
FROM Players p
WHERE p.name LIKE '%d';
