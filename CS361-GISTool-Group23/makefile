CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = File.o Support.o

SRCS = File.cpp Support.cpp

HEADERS = File.hpp Support.hpp
	
file_test: ${OBJS} ${Headers}
	${CXX} ${OBJS} -o file_test
			
File: ${OBJS} ${Headers}
	${CXX} ${OBJS} -o File
	
Support: ${OBJS} ${Headers}
	${CXX} ${OBJS} -o Support
	
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm *.o
	rm file_test