from pymongo import MongoClient
import sys
import time

MONGOADDRESS = 'mongodb://localhost:27012'

client = MongoClient(MONGOADDRESS)

db = client["A5db"]

db_collection = db["listings"]

start = 0
end = 0

start += time.time()

id_list = list(db_collection.aggregate([\
   {"$match": { "reviews": {"$size": 0}}},
    {"$sort":{"id":1}},
    {"$project":{"id":1}},
    {"$limit":10}
    ]))
end += time.time()
print("The runtime for task 5 mongodb is:" ,end-start,"ms")

print("The Id's are: ")
for i in id_list:
    print(i["id"])


