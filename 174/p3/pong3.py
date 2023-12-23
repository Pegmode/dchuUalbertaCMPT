
# Pong V3
'''
In the game pong 2 players play a simluated game of ping pong
'''

# Import libraries
from uagame import Window
from pygame import *
import time

# User defined functions

class Game():
    # Represents a complete game

    def __init__(self,game_window):
        #set up atributes

        self.pause_time = 1/200 #pause time b/w drawing frames (def: 1/200)
        self.close_clicked =  False #indicates if close button was clicked
        self.game_window = game_window
        self.rect_size = (10,80) #width, height (def: 10,80  test: 10,200)
        self.color = 'white'
        self.surface = self.game_window.get_surface()
        self.max_score = 11
        self.update_screen = True
        self.paddle_speed = 2

        self.score = [0,0]
        self.game_window.set_font_size(80)
        self.score_location_x = [0,self.game_window.get_width()-self.game_window.get_string_width(str(0))]
        self.score_location_y = 30

        #setup shapes
        self.centre_y = (500/2)-(self.rect_size[1]/2)
        self.ball = Ball(self.game_window,self.color)
        self.left_rect = Rect((50,self.centre_y),self.rect_size)#(L,Top),(width,height)
        self.right_rect = Rect((500-50-self.rect_size[0],self.centre_y),self.rect_size)
        self.border_rect = Rect(0,0,self.game_window.get_width(),self.game_window.get_height())

        self.key_dict = {
        'q': [False,-1,'left',K_q], #Key state, Direction (1up,-1down), side, Keyscaen index code
        'a': [False,1,'left',K_a],
        'p': [False,-1,'right',K_p],
        'l': [False,1,'right',K_l]
        }

        key.set_repeat(1,1)
        game_window.set_auto_update(False)
        event.set_allowed((QUIT,KEYDOWN)) #allowed events
    def play_game(self):
        # Play the game until the player presses a button
        while not self.close_clicked:
            self.handle_event()
            self.update_game_objects()
            self.draw_game()#draw frames
            #wait for tick pause_time USE time.Clock.tick() from pygame!!!!
            time.sleep(self.pause_time)

    def handle_event(self):
        # You can use event.poll() here if you want
        if event.peek(QUIT):
            self.close_clicked = True
        #other event peeks go here

        if event.peek(KEYDOWN):
            list_of_keys = key.get_pressed()
            for keys in self.key_dict:
                if list_of_keys[self.key_dict[keys][3]]:
                    self.key_dict[keys][0] = True
        event.clear()


    def update_game_objects(self):
        # Update the game objects
        if self.update_screen:
            #update balls
            self.ball.check_collide((self.left_rect.topleft,self.left_rect.bottomright),(self.right_rect.topleft,self.right_rect.bottomright))
            self.ball.move()
            self.update_score()
            #update paddles
            for keys in self.key_dict:
                if self.key_dict[keys][0] and self.key_dict[keys][2] == 'left' and self.border_rect.contains(self.left_rect.move(0,self.key_dict[keys][1]*self.paddle_speed)):
                    self.left_rect = self.left_rect.move(0,self.key_dict[keys][1]*self.paddle_speed)
                elif self.key_dict[keys][0] and self.key_dict[keys][2] == 'right' and self.border_rect.contains(self.right_rect.move(0,self.key_dict[keys][1]*self.paddle_speed)):
                    self.right_rect = self.right_rect.move(0,self.key_dict[keys][1]*self.paddle_speed)
            self.clear_key_state()


    def clear_key_state(self):
        for keys in self.key_dict:
            self.key_dict[keys][0] = False

    def draw_game(self):
        # Draws all objects
        self.game_window.clear()
        draw.rect(self.surface,Color(self.color),self.left_rect,0)
        draw.rect(self.surface,Color(self.color),self.right_rect,0)
        self.ball.draw()
        self.draw_score()
        #need to update the window before surface updates show up
        self.game_window.update()

    def update_score(self):
        scored_flags = self.ball.get_scored()
        for i in range(len(scored_flags)):
            if scored_flags[i]:
                self.score[i] += 1
                if self.score[i] >= self.max_score:
                    self.update_screen = False

        self.score_location_x[1] = self.game_window.get_width()- self.game_window.get_string_width(str(self.score[1])) #set right score to edge of screen


    def draw_score(self):
        #for i in self.score:
            #self.game_window.draw_string(str(self.score[i]),self.score_location_x[i],self.score_location_y)

        self.game_window.draw_string(str(self.score[1]),self.score_location_x[0], self.score_location_y)
        self.game_window.draw_string(str(self.score[0]),self.score_location_x[1], self.score_location_y)


class Ball():
    # An object in this class represents a ball

    def __init__(self,game_window,color):
        self.radius = 5
        self.position = [250,250] #Initial pos x,y
        self.velocity = [3,1] #x,y
        self.game_window = game_window
        self.color = color
        self.collision = [False,False] #left, right (only y axis)

    def draw(self):
        # Draw the ball
        draw.circle(self.game_window.get_surface(),Color(self.color),self.position,self.radius,0)

    def check_collide(self,rect1,rect2):
        #edge detection
        self.collision = [False,False] #left,right
        for index in range(0,2):
            if self.position[index] not in range(0,500):
                self.velocity[index] = -self.velocity[index]
                #only triggers on y axis collision
                if index == 0 and self.position[0] <= 250:
                    self.collision[0] = True
                elif index == 0 and self.position[0] > 250:
                    self.collision[1] = True

        #paddle detection
        rect_group = (rect1,rect2)
        for obj in range(0,2):
            if self.position[0] in range(rect_group[obj][0][0],rect_group[obj][1][0]) and self.position[1] in range(rect_group[obj][0][1],rect_group[obj][1][1]) :
                if self.position[0] <= 250 and self.velocity[0] <= 0:
                    self.velocity[0] = -self.velocity[0]
                elif self.position[0] > 250 and self.velocity[0] >= 0:
                    self.velocity[0] = -self.velocity[0]

    def get_scored(self):
        return self.collision

    def move(self):
        # Moves the ball, wraps it when it hits screen edge
        window_size = (self.game_window.get_width(), self.game_window.get_height())
        for index in range(0, 2):
            #self.position[index] = (self.position[index] + self.velocity[index]) % window_size[index]
            self.position[index] += self.velocity[index]

def main():
    game_window = Window('Pong',500,500)
    current_game = Game(game_window)
    current_game.play_game()
    game_window.close()

main()
