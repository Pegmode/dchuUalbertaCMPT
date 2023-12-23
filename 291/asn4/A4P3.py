#CMPUT291W21 Assignment 4 part3 
#code by dchu
import sqlite3,datetime,pdb

#Querries
#==============================================================================
Q4_QUERY = '''
SELECT p1.partNumber,MAX(p1.partPrice)
FROM Parts as p1,(
	select p2.madeIn
	from Parts as p2
	order by random() limit 1
) as p3
where p1.madeIn = p3.madeIn;
'''

CREATE_INDEX_QUERY = '''
CREATE INDEX idxMaxCostProv 
ON "Parts" (
	"madeIn",
	"partPrice"
);
'''

REMOVE_INDEX_QUERY = '''
DROP INDEX IF EXISTS idxNeedsPart;
DROP INDEX IF EXISTS idxMadeIn;
DROP INDEX IF EXISTS idxMaxCostProv;
'''
#Code
#==============================================================================

NP_PATHS = ["A4v100.db", "A4v1k.db", "A4v10k.db", "A4v100k.db", "A4v1M.db"]

def init():
    for dbPath in NP_PATHS:#drop index
        db = sqlite3.connect(dbPath)
        cur = db.cursor()
        cur.execute(REMOVE_INDEX_QUERY)
        db.close()

def task9():#run query 100 times and record time
    #how do they want query time recorded?
    for dbPath in NP_PATHS:
        sumTime = 0
        db = sqlite3.connect(dbPath)
        cur = db.cursor()
        for i in range(100):
            startTime = datetime.datetime.now()
            cur.execute(Q4_QUERY)
            endTime = datetime.datetime.now()
            result = cur.fetchall()
            sumTime += ((endTime-startTime).microseconds)*0.001#convert to ms
        db.close()
        #calculate av
        average = sumTime / 100
        print("Average of 100 queries on {} was {}ms".format(dbPath,average))
    print()

def task10():#create index
    for dbPath in NP_PATHS:
        db = sqlite3.connect(dbPath)
        cur = db.cursor()
        cur.execute(CREATE_INDEX_QUERY)
        db.close()

def task11():#rereun Q4 with index
    #how do they want query time recorded?
    for dbPath in NP_PATHS:
        sumTime = 0
        db = sqlite3.connect(dbPath)
        cur = db.cursor()
        for i in range(100):
            startTime = datetime.datetime.now()
            cur.execute(Q4_QUERY)
            endTime = datetime.datetime.now()
            result = cur.fetchall()
            sumTime += ((endTime-startTime).microseconds)*0.001#convert to ms
        db.close()
        #calculate av
        average = sumTime / 100
        print("Average of 100 queries on {} was {}ms with index".format(dbPath,average))

def question4():
    init()
    task9()
    task10()
    task11()
question4()

