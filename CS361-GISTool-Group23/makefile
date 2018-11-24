CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = File.o

SRCS = File.cpp

HEADERS = File.hpp
	
file_test: ${OBJS} ${Headers}
	${CXX} ${OBJS} -o file_test
			
File: ${OBJS} ${Headers}
	${CXX} ${OBJS} -o File
		
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm *.o
	rm file_test