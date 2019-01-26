#
#   Hello World server in Python
#   Binds REP socket to tcp://*:5555
#   Expects b"Hello" from client, replies with b"World
#SERVER 
#code inspired from : http://zguide.zeromq.org/py:hwserver

import time
import zmq
import base64
import numpy as np
import cv2

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")
#socket.setsockopt(zmq.SUBSCRIBE, b'')


while True:
	#  Wait for next request from client
	#message = socket.recv()
	#print("Request Recieved : %s" %message)
	#Do some work
	frame = socket.recv()
	#print("Request Recieved : %s" %frame)
	#img = base64.b64decode(frame)
	npimg = np.fromstring(frame, dtype=np.uint8)
	source = cv2.imdecode(npimg, cv2.IMREAD_COLOR)
	print (type(frame))
	print (type(npimg))
	print (type(source))
	cv2.imshow("image", source)
	cv2.waitKey(0)
	#time.sleep(1)
	

	#send reply back to client
	socket.send(b"World")

socket.close();
