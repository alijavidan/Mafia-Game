CXXFLAGS := -std=c++11
a.out: main.o Room.o Player.o functions.o
	g++ main.o Room.o Player.o functions.o

main.o: main.cpp functions.hpp Room.hpp Player.hpp
	g++ -c main.cpp

Room.o: Room.cpp Room.hpp Player.hpp 
	g++ -c Room.cpp

Player.o: Player.cpp Player.hpp Exceptions.hpp
	g++ -c Player.cpp

functions.o: functions.cpp functions.hpp Exceptions.hpp Player.hpp
	g++ -c functions.cpp
clean:
	rm *.o a.out   
