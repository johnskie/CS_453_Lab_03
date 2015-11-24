
all : mfqs.o clock.o process.o  main.o
	g++ -g -std=c++0x process.o clock.o mfqs.o main.o -lm -o myprogram
process.oq : Process.cpp Process.h
	g++ -g -c Process.cpp -o process.o

clock.o : Clock.cpp Clock.h
	g++ -g -c Clock.cpp -o clock.o

mfqs.o : mfqs.cpp mfqs.h
	g++ -g -c -std=c++0x mfqs.cpp -o mfqs.o

main.o : main.cpp
	g++ -g -c main.cpp

clean :
	rm -rf *o myprogram
