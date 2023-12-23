import math
import colorsys
import time
from PIL import Image
 
def plasma (w, h,t):
	out = Image.new("RGB", (w, h))
	pix = out.load()
	for x in range (w):
		for y in range(h):
			hue = 4.0 + math.sin(x / 19.0 + t) + math.sin(y / 9.0 + t) \
				+ math.sin((x + y) / 25.0 + t) + math.sin(math.sqrt(x**2.0 + y**2.0) / 8.0 + t)
			hsv = colorsys.hsv_to_rgb(hue/8.0, 1, 1)
			pix[x, y] = tuple([int(round(c * 255.0)) for c in hsv])
	return out
 
def plasma2 (w, h,t):
	out = Image.new("RGB", (w, h))
	pix = out.load()
	for x in range (w):
		for y in range(h):
			hue =  math.sin(x * 1 + t)
			hsv = colorsys.hsv_to_rgb(hue/8.0, 1, 1)
			pix[x, y] = tuple([int(round(c * 255.0)) for c in hsv])
	return out

 
def plasma3 (w, h,t):
	out = Image.new("RGB", (w, h))
	pix = out.load()
	for x in range (w):
		for y in range(h):
			cx = x +0.5*math.sin(t/5)
			cy = y + 0.5*math.cos(t/3)
			hue =  math.sin(math.sqrt(100*(cx**2+cy**2)+1)+t)
			hsv = colorsys.hsv_to_rgb(hue/8.0, 1, 1)
			pix[x, y] = tuple([int(round(c * 255.0)) for c in hsv])
	return out


if __name__=="__main__":
	for i in range(500):
		im = plasma2(400, 400,i*0.5)
		im.show()

		
		
