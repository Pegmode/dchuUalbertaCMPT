#Lab 3 CMPUT 175
#Daniel Chu 1493374
#reduce found for mean from thepythonguru.com but applied to calculateStandarDev
#from functools import reduce


def readlist():
    user_input = input("Enter a set of numbers (separated by space)").split()
    for i in range(len(user_input)):
        user_input[i] = float(user_input[i])
    user_input.sort()
    return user_input
	



def calculateMean(num_list):
    return (sum(num_list) / len(num_list))

def calculateStandarDev(num_list):
    standard_dev = 0
    mean = calculateMean(num_list)
    current_sum = 0
    for num in num_list:
        current_sum += (num-mean)**2
    return (current_sum/(len(num_list)-1))**0.5


    #sigma = lambda a,b : a+(b-mean)**2
    #reduce(function, sequence[, initial]) -> value
    #reduce takes in a sequence then calls fuction with the previous calculation being one arguement and the next item in the seq being the 2nd for all items
    #return ( reduce(sigma,num_list) / (len(num_list)-1) )**0.5




def outlier(num_list):
    mean = calculateMean(num_list)
    standard_dev = calculateStandarDev(num_list)
    outliers = []
    for i in range(len(num_list)):
        if not(mean-3*standard_dev < num_list[i] < mean+3*standard_dev):
            outliers.append(num_list[i])
    return outliers



def main():
    is_continue = True
    while is_continue:
        user_list = readlist()
        print(user_list,'\n')
        print('The Mean is: ',calculateMean(user_list),'\n')
        print('Std Dev. is: ',calculateStandarDev(user_list),'\n')
        print('Outliers: ',outlier(user_list),'\n')
        user_ans = input('Do you want ot enter more data? (Y/N):')
        if user_ans.upper() == 'N':
            is_continue = False

main()
