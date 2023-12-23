import sqlite3
import time

T4_QUERY =   """SELECT YVR_Airbnb_listings_summary.id FROM YVR_Airbnb_listings_summary
LEFT OUTER JOIN YVR_Airbnb_reviews ON YVR_Airbnb_listings_summary.id = YVR_Airbnb_reviews.listing_id
WHERE reviewer_id is NULL
ORDER BY listing_id
LIMIT 10;"""     



conn = sqlite3.connect("./a5.db")
c = conn.cursor()
start = 0
end = 0
start += time.time()

c.execute(T4_QUERY)
end += time.time()
calc = end-start
print("Task 4 sql query runtime is: ",calc,"ms")
x = c.fetchall()
print("The id's are: ")
for i in x:
    print(i[0])
