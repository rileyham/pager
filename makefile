pager: pager.o process.o fifo.o lru.o mru.o mfu.o lfu.o random.o priority.o roundRobin.o fcfs.o sjf.o frameTable.o
	g++ pager.o process.o fifo.o lru.o mru.o mfu.o lfu.o random.o priority.o roundRobin.o fcfs.o sjf.o frameTable.o -o pager

pager.o: pager.h pager.cpp 
	g++ -c pager.cpp -o pager.o

process.o: process.h process.cpp
	g++ -c process.cpp -o process.o

fifo.o: Pagers/fifo.h Pagers/fifo.cpp
	g++ -c Pagers/fifo.cpp -o fifo.o

lru.o : Pagers/lru.h Pagers/lru.cpp
	g++ -c Pagers/lru.cpp -o lru.o

mru.o : Pagers/mru.h Pagers/mru.cpp
	g++ -c Pagers/mru.cpp -o mru.o

mfu.o : Pagers/mfu.h Pagers/mfu.cpp
	g++ -c Pagers/mfu.cpp -o mfu.o

lfu.o : Pagers/lfu.h Pagers/lfu.cpp
	g++ -c Pagers/lfu.cpp -o lfu.o

random.o : Pagers/random.h Pagers/random.cpp
	g++ -c Pagers/random.cpp -o random.o

priority.o: Schedulers/priority.h Schedulers/priority.cpp
	g++ -c Schedulers/priority.cpp -o priority.o

roundRobin.o: Schedulers/roundRobin.h Schedulers/roundRobin.cpp
	g++ -c Schedulers/roundRobin.cpp -o roundRobin.o

fcfs.o: Schedulers/fcfs.h Schedulers/fcfs.cpp
	g++ -c Schedulers/fcfs.cpp -o fcfs.o

sjf.o: Schedulers/sjf.h Schedulers/sjf.cpp Schedulers/priority.h Schedulers/priority.cpp
	g++ -c Schedulers/sjf.cpp -o sjf.o

scheduler: scheduler.o priority.o process.o roundRobin.o fcfs.o sjf.o
	g++ scheduler.o priority.o process.o roundRobin.o fcfs.o sjf.o -o scheduler

frameTable.o: frameTable.h frameTable.cpp
	g++ -c frameTable.cpp -o frameTable.o


