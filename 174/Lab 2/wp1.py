# Guess the word game V1
"""In the guess the word game a secret word is selected by the computer
from a list of preset words, and the user has to type a guess that will
then either be verified or shown to be wrong."""

#imort required modules
from random import choice
from uagame import Window

def main():

    # Choose the secret word randomly from a list
    list_of_words =  ['apple','banana','watermelon','kiwi','pineapple','mango']
    secret = choice(list_of_words)

    #Create window
    game_window = Window('Word Puzzle', 445,500)
    
    #Type instructions
    game_window.draw_string("I'm thinking of a secret word.",1,1)
    game_window.draw_string("Try and guess the word. You can guess one letter",1,game_window.get_font_height()) #get_font_height() fucntion used for y value offset calculation in each print and input statement
    game_window.draw_string("at a time. Each time you guess I will show you",1,2*game_window.get_font_height())
    game_window.draw_string("which letters have been correctly guessed and which",1,3*game_window.get_font_height())
    game_window.draw_string("letters are still missing. You wil have 4 guesses to",1,4*game_window.get_font_height())
    game_window.draw_string("guess all of the letters. Good luck!",1,5*game_window.get_font_height())
    game_window.draw_string("The answer so far is _" + secret[1:],1,6*game_window.get_font_height())

    # Obtain and print out the user guess
    guess = game_window.input_string("Guess a letter: " ,1,7*game_window.get_font_height())

    #Conditional check if user guess is correct
    if guess == secret[0]: #user guessed correct first letter
        game_window.draw_string("Good job! You found the word " + secret,1,8*game_window.get_font_height()) #correct guess display message
        
    else:#user did not guess correct first letter
        game_window.draw_string("Not quite, the correct word was " + secret + ". Better luck next time",1,8*game_window.get_font_height()) #incorrect guess display message

    game_window.input_string("Press enter to end the game " ,1,9*game_window.get_font_height()) # Wait for enter to be pressed
    game_window.close() #close window after enter is pressed

main()
