CXXFLAGS = -std=c++0x

newReport: createReport.o  report.o
	g++ ${CXXFLAGS} createReport.o report.o  -o newReport

createReport.o: createReport.cpp
	g++ ${CXXFLAGS} -c createReport.cpp


report.o: report.cpp report.hpp
	g++ ${CXXFLAGS} -c report.cpp

clean:
	rm *.o newReport
