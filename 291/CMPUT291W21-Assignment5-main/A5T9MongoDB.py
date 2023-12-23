#CMPUT291 Assignment 5 Task 9
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

def getKeywords():
    rawInput = input("Type keywords separated by commas: ")
    if " " in rawInput:#cases found in test data, don't want to lose marks over weird formatting
        rawInput.replace(" ","")
        rawInput.replace(","," ")
    else:
        rawInput.replace(",","")
    return rawInput#keep as is so we don't need to do wrangling in the query

def createCommentsIndex(listingsCollection):
    listingsCollection.create_index([("reviews.comments", "text")])

def getTopListings(keywords,listingsCollection):
    startTime = time.time()
    results = list(listingsCollection.aggregate([\
	{"$match": {"$text": {"$search":keywords}}},\
	{"$sort": {"score": {"$meta": "textScore"}}},\
	{"$project":{"id":1,"score": { "$meta": "textScore" }}},\
	{"$limit":3}\
	]))
    endTime = time.time()
    print("Done in", endTime-startTime)
    if len(results) == 0:
        sys.exit("No listings found containning given keywords")
    print('Top 3 listings containing keywords "{}"'.format(keywords))
    for i in range(len(results)):
        print("{}. id = {}".format(i+1,results[i]["id"]))

        
def main():
    keywords = getKeywords()
    listingsCollection = connectToMongoListings()
    createCommentsIndex(listingsCollection)
    getTopListings(keywords,listingsCollection)

main()