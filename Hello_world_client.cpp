//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
// code inspired from : http://zguide.zeromq.org/cpp:hwclient
//CLIENT
#include<zmq.hpp>
#include<string>
#include<iostream>

int main()
{
	//prepare context and socket
	zmq::context_t context (1);
	zmq::socket_t socket (context,ZMQ_REQ);
	std::cout<<"Connecting to Hello World server ..."<<std::endl;
	socket.connect("tcp://localhost:5555");

	// Giving 10 requests, with a delay for response
	for(int rqst_nmbr = 0; rqst_nmbr!=10;rqst_nmbr ++)
	{
		zmq::message_t request (5);
		memcpy(request.data(),"Hello",5);
		std::cout<<"Sending Hello"<<rqst_nmbr<<"....."<<std::endl;
		socket.send(request);

		//Get the reply
		zmq::message_t reply;
		socket.recv(&reply);
		std::cout<<"Recieved World"<<rqst_nmbr<<std::endl;

	}
	return 0;
	
}	