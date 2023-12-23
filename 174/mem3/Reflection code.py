#in game
	def __init(self):
		self.clicked_tile = None
		self.clicked_display_size = 30#chage thing
#in Tile
	def __init__(self):
		self.hidden_click_tracker = 0



##IN MOUSE HANDLE
	...
	self.click_tracker_handler(tile)
	

def click_tracker_handler(self,tile):
	tile.hidden_click_tracker += 1
	self.clicked_tile = tile

## in drawing 
...

self.window.set_font_size(self.clicked_dislpay_size)
if self.clicked_tile != None:
	self.window.draw_string(str(self.clicked_tile.hidden_click_tracker),self.clicked_tile.rectangle.x,self.clicked_tile.rectangle.y)
self.window.update()
