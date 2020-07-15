CXX=g++
CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g
INCLUDE_OBJECTS=-I./objects/
INCLUDE_CFUNCS=-I./cfunctions/

sim1: main.o Cell.o Entity.o User.o SensingTask.o Enviroment.o Game.o functions.o
	${CXX} ${LFLAGS} -o sim1 main.o Cell.o Entity.o User.o SensingTask.o Enviroment.o Game.o functions.o

main.o: main.cpp
	${CXX} ${CFLAGS} ${INCLUDE_OBJECTS} ${INCLUDE_CFUNCS} main.cpp

Cell.o: Cell.cpp Cell.hpp
	${CXX} ${CFLAGS} ${INCLUDE_OBJECTS} Cell.cpp

Entity.o: Entity.cpp Entity.hpp
	${CXX} ${CFLAGS} ${INCLUDE_OBJECTS} Entity.cpp

User.o: User.cpp User.hpp
	${CXX} ${CFLAGS} ${INCLUDE_OBJECTS} User.cpp

SensingTask.o: SensingTask.cpp SensingTask.hpp
	${CXX} ${CFLAGS} ${INCLUDE_OBJECTS} SensingTask.cpp

Enviroment.o: Enviroment.cpp Enviroment.hpp
	${CXX} ${CFLAGS} ${INCLUDE_OBJECTS} Enviroment.cpp

Game.o: Game.cpp Game.hpp
	${CXX} ${CFLAGS} ${INCLUDE_OBJECTS} Game.cpp

functions.o: functions.hpp functions.cpp
	${CXX} ${CFLAGS} ${INCLUDE_CFUNCS} functions.cpp

clean:
	rm -f *.o
	rm -f sim1

clear:
	clear
	make