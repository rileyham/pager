pager: pager.o process.o
	g++ pager.o process.o -o pager

pager.o: pager.h pager.cpp
	g++ -c pager.cpp -o pager.o

process.o: process.h process.cpp
	g++ -c process.cpp -o process.o