Run the client.cpp with the following command :  g++ `pkg-config --cflags opencv` client.cpp `pkg-config --libs opencv` -std=c++14 -o client  -lzmq -I/home/ghost/Desktop/git-temp/include

/home/ghost/Desktop/git-temp/include : this is the location of the include folder that needs to be explicitely included since the compiler doesn't detect it automatically.
nlohmann json is used here and the include file is from his repo.
