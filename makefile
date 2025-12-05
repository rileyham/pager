pager: pager.o process.o fifo.o
	g++ pager.o process.o fifo.o -o pager

pager.o: pager.h pager.cpp
	g++ -c pager.cpp -o pager.o

process.o: process.h process.cpp
	g++ -c process.cpp -o process.o

fifo.o: Pagers/fifo.h Pagers/fifo.cpp
	g++ -c Pagers/fifo.cpp -o fifo.o