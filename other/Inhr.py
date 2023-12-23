#inheretence test

class Queue():
	def __init__(self,capacity):
		assert isinstance(capacity,int),("Error: Type Error:{}".format(type(capacity)))
		assert capacity >= 0,("Error: Illegal capacity:{}".format(capacity))
	
		self.__capacity = capacity
		self.__items = []
	def capacity(self):
		return self.__capacity

class BoundedQueue(Queue):
	def __init__(self,capacity):
		super().__init__(capcity)
		
