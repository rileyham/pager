pager: pager.o process.o fifo.o lru.o mfu.o
	g++ pager.o process.o fifo.o lru.o mfu.o -o pager

pager.o: pager.h pager.cpp
	g++ -c pager.cpp -o pager.o

process.o: process.h process.cpp
	g++ -c process.cpp -o process.o

fifo.o: Pagers/fifo.h Pagers/fifo.cpp
	g++ -c Pagers/fifo.cpp -o fifo.o

lru.o : Pagers/lru.h Pagers/lru.cpp
	g++ -c Pagers/lru.cpp -o lru.o

mfu.o : Pagers/mfu.h Pagers/mfu.cpp
	g++ -c Pagers/mfu.cpp -o mfu.o