# http://www.haverford.edu/cmsc/course-pages/usingMake.html

all: main.o mfqs.o clock.o process.o
	g++ process.o clock.o mfqs.o main.o -lm -o myprogram
process.o : Process.cpp Process.h
	g++ -c Process.cpp -o process.o

clock.o : Clock.cpp Clock.h
	g++ -c Clock.cpp -o clock.o

mfqs.o : mfqs.cpp mfqs.h
	g++ -c mfqs.cpp -o mfqs.o

main.o : main.cpp
	g++ -c main.cpp
