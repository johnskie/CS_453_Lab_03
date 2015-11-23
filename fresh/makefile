# http://www.haverford.edu/cmsc/course-pages/usingMake.html

all :  process.o  whs.o readin.o main.o
	g++ -g -std=c++0x process.o whs.o readin.o main.o -lm -o myprogram
process.oq : Process.cpp Process.h
	g++ -g -c Process.cpp -o process.o
readin.oq : readin.cpp readin.h
	g++ -g -c readin.cpp -o readin.o
whs.o : whs.cpp
	g++ -g -c whs.cpp
main.o : main.cpp
	g++ -g -c main.cpp