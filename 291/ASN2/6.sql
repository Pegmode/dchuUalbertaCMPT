--Question 6
.print Question 6 - dchu
select off.CITY
from  OFFICES as off
where off.TARGET > (
	select sum(s1.SALES)
	from SALESREPS as s1, OFFICES as off1
	where s1.REP_OFFICE = off1.OFFICE
);