--Question 7
.print Question 7 - dchu
select p.DESCRIPTION,sum(o.QTY)
from PRODUCTS as p, ORDERS as o 
where o.PRODUCT = p.PRODUCT_ID
group by p.PRODUCT_ID
order by sum(o.qty) desc;
