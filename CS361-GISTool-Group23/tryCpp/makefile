CXXFLAGS = -std=c++0x

test: try.o  report.o
	g++ ${CXXFLAGS} try.o report.o  -o test

try.o: try.cpp
	g++ ${CXXFLAGS} -c try.cpp


report.o: report.cpp report.hpp
	g++ ${CXXFLAGS} -c report.cpp

clean:
	rm *.o test
