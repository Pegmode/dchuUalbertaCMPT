##lab5-2
#Daniel Chu 1493374

months_dict = {
'1':31,
'2':28,
'3':31,
'4':30,
'5':31,
'6':30,
'7':31,
'8':31,
'9':30,
'10':31,
'11':30,
'12':31
}

def isValidDate(user_input):
	try:
		date_list = [int(entry) for entry in user_input.split('-')] #list compression
	except ValueError:
		print('Value Error: Year, Month and date must be numbers')
		return
	assert (date_list[1] in range(1,13)),'Month Must be between 1 and 12'
	assert (date_list[0] in range(1900,2021)),'Year must be bewtween 1901 and 2020'
	assert (date_list[0]%400 != 0 or date_list[1] != 2 or date_list[2] in range(1,30)),'Date out of range. Is leap year'
	assert ((date_list[2] in range (1,months_dict[str(date_list[1])]) and date_list[0]%400 != 0) or (date_list[0]%400 == 0) and date_list[1] == 2),'Date out of range'

def main():
	user_input = input('Enter date in YYYY-MM-DD format: ')
	try:
		assert (len(user_input) == 10 and user_input[4] == '-'and user_input[7] == '-'),'Wrong format! Please enter date in YYYY-MM-DD format!'
		isValidDate(user_input)
	except AssertionError as error:
		print('\nAssertion Error: {}\n'.format(error.args[0]))
	else:
		print('\n Date is Valid! \n')
main()
