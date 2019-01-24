//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
// code inspired from : http://zguide.zeromq.org/cpp:hwclient
//CLIENT
//Run on CLI with this command to avoid conflicts with imread and zmq:: g++ `pkg-config --cflags opencv` Hello_world_client.cpp `pkg-config --libs opencv` -o Hello_world_client -lzmq



#include<zmq.hpp>
#include<string>
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
	//prepare context and socket
	zmq::context_t context (1);
	zmq::socket_t socket (context,ZMQ_REQ);
	
	std::cout<<"Connecting to Hello World server ..."<<std::endl;
	socket.connect("tcp://localhost:5555");
	cv::Mat image;

	image = imread("/home/siemens/Desktop/cat.jpg");
	int columns = image.cols;
    	int rows = image.rows;

	//vector<uint8_t> img_list = [1,2,3,4,2,3,4,5]; 
	int num = 8;
	struct Message
	{
	  uint32_t one;
	  uint64_t two;
	};

	Message msg;
	msg.one = 1;
	msg.two = 20;
	
	
	



	
	// Giving 10 requests, with a delay for response
	for(int rqst_nmbr = 0; rqst_nmbr!=10;rqst_nmbr ++)
	{
		zmq::message_t request (32);
		//cout<<request.data()<<endl;

		//memcpy(request.data(), "Hello", 32);
		std::cout<<"Sending Hello"<<rqst_nmbr<<"....."<<std::endl;
		//cout<<request.data()<<endl;
		//socket.send(request);
		socket.send(&msg, sizeof(Message));

		//Get the reply
		zmq::message_t reply;
		socket.recv(&reply);
		std::cout<<"Recieved World"<<rqst_nmbr<<std::endl;
		
	}
	return 0;
	
}	
