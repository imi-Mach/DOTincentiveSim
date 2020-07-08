CXX=g++
CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

sim1: main.o functions.o
	${CXX} ${LFLAGS} -o sim1 main.o functions.o

main.o: main.cpp
	${CXX} ${CFLAGS} main.cpp

functions.o: functions.hpp functions.cpp
	${CXX} ${CFLAGS} functions.cpp

clean:
	rm -f *.o
	rm -f sim1

clear:
	clear
	make