# Guess the word game V1
"""In the guess the word game a secret word is selected by the computer
from a list of preset words, and the user has to type a guess that will
then either be verified or shown to be wrong."""

from random import choice
from uagame import Window

debug = True

def draw_string_format(wingame,print_string,x,y):
    '''
    Prints text screen with new line characers
    '''
    font_height = wingame.get_font_height()
    print_string = print_string.splitlines()
    for line_string in print_string:
        wingame.draw_string(line_string,x,y)
        y += font_height
    return y

def build_progress_string(secret,correct_letter):
    '''
    builds a string that with correct guessed letters shown and unguessed 
    letters replaced with underscores
    '''
    progress_string = ''
    for letter in secret:
        if letter == correct_letter:
            progress_string += ' ' + correct_letter 
        else:
            progress_string += ' _'
            
    return progress_string

def main():
    
    # Make the game window
    wingame = Window("Word Game", 450, 500)
    
    # Choose the secret word randomly from a list
    list_of_words =  ['apple','banana','watermelon','kiwi','pineapple','mango']
    secret = choice(list_of_words)
    
    if debug == True:
        print('Answer is: {}'.format(secret))
    
    # format user instructions    
    info_text = '''I'm thinking of a secret word
Try and guess the word. You can guess one letter
at a time. Each time you guess I will show you
which letters have been correctly guessed and which
letters are still missing. You will have 4 guesses to
guess all of he letters. Good luck!
'''
    prompt_text ='The answer so far is:{}'
 
    # Print out the user instructions   
    current_line = draw_string_format(wingame,info_text+prompt_text.format(' _'*len(secret)),0,0)

    # Obtain user guess and print out win or loss scenario
    guess = wingame.input_string("Guess a letter: ",0,current_line)
    current_line += wingame.get_font_height()
    
    wingame.draw_string(prompt_text.format(build_progress_string(secret,guess)),0,current_line)
    current_line += wingame.get_font_height()    
    
    if guess.lower() in secret and guess !='':   
        current_line = draw_string_format(wingame,"Good job! You found the word {}!".format(secret),0,current_line)
    else:      
        current_line = draw_string_format(wingame,"Not quite, the correct word was {}. Better luck next time".format(secret),0,current_line)
        
    # End the game if enter is pressed
    end_game = wingame.input_string("Press enter to end the game",0,current_line)
    wingame.close()
    
main()
        
        
    