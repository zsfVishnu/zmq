import zmq
import json
import numpy as np
import matplotlib.pyplot as plt
import cv2

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
	json_str = socket.recv()
	print("no error till here")
	data_print = json.loads(json_str)
	print(data_print["Image"]["rows"],data_print["Image"]["cols"])  #Check the number of rows and columns
	
	img = np.array(data_print["Image"]["data"])
	img = img.reshape(data_print["Image"]["rows"],data_print["Image"]["cols"], data_print["Image"]["channels"])
	
	b,g,r = cv2.split(img)      #Image channels will be inverted ie BGR 
	img = cv2.merge((r,g,b))
	
	plt.imshow(img)
	plt.show()

	socket.send(b"Hello")
