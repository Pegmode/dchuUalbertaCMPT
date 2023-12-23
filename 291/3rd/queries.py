#contains all sqlite3 queries for options 1-4
#values are constant but contain "qmark style placeholders" for varible data

#Query for option 1: Find accepted Papers
#
Q_QUERY1 = '''
select p.title
from papers as p, areas as a
where p.area = a.name
and a.name = ?;
'''

#Query for option 2: find papers reviewed by user email
Q_QUERY2 = '''
select p.title
from papers as p, users as u, reviews as r
where u.email = r.reviewer
and r.paper = p.id
and r.reviewer = ?
group by p.id;
'''

#Query for option 3: find papers who has reviews that are "inconsistent"
Q_QUERY3 = '''
select p.id,p.title
from papers as p,(
    select r1.paper
    from reviews as r1
    left outer join (
        select r.paper,AVG(r.overall) as average
        from reviews as r
        group by r.paper
) as a on a.paper = r1.paper--a alias = averages
where abs(100*(r1.overall - a.average)/a.average) > ?
group by r1.paper) as r2
where r2.paper = p.id
'''

#Query for option 4
Q_QUERY4 = '''
select r1.reviewer, u1.name
from DiffScore as d1, reviews as r1, papers as p1, users as u1
where d1.pid = p1.id
and u1.email = r1.reviewer
and r1.paper = p1.id
and d1.difference >= ?
and d1.difference <= ?;
'''

#Query for creating view for option for during startup
Q_CREATE_VIEW = '''
--create view DiffScore
create view [DiffScore] as
select p1.id as pid, p1.title as ptitle, abs(ao.areaAverage - a.average) as difference
from papers as p1, (--find average review of this paper
	select r2.paper,AVG(r2.overall) as average
	from reviews as r2
	group by r2.paper
) as a on a.paper = p1.id,(-- find average of paper area
	select avg(r3.overall) as areaAverage,p3.area
	from papers as p3, reviews as r3 
	where p3.id = r3.paper
	group by p3.area
) as ao on ao.area = p1.area
'''