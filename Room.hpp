#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <sstream>
#include <vector>

#include "Player.hpp"

using namespace std;

class Room;

class Vote {
public:
	Vote (string, string, Room*&);
	Player* get_voter ();
	Player* get_votee ();
private:
	Player* voter;
	Player* votee;	
};

class Room {
public:
	Room(string, string);
	bool checkDuplicateRole (string);
	void disMount (string); 
	string get_room_name();
	string get_cycle_status ();
	int get_day_num ();
	void cycle ();	
	int get_joined_players_count ();
	void inc_joined_players_count ();
	vector<Player*> get_players ();
	vector<Mafia*> get_mafias ();
	vector<Villager*> get_villagers ();
	vector<Joker*> get_jokers ();
	vector<Godfather*> get_godfathers ();
	vector<Silencer*> get_silencers ();
	vector<Rouintan*> get_rouintans ();
	vector<Doctor*> get_doctors ();
	vector<Detective*> get_detectives ();
	void list_pushback (string);
	vector<string> get_list();
	void list_clear ();
	void votes_pushback (Vote*);
	vector<Vote*>& get_votes();
	void votes_clear ();
	void immunedbyDoc_pushback (Player*);
	vector<Player*> get_immunedbyDoc();
	void immunedbyDoc_clear ();
	void mutedPlayer_pushback (Player*);
	vector<Player*>& get_mutedPlayer();
	void mutedPlayer_clear ();
private:
	vector<Player*> immunedbyDoc;
	vector<Player*> mutedPlayer;
	vector<Player*> players;
	vector<Vote*> votes;
	vector<string> list;
	vector<Mafia*> mafias;
	vector<Villager*> villagers;
	vector<Joker*> jokers;
	vector<Doctor*> doctors;
	vector<Rouintan*> rouintans;
	vector<Godfather*> godfathers;
	vector<Detective*> detectives;
	vector<Silencer*> silencers;
	string room_name;
	int joined_players_count;
	string current_time; 
	int day_num;
};

#endif