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
