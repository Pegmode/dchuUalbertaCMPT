import random

initial_prompt = '''I am thinking of a 3 digit number. Try to guess what it is. You have 10
attempts.
If you guess none of the digits I will answer WRONG
I will answer DING for every correct digit in the right position
and will answer DONG for every correct digit in the wrong position.
'''
debug = True

class Secret_Number():
    def __init__(self):
        self.number = []
        self.generate_number()

    def generate_number(self):
        is_illegal = True
        while is_illegal:
            number_buffer = random.sample(range(0,9),3)
            if number_buffer[0] != 0:
                is_illegal = False
        for number in number_buffer:
            self.number.append(str(number))

    def get(self):
        return self.number

    def getClues(self,guess):
        guess_set = set(guess)
        number_set = set(self.number)
        intersection_length = len(number_set.intersection(guess_set))
        if list(guess) == self.number:
            return "CORRECT"
        elif intersection_length > 0:
            return_buffer_ding = ''
            return_buffer_dong = ''
            for i in range(3):
                if guess[i] == self.number[i]:
                    return_buffer_ding += "DING "
                elif guess[i] in self.number:
                    return_buffer_dong += "DONG "
            return return_buffer_ding + return_buffer_dong

        else:
            return "WRONG"

def debug():
    sNum = Secret_Number()
    print("debug {}".format(sNum.get()))
    for i in range(5):
        ip = input("Guess a number: ")
        print(sNum.getClues(ip))
    print(sNum.get())

def readNumber(attempt_number):
    is_illegal = True
    while is_illegal:
        guess = input('Enter a three digit number with non-repeating digits\nGuess attempt {}:'.format(attempt_number))
        if guess.isdigit() and len(guess) == 3 and len(set(guess)) == len(guess):
            is_illegal = False
    return guess


def main():
        max_attempts = 5
        is_play = True
        secret_number = Secret_Number()
        while is_play:
            if debug:
                print('***SECRET NUMBER: {}***\n\n'.format(secret_number.get()))
            print(initial_prompt)
            for i in range(max_attempts):
                 clue = secret_number.getClues(readNumber(i))
                 print(clue)
                 if clue == "CORRECT":
                    print('You guessed it after {} attempts. The number is indeed {}'.format(i,secret_number.get()))
                    break
                 if i == max_attempts-1:
                     print('Out of attempts, you lost!')
            continue_prompt = input('Do you want to play again (Y/N)?')
            if continue_prompt.upper() == 'N':
                is_play = False
            secret_number = Secret_Number()
main()
