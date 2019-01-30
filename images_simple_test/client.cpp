#include <zmq.hpp> 
#include <string>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp> 
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <typeinfo>

// for convenience
using json = nlohmann::json;




class client_class
  {
    public:
      void client_function()
        {
          while (true)
            {
              // create an empty structure (null)
              json j;
              std::string data;
              float f = 3.12;

              // add a number that is stored as double (note the implicit conversion of j to an object)
              cv::Mat mat = cv::imread("insti.jpg",CV_LOAD_IMAGE_COLOR);
              std::vector<uchar> array;
              if (mat.isContinuous()) 
                {
                  array.assign(mat.datastart, mat.dataend);
                } 
              else 
                {
                  for (int i = 0; i < mat.rows; ++i) 
                    {
                      array.insert(array.end(), mat.ptr<uchar>(i), mat.ptr<uchar>(i)+mat.cols);
                    }
                }

              std::vector<uint> v = {1,5,9};
              j["Type"] = f;                            //float
              j["vec"] = v;                             //vector
              j["Image"]["rows"] = mat.rows;            //Number of rows in the image matrix
              j["Image"]["cols"] = mat.cols;            //Number of columns
              j["Image"]["channels"] = mat.channels();  //Number of channels of the image
              j["Image"]["data"] = array;               //Pass the array
              j["Parameter"] = "Frequency";             //String
              j["Value"] = "5.17e9";                    //string

             
              std::string s = j.dump();                 // explicit conversion to string

              zmq::context_t context (1);
              zmq::socket_t socket (context, ZMQ_REQ);
              socket.connect ("tcp://localhost:5555");
              zmq::message_t request (s.size());
              memcpy (request.data (), (s.c_str()), (s.size()));
              socket.send(request);
            }
        }

  };

int main (void)
  {
    client_class caller;
    caller.client_function();
  }

