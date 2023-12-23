#example in class
def main(z,x=3): 
#assignment in arguements cause those values to be initilized when func is called
#if no arguement is given in that position then value in arguement is what is taken
	print(z,x)

main(1) #varible not given in arguement; defualt value taken
main(5,x=5) #varible given in arguement; x is now 5
