#Earthquake text formatter
#Daniel Chu 1493374 CMPUT 175
#Got assistance from Ethan Anderson

import os


f = open('earthquake.txt','r')

tempEarthquakeList = []
earthquakeList = []
formattedEarthquakeDict = {}

while f.tell() < os.path.getsize('earthquake.txt'):#read input .txt file line by line
    tempEarthquakeList.append(f.readline())
    tempEarthquakeList[-1] = tempEarthquakeList[-1].replace('\n','')#trim newline characters
                       
f.close()                       
    
for entry in tempEarthquakeList:#split lines
    earthquakeList.append(entry.split(' '))
                    
for entry in earthquakeList:#fill final list
    if entry[-1] not in formattedEarthquakeDict:#Is the current location already in the dictionary
        formattedEarthquakeDict[entry[-1]] = []#create Blank list at new location
        
    formattedEarthquakeDict[entry[-1]].append([])    
    formattedEarthquakeDict[entry[-1]][-1].append(entry[1])#append date
    formattedEarthquakeDict[entry[-1]][-1].append(entry[0])#append magnitude


for locations in formattedEarthquakeDict:
    #print('[{} ,{}]'.format(locations,formattedEarthquakeDict[locations]))
    print(locations ,formattedEarthquakeDict[locations])
    
      
    
