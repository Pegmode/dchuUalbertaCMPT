import csv,pdb,random,sqlite3,os
UPC_CSV_PATH = "upc_corpus.csv"
COUNTRYCODE_CSV_PATH = "countryCodes.csv"

INSERTION_QUERY = '''
INSERT INTO Parts(partNumber,partPrice,needsPart,madeIn)
VALUES(?,?,?,?);
'''

CREATION_QUERY = '''
CREATE TABLE Parts (
partNumber INTEGER, -- a UPC code 
partPrice INTEGER, -- in the [1, 100] range
needsPart INTEGER, -- a UPC code
madeIn TEXT, -- a country (2 letters) code 
PRIMARY KEY(partNumber)
);'''


db = sqlite3.connect("A4v1k.db")
cur = db.cursor()
cur.execute(".timerOn")
db.commit("select * from Parts")
result = cur.fetchall()
print(result)
db.close()

npPaths = ["A4v100.db", "A4v1k.db", "A4v10k.db", "A4v100k.db", "A4v1M.db"]
