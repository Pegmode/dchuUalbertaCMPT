
# Tic Tac Toe Version 1
# This program allows two players to play Tic Tac Toe.
# The X and Y player's take turns selecting empty tiles
# to fill on a 3x3 board. If a player selects three tiles
# in a row, a column or a diagonal, that player wins.
# If all the tiles are filled without a win, the game is
# a draw.
# This program requires two data files: cursorx.txt and
# cursoro.txt that contain string represenations of  two
# custom cursors used in the game.
#
# V1 implements only a single player 'X' who can select 
# tiles using a regular cursor. A tile flashes when an 
# occupied tile is selected, but there is no win or draw
# indication at the end. The game runs until the player 
# closes the window.


from uagame import Window
import pygame, time
from pygame.locals import *
import math, random

# User-defined functions

def main():

   window = Window('Tic Tac Toe', 500, 400)
   window.set_auto_update(False)   
   game = Game(window)
   game.play()
   window.close()

# User-defined classes

class Game:
   # An object in this class represents a complete game.

   def __init__(self, window):
      # Initialize a Game.
      # - self is the Game to initialize
      # - window is the uagame window object
      
      self.window = window
      Tile.set_window(window)
      self.bg_color = 'black'
      self.font_color = 'white'
      self.pause_time = 0.01 # smaller is faster game
      self.close_clicked = False
      self.continue_game = True
      self.board_size = 3
      self.board = []
      self.player = 'X'
      self.create_board()
      
   def create_board(self):
      # Create the game board.
      # - self is the Game whose board is created

      for row_index in range(0, self.board_size):
         row = self.create_row(row_index)
         self.board.append(row)
      
   def create_row(self, row_index):
      # Create one row of the board
      # - self is the Game whose board row is being created
      # - row_index is the int index of the row starting at 0

      row = []
      width = self.window.get_width() // self.board_size
      height = self.window.get_height() // self.board_size
      y = row_index * height
      for col_index in range(0, self.board_size):
         x = col_index * width
         tile = Tile(x, y, width, height)
         row.append(tile)
      return row

   def play(self):
      # Play the game until the player presses the close box.
      # - self is the Game that should be continued or not.

      while not self.close_clicked:  # until player clicks close box
         # play frame
         self.handle_event()
         self.draw()            
         if self.continue_game:
            self.update()
            self.decide_continue()
         time.sleep(self.pause_time) # set game velocity by pausing

   def handle_event(self):
      # Handle each user event by changing the game state
      # appropriately.
      # - self is the Game whose events will be handled

      event = pygame.event.poll()
      if event.type == QUIT:
         self.close_clicked = True
      elif event.type == MOUSEBUTTONUP and self.continue_game:
         self.handle_mouse_up(event)
         
   def handle_mouse_up(self, event):
      # Respond to the player releasing the mouse button by
      # taking appropriate actions.
      # - self is the Game where the mouse up occurred.
      # - event is the pygame.event.Event object to handle
      
      for row in self.board:
         for tile in row:
            tile.select(event.pos, self.player)

   def draw(self):
      # Draw all game objects.
      # - self is the Game to draw
      
      self.window.clear()
      for row in self.board:
         for tile in row:
            tile.draw()
      self.window.update()

   def update(self):
      # Update the game objects.
      # - self is the Game to update
      pass

   def decide_continue(self):
      # Check and remember if the game should continue
      # - self is the Game to check
      pass

   
class Tile:
   # An object in this class represents a Rectangular tile
   # that contains a string. A new tile contains an empty
   # string. A tile can be selected if the tile contains a
   # position. If an empty tile is selected its string can
   # be changed. If a non-empty tile is selected it will flash
   # the next time it is drawn. A tile can also be set to
   # flash forever. Two tiles are equal if they contain the
   # same non-empty string.


   # initialize the class attributes that are common to all tiles.
   window = None
   fg_color = pygame.Color('white')  # for drawing the border
   border_width = 3 # the pixel width of the tile border
   font_size = 144    # for drawing the player symbol
   
   @classmethod
   def set_window(cls, window):
      # remember the window
      cls.window = window
   
   def __init__(self, x, y, width, height):
      # Initialize a tile to contain a ' '
      # - x is the int x coord of the upper left corner
      # - y is the int y coord of the upper left corner
      # - width is the int width of the tile
      # - height is the int height of the tile
      
      self.rectangle = pygame.Rect(x, y, width, height)
      self.content = ''
      self.flashing = False
      

   def draw(self):
      # Draw the tile on the surface
      # - self is the Tile
      
      if self.flashing:
         pygame.draw.rect(Tile.window.get_surface(), Tile.fg_color, self.rectangle)
         self.flashing = False
      else:
         self.draw_content()

   def draw_content(self):
         pygame.draw.rect(Tile.window.get_surface(), Tile.fg_color, self.rectangle, Tile.border_width)
         Tile.window.set_font_size(Tile.font_size)
         content_width = Tile.window.get_string_width(self.content)
         content_height = Tile.window.get_font_height()
         content_x = self.rectangle.left + (self.rectangle.width - content_width) // 2
         content_y = self.rectangle.top + (self.rectangle.height - content_height) // 2
         Tile.window.draw_string(self.content, content_x, content_y) 
      
   def select(self, mouse_position, player_symbol):
      # A position was selected. If the position is in the Tile
      # and the Tile is empty, then update the Tile content
      # - self is the Tile
      # - position is the selected location (tuple)
      # - new_content is the new str contents of the tile
      
      if self.rectangle.collidepoint(mouse_position):
         if self.content == '':
            self.content = player_symbol
         else:
            self.flashing = True

main()
TTTV1-A2.py
Displaying TTTV1-A2.py.
