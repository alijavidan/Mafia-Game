#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Exceptions.hpp"

using namespace std;

class Player {
protected:
	string player_name;
	bool death_status;
	bool mute_status;
	string role;
	int votes_count;
	bool immune;
public:
	void nameSetter (string);
	void setRole (string);
	string get_role ();
	void add_vote ();
	int get_votes_count ();
	void clear_player_votes ();
	void immune_player ();
	void mute_player ();
	bool get_immune_status ();
	void notimmuneSetter ();
	bool get_mute_status ();
	void notmuteSetter ();
	//
	string get_player_name ();
	bool get_death_status ();
	void kill ();
	//
	virtual void notRouintanAnymore ();
	virtual bool getRouintanStatus ();
};
class Mafia : public Player {
public:
	Mafia ();
	string get_player_name ();
	bool get_death_status ();
	void kill ();
};
class Villager : public Player {
public:
	Villager ();
	string get_player_name ();
	bool get_death_status ();
	void kill ();
};
class Joker : public Player {
public:
	Joker ();
	string get_player_name ();
	bool get_death_status ();
	void kill ();
};
class Godfather : public Mafia {
public:
	Godfather ();
	string get_player_name ();
	bool get_death_status ();
	void kill ();
};
class Silencer : public Mafia {
public:
	Silencer ();
	string get_player_name ();
	bool get_death_status ();
	void kill ();
	void doSilence ();
private:
	bool has_silenced;
};
class Rouintan : public Villager {
public:
	Rouintan ();
	string get_player_name ();
	bool get_death_status ();
	void kill ();
	void notRouintanAnymore ();
	bool getRouintanStatus ();
private :
	bool rouintanStatus;
};
class Doctor : public Villager {
public:
	Doctor ();
	string get_player_name ();
	bool get_death_status ();
	void kill ();
	void doHeal ();
private:
	bool has_healed; 
};
class Detective : public Villager {
public:
	Detective ();
	string get_player_name ();
	bool get_death_status ();
	void kill ();
	void doDetect ();
private:
	bool has_detected;
};

#endif