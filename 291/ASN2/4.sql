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
