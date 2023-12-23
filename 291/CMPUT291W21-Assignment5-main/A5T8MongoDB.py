#CMPUT291 Assignment 5 Task 8
#code by dchu
from pymongo import MongoClient
import sys,time

MONGOADDRESS = 'mongodb://localhost:27012'#change port as needed

#usage: python3 A5T8MongoDb.py <listing id>

#Used Query: find the most recent review comment, host name and price

#db.listings.aggregate([
#	{$unwind: "$reviews"},
#... {"$match": {"id":10080}},
#	{"$sort": {"reviews.date":-1}},
#... {"$project":{"host_name":1,"price":1,"comments":1}},
#	{"$limit":1}
#... ])

def connectToMongoListings():
    client = MongoClient(MONGOADDRESS)
    db = client["A5db"]
    if "listings" not in db.list_collection_names():
       sys.exit("listings collection was not found in the database")
    return db["listings"]

def getNewestReview(listingId,listingCollection):
    query = [{"$unwind": "$reviews"},{"$match": {"id":listingId}},{"$sort": {"id":-1}},{"$project":{"host_name":1,"price":1,"reviews.comments":1}},{"$limit":1}]
    startTime = time.time()
    results = list(listingCollection.aggregate(query))
    endTime = time.time()
    print("Done in", endTime-startTime)
    if len(results) == 0:
         sys.exit("The given listing with id {} does not exist in the database".format(listingId))
    return results[0]

def getListingId():
    listingId = input("Enter listing Id to search: ")#for testing use 10080 example
    if listingId == "":
        sys.exit("a listing Id must be given")
    if not listingId.isnumeric():
        sys.exit("given listing Id is not a number")
    return int(listingId)


def printReviewInfo(review,listingId):
    reviewComment = review["reviews"]["comments"]
    reviewPrice = review["price"]
    reviewHostName = review["host_name"]
    print("Newest review for listing with id: {}\nHost Name: {}\nPrice: {}\nComment: {}".format(listingId,reviewHostName,reviewPrice,reviewComment))

def main():
    listingId = getListingId()
    listingCollection = connectToMongoListings()
    newestReview = getNewestReview(listingId,listingCollection)
    printReviewInfo(newestReview,listingId)

main()