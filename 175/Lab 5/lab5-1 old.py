#lab 5
#Daniel Chu 1493374

def readAccounts(infile):
	file_lines = infile.readlines()
	accounts = {line.split(':')[0]:line.split(':')[1] for line in file_lines} #dict compresion
	for key in accounts:
		try:
			accounts[key] = float(accounts[key])#used because string.isdigit does not detect negative
		except ValueError:
			del accounts[key]
			print('ValueError. Account for {} not added: illegal value for ballance'.format(key))
	return accounts

def processAccounts(accounts):
	is_running = True
	while is_running:
		user_input = input("Enter account name, or 'stop' to exit: ")
		if user_input == 'stop':
			is_running = False
		else:
			try:
				accounts[user_input]
			except KeyError:
				print('KeyError: Account for {} does not Exist. Transaction cancelled.'.format(user_input))
			else:
				try:
					amount = input('Enter transaction amount for {}: '.format(user_input))
					accounts[user_input] += float(amount)
				except ValueError:
					print('Value Error. Incorrect Amount. Transactio cancelled.')
				else:
					print('New balance for account {}: {}'.format(user_input,accounts[user_input]))


def main():
	filename =  input('Enter filename> ')
	try:
		f = open(filename,'r')
	except IOError:
		print("IOError. {} does not exist".format(f))
		return
	processAccounts(readAccounts(f))
main()
