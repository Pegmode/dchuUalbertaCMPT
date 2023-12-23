# Task 7
# Curtis Kennedy
# I utilized the pymongo documentation available here: https://pymongo.readthedocs.io/en/stable/api/pymongo/collection.html

import pymongo
import random
import time

MONGOADDRESS = 'mongodb://localhost:27012'  # change port as needed
MONGODBNAME = "A5db"
MONGOCOLLECTION = "listings"

client = pymongo.MongoClient(MONGOADDRESS)
db = client[MONGODBNAME]
col = db[MONGOCOLLECTION]

start = time.time()

print("Creating avgRating")

for doc in col.find():
    col.update_one({"_id": doc["_id"]}, {"$set": {"avgRating": random.randint(1,10)}})

end = time.time()
print("Done in", end-start)
