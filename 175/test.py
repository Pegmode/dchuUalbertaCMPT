import pdb

y = [1,2,3,4,5,6]

def main():
	x = input("input:")
	for i in range(len(x)):
		print(x[i])
	print(y)
	pdb.set_trace()
	print(y.reverse())

main()
