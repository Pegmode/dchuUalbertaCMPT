--Question 1
.print Question 1 - dchu
select OFFICE 
from OFFICES
where OFFICES.SALES > OFFICES.TARGET and REGION = "Eastern"
ORDER BY OFFICES.CITY;