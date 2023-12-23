def get_top_left_coord(self):
    for i in range(len(self.board)):
	for j in range(len(self.board[i])):
		print("({},{})".format(self.board[i][j].x,self.board[i][j].x))







#for our code
def get_top_left_coord(self,number_of_tiles,tile_width,tile_height):
	for i in range(0,number_of_tiles):
		for j in range(0,number_of_tiles):
			print(str(self.board[i][j].topleft))


#w/o our code
def get_top_left_coord(self,number_of_tiles,tile_width,tile_height):
	for i in range(0,number_of_tiles): #group of rows
		for j in range(0,number_of_tiles): # entries in each row
			x_coord = tile_height * j
			y_coord = tile_width * i 
			print("({},{})".format(x_coord,x_coord))




seating_chart = [['Amy','Sarah','Brian'],['Donald','Jacob','Zoey'],['Amanda','Bob','Dora']]
