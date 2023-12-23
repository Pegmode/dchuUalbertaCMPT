
import sqlite3
import time
import random
l = [1,2,3,4,5,6,7,8,9,10]
conn = sqlite3.connect("./a5.db")

c = conn.cursor()




add = """ALTER TABLE YVR_Airbnb_reviews ADD COLUMN avgRating INTEGER"""
conn.commit()

c.execute(add)
start = 0
end = 0
start += time.time()
for i in range(1,147937):
    data = random.choice(l)
    c.execute("UPDATE {} SET avgRating = ? WHERE ROWID = ?".format('YVR_Airbnb_reviews'),(data, i))
    conn.commit()

end += time.time()

calc = end-start

print("The task runtime is:",calc,"ms")