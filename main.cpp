#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

#include "functions.hpp"
#include "Room.hpp"
#include "Player.hpp"

using namespace std;

int main ( ) {
	srand (time(NULL));
	vector<Room*> rooms;
	Room* current_room = NULL;
	string str;
	try {
		while ( cin >> str )
			selection ( str, rooms, current_room);
	} catch (exit_exception e) {
		return 0;
	} catch (jokerWon e) {
		cout << "Do i look like a guy with a plan?\n";
		return 0;
	}
}
