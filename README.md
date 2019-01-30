### zmq
Trials and tests on zmq for sending images,vectors etc via nlohmann json.


## Hello_world files are just an intro on basic client server REQ-REP data transfer via zmq
Compile the Hello_world_client.cpp as :
g++ 'pkg-config --cflags opencv'  cpp_file_name.cpp 'pkg-config --libs opencv' -o cppfile_name -lzmq

## Simple_image_test has the code for sending images,vectors, variables etc
