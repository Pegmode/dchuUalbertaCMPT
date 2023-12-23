"""
Memory version 3

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
      self.tile_buffer = None
      self.image_count = 0
      self.board_size = 4
      self.offset = 5
      self.images = []
      self.board = []
      self.get_images()
      self.create_board()
      self.elapsed_time = 0
      self.hide_delay = 0
      self.hide_buffer = [None, None]

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
       y = row_index * height + self.offset
       tile_width = 100 
       tile_height = 100
       for col_index in range(0, self.board_size):
           x = col_index * width + self.offset
           tile = Tile(x, y, tile_width, tile_height, self.images[self.image_count], self.image_count)
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
      if self.hide_delay == 0:
         self.hide()   
      else:
         self.hide_delay -= 1
      
      if event.type == QUIT:
         self.close_clicked = True
      elif event.type == MOUSEBUTTONUP and self.continue_game:
         if self.hide_delay == 0:
            self.handle_mouse_up(event)
      pygame.event.clear()

      
   def handle_mouse_up(self, event):
      # Respond to the player releasing the mouse button by 
      # taking appropriate actions.
      # - self is the Game where the mouse up occured.
      # - event is the pygame.event.Event object to handle

      for row in self.board:
         for tile in row:
            valid_move = tile.select(event.pos)
            if valid_move and self.tile_buffer == None:
               self.tile_buffer = tile
            elif valid_move and self.tile_buffer is not (tile or None):
               self.compare_tiles(tile)

                 

              
   def compare_tiles(self, tile):
      # compare buffer tile to tile, and 
      # either match or hide, then clear buffer
      # in case of hiding, wait 0.25 seconds first  
      
      if tile != self.tile_buffer:
         self.hide_buffer[0] = self.tile_buffer
         self.hide_buffer[1] = tile 
         self.hide_delay = self.calculate_delay_frames(0.25)
         #self.hide_delay = 50 
      if tile == self.tile_buffer:
         self.hide_buffer[0] = None# Reset hide_buffer
         self.hide_buffer[1] = None
         print('Match!')
         print('buffer and tile:',self.tile_buffer,tile)
         self.tile_buffer.expose
         tile.expose()#set current tile to be exposed
      self.tile_buffer = None 
   
   def hide(self):
      # hides hide_buffer tiles
      for tile in self.hide_buffer:
         if tile != None:
            tile.hide()
            tile = None
            
   def calculate_delay_frames(self,delay_time):
      #Converts delay time in seconds to number of frames to wait
      #time.sleep(sec)
      if delay_time >= self.pause_time:#make sure delay time is shorter than frame time
         return delay_time//self.pause_time#how many frames are needed to meet delay_time
      else: #error handling
         print("WARNING DELAY_TIME < Frame speed")
         return 0
      
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

    def __init__(self, x, y, width, height, image, image_number):
        # Initialize a tile to contain a ' '
        # - x is the int x coord of the upper left corner 
        # - y is the int y coord of the upper left corner 
        # - width is the int width of the tile
        # - height is the int height of the tile
        # - image is the image to be overlaid 

        self.rectangle = pygame.Rect(x, y, width, height)
        self.image = image
        self.exposed = False
        self.image_number = image_number
    
    def __eq__(self, other_tile):
        # Set conditions for use of the == operator on tiles
        if other_tile == None:
            final = False 
        else:
            final = self.image == other_tile.image 
        return final 
        
    def __str__(self):
        # return self's image name 
        return str(self.image_number)

    def select(self, mouse_position):
        # If the tile is clicked by the player and 
        # not already exposed, set self.exposed to true
        # if newly exposed, valid move is true 
        # - self is the tile 
        # - mouse- position is the mouse position 
        valid_move = False 
        if self.rectangle.collidepoint(mouse_position):
            if not self.exposed:
                self.exposed = True
                valid_move = True
        return valid_move 
                            
    def hide(self):
        # hide the tile 
        self.exposed = False 
        
    def expose(self):
        # expose the tile 
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




