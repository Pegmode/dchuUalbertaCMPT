# Guess Version 1
# In the Guess the number game a 
# random number is selected by the computer
# and the user has to try and guess the 
# number and input their guess
#
# V1 uses the python shell to display all
# instructions and interactions, and
# implements all parts of the full game

from random import randint

def main():
    
    # Display user instructions
    print("I am thinking of a number between 1 and 10.")
    
    # Get a random number
    number = randint(1,10)
    
    # Get the user guess
    guess = input("What is the number?")
    
    # Display random number and user guess
    print("The number was {}.".format(number))
    print("You guessed {}.".format(guess))

main()