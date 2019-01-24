#
#   Hello World server in Python
#   Binds REP socket to tcp://*:5555
#   Expects b"Hello" from client, replies with b"World
#SERVER 
#code inspired from : http://zguide.zeromq.org/py:hwserver

import time
import zmq
import json



context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

while True:
	#  Wait for next request from client
	message = socket.recv()
	#print(message.decode('utf-8'))
	#print(json.loads(message.decode('utf-8')))
	print(repr(message.decode('utf-8')))	
#Do some work
	time.sleep(1)
	
	#send reply back to client
	socket.send(b"World")


