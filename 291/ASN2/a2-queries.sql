.echo on
--Question 1
.print Question 1 - dchu
select OFFICE 
from OFFICES
where OFFICES.SALES > OFFICES.TARGET and REGION = "Eastern"
ORDER BY OFFICES.CITY;

--Question 2
.print Question 2 - dchu
SELECT *
FROM (SELECT s.NAME,count(*)
FROM SALESREPS as s, ORDERS as o
WHERE s.EMP_ID = o.REP
GROUP by s.EMP_ID)

UNION ALL

SELECT *
FROM (SELECT s.NAME,NULL
FROM SALESREPS as s
WHERE s.EMP_ID NOT IN (SELECT REP FROM ORDERS)
GROUP by s.EMP_ID);

--Question 3
.print Question 3 - dchu
select p.PRODUCT_ID,p.DESCRIPTION
from PRODUCTS as p, ORDERS as o
where p.PRODUCT_ID = o.PRODUCT 
and p.PRICE > 2000
and 3 > (
	select count(*)
	from PRODUCTS  as p1, ORDERS as o1
	where p1.PRODUCT_ID = o1.PRODUCT
	group by p1.PRODUCT_ID
);

--Question 4
.print Question 4 - dchu
select p.DESCRIPTION,p.PRICE,p.QTY_ON_HAND,sum(o.QTY)
from PRODUCTS as p, ORDERS as o
where p.PRODUCT_ID = o.PRODUCT
and ((
	select sum(o1.QTY)
	from PRODUCTS as p1, ORDERS as o1
	where p1.PRODUCT_ID = o1.PRODUCT
	group by p1.PRODUCT_ID
)
/p.QTY_ON_HAND) > 1.75--1.75 for more than, 0.75 for 75% of stock
group by p.PRODUCT_ID;

--Question 5
.print Question 5 - dchu

select s.NAME
from SALESREPS as s, OFFICES as off
where off.OFFICE = s.REP_OFFICE
and(off.CITY = "Edmonton"
	or (off.CITY = "Calgary"
		and not exists (
			select s1.NAME
			from SALESREPS as s1,SALESREPS as s2, OFFICES as off1
			where s1.MANAGER = s2.EMP_ID and s2.REP_OFFICE = off1.OFFICE
			and (off1.CITY = "Edmonton" or off1.CITY = "Calgary")
			)
	)
);

--Question 6
.print Question 6 - dchu
select off.CITY
from  OFFICES as off
where off.TARGET > (
	select sum(s1.SALES)
	from SALESREPS as s1, OFFICES as off1
	where s1.REP_OFFICE = off1.OFFICE
);

--Question 7
.print Question 7 - dchu
select p.DESCRIPTION,sum(o.QTY)
from PRODUCTS as p, ORDERS as o 
where o.PRODUCT = p.PRODUCT_ID
group by p.PRODUCT_ID
order by sum(o.qty) desc;
