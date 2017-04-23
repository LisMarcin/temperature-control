CXX=g++-4.9
CXXFLAGS= -std=c++14 -Wall -l mysqlclient_r -O3
TARGET=execute

$(TARGET): src/* main.cpp include/*
	$(CXX) main.cpp -o $(TARGET) -I include/ src/* $(CXXFLAGS)
