#Rainfall text formating lab
#Daniel Chu 1493374 CMPUT 175
#lambda idea given by TA Mennatullah Siam

import os

f = open('rainfall.txt','r')
fileSize= os.stat('rainfall.txt').st_size
currentFilePos = f.tell()

categories = ([51,60], [61,70], [71,80], [81,90], [91,100]) #ranges given by the lab 

rainfallList = []
rainfallListTemp = []
orderedRainfallList = []
                    
for i in range(len(categories)):#Create empty final list
    orderedRainfallList.append([])


while f.tell() < fileSize: #populate list containing each location and rainfall ammount
    rainfallListTemp.append(f.readline())
    rainfallListTemp[-1] = rainfallListTemp[-1].replace('\n','')#trim newline
f.close()

for entry in rainfallListTemp:#construct list format
    rainfallList.append(entry.split(' '))

for entry in rainfallList: #format rainfall values 
    entry[0] = entry[0].upper()#uppercase names
    entry[1] = float(entry[1])#rainfall values as float


for entry in rainfallList: #create grouped list
    i = 0
    for category in categories:
        if category[0] <= entry[1] <= category[1]:
            orderedRainfallList[i].append(entry)
        i += 1
 
for group in orderedRainfallList:#Center Text
    if group:
        for item in group:
            item[0] = item[0].center(25)
            
for group in orderedRainfallList:#sort entries 
    if group:
        group.sort(key = lambda x:x[1])
        

#write formatted file
f = open('rainfallfmt.txt','w')

i = 0
for group in orderedRainfallList: #Write formated text to file
    f.write(str(categories[i]) + '\n')
    for entry in group:
        f.write('{:}{:5.1f}\n'.format(entry[0],entry[1]))
    i += 1
f.close()

            
    