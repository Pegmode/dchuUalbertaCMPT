import sqlite3
import time

T8_QUERY =   """SELECT host_name,price,comments FROM YVR_Airbnb_reviews
JOIN YVR_Airbnb_listings_summary ON YVR_Airbnb_reviews.listing_id = YVR_Airbnb_listings_summary.id
WHERE listing_id = ?
ORDER BY date DESC
limit 1;
"""     

print("Enter a listing id to search: ")
listing = input('listing id: ')

conn = sqlite3.connect("./a5.db")
c = conn.cursor()
start = 0
end = 0
start += time.time()
c.execute(T8_QUERY,(listing,))
end += time.time()
calc = end-start
print("Task 8 sql query runtime is:",calc,"ms")
x = c.fetchall()
print("The host name, price, and most recent comment for the listing is:")
for i in x:
    print(i)