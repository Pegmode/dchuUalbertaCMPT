# Creates an SQLITE db for Assignment 5
# Curtis Kennedy
import csv
import sqlite3
import time

# Configuration
dbToCreate = 'A5.db'
listingsCsv = 'YVR_Airbnb_listings_summary.csv'
reviewsCsv = 'YVR_Airbnb_reviews.csv'

start = time.time()

# DB Population Prep
print("Reading listings csv")
listings = []
with open(listingsCsv, 'r') as f:
    reader = csv.reader(f)
    next(reader)
    for row in reader:
        listings.append(tuple(row))

print("Reading reviews csv")
reviews = []
with open(reviewsCsv, 'r') as f:
    reader = csv.reader(f)
    next(reader)
    for row in reader:
        reviews.append(tuple(row))


# Create Database
print("Creating db")
con = sqlite3.connect(dbToCreate)
cur = con.cursor()


# Drop existing tables
print("Dropping tables if already exist")
cur.execute("DROP TABLE IF EXISTS Listings")
cur.execute("DROP TABLE IF EXISTS Reviews")
con.commit()


# Create tables
print("Create tables")
cur.execute('''CREATE TABLE Listings (id INTEGER PRIMARY KEY, name TEXT, host_id INTEGER, host_name TEXT, neighbourhood TEXT, room_type TEXT, price INTEGER,
            minimum_nights INTEGER, availability_365 INTEGER)''')
cur.execute('''CREATE TABLE Reviews (listing_id INTEGER, id INTEGER PRIMARY KEY, date TEXT, reviewer_id INTEGER, reviewer_name TEXT, comments TEXT) ''')
con.commit()


# Fill in tables
print("Filling in tables")
cur.executemany('INSERT INTO Listings (id, name, host_id, host_name, neighbourhood, room_type, price, minimum_nights, availability_365) '
                'VALUES(?,?,?,?,?,?,?,?,?)', listings)
con.commit()
cur.executemany('INSERT INTO Reviews (listing_id, id, date, reviewer_id, reviewer_name, comments) '
                'VALUES(?,?,?,?,?,?)', reviews)
con.commit()

end = time.time()
print("Done in", end-start)
con.close()
