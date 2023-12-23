
def get_top_left_coord(number_of_tiles,tile_width,tile_height):
	for i in range(0,number_of_tiles): #list of rows lists
		for j in range(0,number_of_tiles): #list of entries in each row
			x_coord = tile_height * j
			y_coord = tile_width * i 
			print("({},{})".format(x_coord,y_coord))


get_top_left_coord(3,3,3)