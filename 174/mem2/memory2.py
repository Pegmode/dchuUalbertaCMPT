"""
Memory version 2

this version adds:
   - the score, which is simply the time elapsed 
   - all tiles must start hidden 
   - when a player clicks a tile it should become exposed 
   - the game should end when all tiles are exposed 
"""
# import libraries 

from uagame import Window
import pygame, time
from pygame.locals import *
import math, random 

# User-defined functions

def main():

   window = Window('Memory', 540, 440)
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
      self.bg_color = pygame.Color('black')
      self.pause_time = 0.01 # smaller is faster game
      self.close_clicked = False
      self.continue_game = True
      self.image_count = 0
      self.board_size = 4
      self.images = []
      self.board = []
      self.get_images()
      self.create_board()
      self.elapsed_time = 0

   def get_images(self):
       # Creates a list of 16 shuffled images loaded from file
       # - self is the Game whose list is created 

       for i in range(1,9):
           self.images.append(pygame.image.load('image' + str(i) + '.bmp'))
       self.images = self.images + self.images
       random.shuffle(self.images)
       
      
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
       height = self.window.get_height() // self.board_size
       width = height
       y = row_index * height
       tile_width = 100 
       tile_height = 100
       for col_index in range(0, self.board_size):
           x = col_index * width 
           tile = Tile(x, y, tile_width, tile_height, self.images[self.image_count])
           row.append(tile)
           self.image_count += 1
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
      # - self is the Game where the mouse up occured.
      # - event is the pygame.event.Event object to handle

      for row in self.board:
          for tile in row:
              tile.select(event.pos)

   def draw(self):
      # Draw all game objects.
      # - self is the Game to draw

      self.window.clear()
      self.draw_score()
      for row in self.board:
          for tile in row:
              tile.draw()
      self.window.update()

   def update(self):
      # Update the game objects.
      # - self is the Game to update

      self.elapsed_time = pygame.time.get_ticks() // 1000

   def decide_continue(self):
      # Check and remember if the game should continue
      # - self is the Game to check
      
      tile_count = 0
      for row in self.board:
          for tile in row:
              if tile.check_exposed():
                  tile_count += 1
      if tile_count == 16:
          self.continue_game = False

   def draw_score(self):
       # Draw the score 
       # - self is the game to draw score for 

       score_string = str(self.elapsed_time)
       self.window.set_font_size(72)
       self.window.draw_string(score_string, 470, 20)

class Tile: 
    """
    An object in this class represents a square tile
    that contains an image.
    """
    #initialize the class attributes that are common to all tiles.
    window = None 
    fg_color = pygame.Color('blue') # for coloring rectangle 
    hidden_image = pygame.image.load('image0.bmp')

    @classmethod
    def set_window(cls, window):
        cls.window = window

    def __init__(self, x, y, width, height, image):
        # Initialize a tile to contain a ' '
        # - x is the int x coord of the upper left corner 
        # - y is the int y coord of the upper left corner 
        # - width is the int width of the tile
        # - height is the int height of the tile
        # - image is the image to be overlaid 

        self.rectangle = pygame.Rect(x, y, width, height)
        self.image = image
        self.exposed = False

    def select(self, mouse_position):
        # If the tile is clicked by the player and 
        # not already exposed, set self.exposed to true
        # - self is the tile 
        # - mouse- position is the mouse position 

        if self.rectangle.collidepoint(mouse_position):
            if not self.exposed:
                self.exposed = True

    def check_exposed(self):
        # return whether a given tile is exposed
        # - self is the tile 
        return self.exposed

    def draw(self):
        # Draw the tile on the surface, image type depends 
        # on whether tile is exposed 
        # - self is the tile 

        pygame.draw.rect(Tile.window.get_surface(), Tile.fg_color, self.rectangle)
        if self.exposed:
            Tile.window.get_surface().blit(self.image, self.rectangle) 
        else:
            Tile.window.get_surface().blit(Tile.hidden_image, self.rectangle)

main()




