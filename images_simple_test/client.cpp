#include <stdio.h>
#include <zmq.hpp>
#include <opencv2/opencv.hpp>
#include "fstream"
#include "iostream"
int main()
{
    zmq::context_t context(1);
    zmq::socket_t sock(context, ZMQ_REQ);
    sock.connect("tcp://localhost:5555");
    std::string data;
    {
        cv::Mat Imgdata = cv::imread("bagree.JPG", CV_LOAD_IMAGE_GRAYSCALE);
        std::vector<uchar> data_encode;
        cv::imencode("bagree.JPG", Imgdata, data_encode);
        data = std::string(data_encode.begin(), data_encode.end());
    }
    // send
    {
        zmq::message_t message(data.size());
        memcpy(message.data(), data.c_str(), data.size());
        sock.send(message);
    }
    sock.close();
    system("pause");
    return 0;
}
