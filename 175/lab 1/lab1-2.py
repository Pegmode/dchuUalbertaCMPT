#Earthquake text formatter
#Daniel Chu 1493374 CMPUT 175
#Got assistance from Ethan Anderson

import os


f = open('earthquake.txt','r')

tempEarthquakeList = []
earthquakeList = []
formattedEarthquakeList = []

while f.tell() < os.path.getsize('earthquake.txt'):#read input .txt file line by line
    tempEarthquakeList.append(f.readline())
    tempEarthquakeList[-1] = tempEarthquakeList[-1].replace('\n','')#trim newline characters
                       
f.close()                       
    
for entry in tempEarthquakeList:#split lines
    earthquakeList.append(entry.split(' '))
                    
for entry in earthquakeList:#fill final list
    if entry[-1] not in formattedEarthquakeList:#is the entry in a new location?
        formattedEarthquakeList.append([])
        
        formattedEarthquakeList[-1].append(entry[-1])#append location name
        
        formattedEarthquakeList[-1].append([])#prep blank list
        formattedEarthquakeList[-1][-1].append(entry[1])#append Data
        formattedEarthquakeList[-1][-1].append(entry[0])
    else: #if entry location already in list
        for location in formattedEarthqukeList:
            if location[0] == entry[-1]:
                location.append([])#prep blank list
                location[-1].append(entry[1])#append Data
                location[-1].append(entry[0])


for group in formattedEarthquakeList:
    print(str(group))
                            
    
