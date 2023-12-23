#Lab 2-2
#unzip function
#Daniel Chu
#1493374
#CMPUT 175

#example data from lab explanation
test_data1 = [(1,2)]
test_data2 = []
test_data3 = [(1,4),(2,5),(3,6)]
test_data4 = [('A','B'),('X','Y')]

def unzip(packed_list):
    new_list = ([],[]) #create blank list
    for touple in packed_list:
        for j in range(0,2):
            new_list[j].append(touple[j])
    return new_list 

#show example output data from lab explanantion
print(unzip(test_data1))
print(unzip(test_data2))
print(unzip(test_data3))
print(unzip(test_data4))



           
        