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