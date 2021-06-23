#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <string>
#include <algorithm>

#include "Player.hpp"
#include "Room.hpp"

using namespace std;

void checkGameStatus (Room*&);
void get_room_state (Room*&); 
bool compareLogin (Player*, Player*);
void checkMuteStatus (string, Room*&);
void heal (Room*&);
void silence (Room*&);
void detect (Room*&);
int countAlives (Room* &current_room, string);	
string MafiaVillager (string);
void ratioCheck (string);
void checkUser (string, Room*&);
bool numberChecker (const string&);
void dashChecker (string);
void roleChecker (string);
void checkRoom (string, vector<Room*>&, Room*&, string);
void create_room (vector<Room*>&, Room*&);
void switch_room (vector<Room*>&, Room*&);
void randomize(vector<Room*>&, Room*&);
void join(vector<Room*>&, Room*&);
void vote(vector<Room*>&, Room*&);
void end_vote(vector<Room*>&, Room*&);
void selection (string, vector<Room*>&, Room*&);
void voteAllowance (string, Room*&);
void checkDeathStatus (string, Room*&);

#endif