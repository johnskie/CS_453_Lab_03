# http://www.haverford.edu/cmsc/course-pages/usingMake.html

process.o : Process.cpp Process.h
	g++ -c Process.cpp

clock.o : Clock.cpp Clock.h
	g++ -c Clock.cpp

mfqs.o : mfqs.cpp mfqs.h
	g++ -c mfqs.cpp

myprogram : mfqs.o clock.o process.o
	g++ -g process.o clock.o mfqs.o -lm -o myprogram