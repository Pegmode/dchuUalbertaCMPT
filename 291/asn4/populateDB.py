import csv,pdb,random,sqlite3,os,sys
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

def checkForFiles(pathNames):
    for path in pathNames:
        if os.path.exists(path):
            os.remove(path)

def loadCSV(path):
    csvData = []
    with open(path, 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            if 'null' not in row and '' not in row:
                csvData.append(row)
    csvDict = {}      
    finalOutput = []
    for row in csvData[1:]:
        csvDict[row[0]] = row[1]
    for k,v in csvDict.items():
        internal = []
        internal.append(k)
        internal.append(v)
        finalOutput.append(internal)
    return finalOutput

def populateDB(upcData,countryCodes,dbPath,np):
    random.shuffle(countryCodes)
    random.shuffle(upcData)
    db = sqlite3.connect(dbPath)
    cur = db.cursor()
    for i in range(np):
        try:
            partNumber = int(upcData[i][0])
            partPrice = random.randrange(1,100)
            #needsPart = random.choice(upcData[0:np])[0]
            needsPart = int(random.choice(upcData)[0])
            madeIn = random.choice(countryCodes)[1]
            dbArg = (partNumber,partPrice,needsPart,madeIn)
            try:
                cur.execute(INSERTION_QUERY,dbArg)
            except:
                print(sys.exc_info())
                pdb.set_trace()
        except:
            pass
    db.commit()
    db.close()  

def createDB(path):
    db = sqlite3.connect(path)
    cur = db.cursor()
    cur.execute(CREATION_QUERY)
    db.commit()
    db.close()
    
def generateAllTables():
    npPaths = ["A4v100.db", "A4v1k.db", "A4v10k.db", "A4v100k.db", "A4v1M.db"]
    npVals = [100,1000,10000,100000,1000000]
    checkForFiles(npPaths)
    upcData = loadCSV(UPC_CSV_PATH)
    countryCodes = loadCSV(COUNTRYCODE_CSV_PATH)
    for i in range(len(npVals)):
        createDB(npPaths[i])
        populateDB(upcData,countryCodes,npPaths[i],npVals[i])

#loadCSV(UPC_CSV_PATH)
generateAllTables()
#pdb.set_trace()