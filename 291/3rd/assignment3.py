#CMPUT291 W21 Assignment 3 dchu (1493374)
import sys,sqlite3

#constants
from queries import *#contains all sql queries as multi-line strings in separate file for readability
DATABASE_FILEPATH = "A3.db"#filebase to assignment 3 database

S_MAIN_PROMPT = '''\
Please select an option by entering a number:
1. Find accepted papers
2. Find papers assigned for review
3. Find papers with inconsistent reviews
4. Find papers according to difference score
5. Exit\
'''#main screen prompt

def connectToDB():#get sqlite3 cursor
    con = sqlite3.connect(DATABASE_FILEPATH)
    return con.cursor()

def printQueryResult(results):#takes in single touple result from sql query and prints it line by line
    for result in results:
        for entry in result:#print everything in returned, space separated
            print("{} ".format(entry), end='')
        print()#print newline

def checkAndPrintQuery(results,acceptedMsg,failMsg):#checks if query return has content and prints based on if there is content
    if len(results) < 1:
        print(failMsg)
    else:
        print(acceptedMsg)
        printQueryResult(results)


def option1():#Find accepted Papers
    cursor = connectToDB()
    print("Enter an area to list the titles of accepted papers in the given area in descending order of their overall review score.")
    option = input("Area: ")
    cursor.execute(Q_QUERY1,(option,))#run query
    titles = cursor.fetchall()#get query result
    successMsg = "Accepted papers in this area: "
    failMsg = "No papers found in this area"
    checkAndPrintQuery(titles,successMsg,failMsg)#print results based on content


def option2():#find papers reviewed by user email
    cursor = connectToDB()
    print("Enter a user's email to list the titles of papers that they were assigned to review.")
    option = input("Email: ")
    cursor.execute(Q_QUERY2,(option,))#run query
    titles = cursor.fetchall()#get query result
    successMsg = "Papers assigned to this user: "
    failMsg = "There are no papers assigned to this user"
    checkAndPrintQuery(titles,successMsg,failMsg)#print results based on content
    
def option3():#find papers who has reviews that are "inconsistent"
    cursor = connectToDB()
    print("Enter a percentage (X%) for which to find inconsistent papers.")
    try:
        option = int(input("X: "))
    except:
        print("Incorrect formatting try again")
        return
    cursor.execute(Q_QUERY3,(option,))#run query
    titles = cursor.fetchall()#get query result
    successMsg = "Searching for papers with overall scores that differ by more than {}% from their average overall score: ".format(option)
    failMsg = "No inconsistent papers found that differ by more than {}%".format(option)
    checkAndPrintQuery(titles,successMsg,failMsg)#print results based on content

def option4():
    cursor = connectToDB()
    print("Enter a range from X to Y.")
    try:
        option1 = float(input("X: "))
    except:
        print("Incorrect formatting try again")
        return     
    try:   
        option2 = float(input("Y: "))
    except:
        print("Incorrect formatting try again")
        return  
    print("Seareching for reviewers that have reviewed a paper with a difference score between {} and {}".format(option1,option2))
    cursor.execute(Q_QUERY4,(option1,option2))#run query
    titles = cursor.fetchall()#get query result
    successMsg = "The following users were found: "
    failMsg = "There are no papers that match this request"
    checkAndPrintQuery(titles,successMsg,failMsg)#print results based on content

def exitP():
    sys.exit()

command_dict = { #dictionary for selection option functions
    "1":option1,
    "2":option2,
    "3":option3,
    "4":option4,
    "5":exitP,
    "exit":exitP#extra exit command
}

def mainScreen(): #main prompts and mainscreen input logic
    print(S_MAIN_PROMPT)
    option = input("Option: ").lower()
    if option in command_dict:
        command_dict[option]()
    else:
        print("Incorret option, please re-enter")    

def init():
    #create DiffScore View
    cursor = connectToDB()
    cursor.execute("DROP VIEW IF EXISTS DiffScore;")#drop view for case where view already exists
    cursor.execute(Q_CREATE_VIEW)#run query
    pass

def main():#Mainloop
    init()
    while True:
        print("\n")
        mainScreen()

main()#run main() C styled