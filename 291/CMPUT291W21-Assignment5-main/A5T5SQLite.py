import sqlite3
import time

T5_QUERY =   """SELECT avg(price) FROM YVR_Airbnb_listings_summary
WHERE neighbourhood = ?;
"""     

print("Enter a neighborhood to search: ")
neighborhood = input('Neighborhood: ')

conn = sqlite3.connect("./a5.db")
c = conn.cursor()
start = 0
end = 0
start += time.time()
c.execute(T5_QUERY,(neighborhood,))
end += time.time()
calc = end-start
print("Task 5 sql query runtime is:",calc,"ms")
x = c.fetchall()
print("The average price for the neighborhood is:",x[0][0])