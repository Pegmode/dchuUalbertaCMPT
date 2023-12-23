#Lab 2-1
#Coin guessing game
#Daniel Chu
#1493374
#CMPUT 175
import random

class Game():#Main Game class
    def __init__(self): #intialize variables
        self.debug_mode = True#enable/disable debug mode
        
        self.value = random.randint(1,99)#find random value from 1-99
        self.is_playing = True #Determines if the main game loop is running
        self.explanation_text = 'Enter coins values as 1-penny, 5-nickel, 10-dime, and 25-quarter.\nEtner coins that add up to {} cents, one per line.'.format(self.value)
        self.prompt_text = 'Enter a valid coin value > '
        self.player_guess = '' #current player guess
        self.player_total = 0 #sum of player inputs
        self.continue_game = False #decides if game continues once finished
        self.coin_values = (1,5,10,25)
        
        if self.debug_mode:
            print('Correct Answer: {}'.format(self.value))
 
    def PlayGame(self):#tells the game to start playign, contains main game loop
        print(self.explanation_text)
        while self.is_playing:
            self.PromptPlayer()
            self.HandleInput()
        self.EndGameScreen()

    def PromptPlayer(self):#give player input prompt and save user input (string)
        self.player_guess = input(self.prompt_text)
    
    def HandleInput(self):#check if player input is valid
        if self.player_guess.isdigit() and (int(self.player_guess) in self.coin_values):#checks if player input was an int and is in the range of acceptable values
            self.player_total += int(self.player_guess)
            if self.player_total > self.value:
                self.is_playing = False
        elif self.player_guess == '':#case in which player is done guessing and only presses enter
            self.is_playing = False
        else:
            print("Invalid Entry - Try again!")
            
    def EndGameScreen(self):#show endgame screen
        print("Here is the outcome:")
        
        if self.player_total == self.value:
            print('Success!')
        else:
            score_difference = self.player_total - self.value
            if score_difference > 0: #player was above the required value
                print('The amount exceeds {} cents by {} cents'.format(self.value,score_difference))          
            elif score_difference <0:
                print('You are short of {} cents'.format(abs(score_difference)))
                pass
        self.ContinuePrompt()       
        if self.continue_game == True:
            self.__init__()
            self.PlayGame()
            
    def ContinuePrompt(self):#prompt and logic for when game is finished
        input_string = input('Play another game session (y/n)?')
        if input_string == 'y':
            self.continue_game = True
        elif input_string == 'n':
            self.continue_game = False
        else:
            self.ContinuePrompt()
   
def main():
    game = Game()
    game.PlayGame()
main()