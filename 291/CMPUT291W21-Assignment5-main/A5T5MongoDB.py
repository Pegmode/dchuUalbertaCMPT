#CMPUT291 Assignment 5 Task 5
#code by dchu
from pymongo import MongoClient
import sys,time

MONGOADDRESS = 'mongodb://localhost:27012'#change port as needed

def connectToMongoListings():
    client = MongoClient(MONGOADDRESS)
    db = client["A5db"]
    if "listings" not in db.list_collection_names():
       sys.exit("listings collection was not found in the database")
    return db["listings"]

def runQuery(listingsCollection,neighbourhood):
    startTime = time.time()
    results = list(listingsCollection.aggregate([\
    {"$match": {"neighbourhood":neighbourhood}},\
    {"$group": {"_id":"$neighbourhood", "avg": {"$avg":"$price"}}}\
    ]))
    endTime = time.time()
    print("Done in", endTime-startTime)
    if len(results) == 0:
        sys.exit("No listing with given neighbourhood found")
    print("Average price for listings in {}: {}$".format(neighbourhood,results[0]["avg"]))
    
def getNeighbourhood():
    neighbourhood = input("Input listing neighbourhood: ")
    if neighbourhood == "":
        sys.exit("you must enter a value for neighbourhood")
    return neighbourhood

def main():
    listingsCollection = connectToMongoListings()
    neighbourhood = getNeighbourhood()
    runQuery(listingsCollection,neighbourhood)

main()