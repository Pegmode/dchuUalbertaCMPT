#code by dchu

from pymongo import MongoClient
import csv

CSVREVIEWPATH = "YVR_Airbnb_reviews.csv"
CSVLISTINGPATH = "YVR_Airbnb_listings_summary.csv"
MONGOADDRESS = 'mongodb://localhost:27012'#change port as needed

def buildRow(csvRow,keys):
    document = {}
    for i in range(len(keys)):
        if csvRow[i].isdecimal():
            document[keys[i]] = int(csvRow[i])
        else:
            document[keys[i]] = csvRow[i]
    return document

def csvDataToDicts(csvData):#returns list of dicts
    keys = csvData[0]
    collection = []
    for csvRow in csvData[1:]:
        collection.append(buildRow(csvRow,keys))
    return collection

def readCSV(path):
    csvData = []
    with open(path,'r') as f:
        reader = csv.reader(f)
        for row in reader:
            csvData.append(row)
    return csvData
     
def writeToMongo(collection,collectionName):
    client = MongoClient(MONGOADDRESS)
    db = client["A5db"]
    reviews_collection = db[collectionName]
    ret = reviews_collection.insert_many(collection)

def groupAllInDocument(listingDicts,reviewDicts):
    totalLen = (len(listingDicts)*len(reviewDicts))
    reviewDictLen = len(reviewDicts)
    i = 0
    for listing in listingDicts:
        currentCollection = []
        j = 1
        for review in reviewDicts:
            currentPos = i*reviewDictLen+j
            if review["listing_id"] == listing["id"]:
                currentCollection.append(review)
                print("{}/{}; {}%".format(currentPos,totalLen,(currentPos/totalLen*100)))#only print on used vals (wont  reach 100%)
            j +=1
        listing["reviews"] = currentCollection
        i += 1
    print("Grouping complete!")


def main():
    listingData = readCSV(CSVLISTINGPATH)
    reviewData = readCSV(CSVREVIEWPATH)
    listingDicts = csvDataToDicts(listingData)
    reviewDicts = csvDataToDicts(reviewData)
    groupAllInDocument(listingDicts,reviewDicts)
    writeToMongo(listingDicts,"listings")

main()