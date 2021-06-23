#include "Room.hpp"

bool Room::checkDuplicateRole (string str) {
	bool bl = false;
	for (int i = 0; i < players.size (); i++) {
		if (players[i] -> get_role () == str)
			bl = true;
	}
	if (!bl)
		return false;
		else
			return true;
}

void Room::disMount (string str) {
	vector<Player*> wantedData;
	for (int i = 0; i < players.size (); i++) 
		if (players[i] -> get_role () != str) 
			wantedData.push_back(players[i]);
		else 
			if (str == "Mafia")
				mafias.clear ();
			else if (str == "Villager")
				villagers.clear ();
			else if (str == "GodFather")
				godfathers.clear ();
			else if (str == "Silencer")
				silencers.clear ();
			else if (str == "Detective")
				detectives.clear ();
			else if (str == "Doctor")
				doctors.clear ();
			else if (str == "RouinTan")
				rouintans.clear ();
			else if (str == "Joker")
				jokers.clear ();

	players.clear ();
	players = wantedData;			
}

Room::Room(string str, string _room_name){
	room_name = _room_name;
	istringstream iss(str);
	string word;
	int number;	
	vector<string> duplicateRole;
	while(iss>>word  && iss>>number){
		word.erase(word.begin());
		if (word == "Mafia") {
			if (!(checkDuplicateRole(word))) 
				duplicateRole.push_back ("Mafia");
			else
				disMount(word);
			for(int i=0;i<number;i++) {
				mafias.push_back(new Mafia());
				players.push_back(mafias[mafias.size()-1]);
				players[players.size()-1] -> setRole ("Mafia");
			}
		} else if (word == "Villager") {
			if (!(checkDuplicateRole(word)))
				duplicateRole.push_back ("Villager");
			else 
				disMount(word);
			for(int i=0;i<number;i++) {
				villagers.push_back(new Villager());
				players.push_back(villagers[villagers.size()-1]);
				players[players.size()-1] -> setRole ("Villager");
			}
		} else if (word == "GodFather") {
			if (!(checkDuplicateRole(word)))
				duplicateRole.push_back ("GodFather");
			else
				disMount(word);
			for(int i=0;i<number;i++) {
			godfathers.push_back(new Godfather());
			players.push_back(godfathers[godfathers.size()-1]);
			players[players.size()-1] -> setRole ("GodFather");
			}
		} else if (word == "Silencer") {
			if (!(checkDuplicateRole(word)))
				duplicateRole.push_back ("Silencer");
			else
				disMount(word);
			for(int i=0;i<number;i++) {
				silencers.push_back(new Silencer());
				players.push_back(silencers[silencers.size()-1]);
				players[players.size()-1] -> setRole ("Silencer");
			}
		} else if (word == "Detective") {
			if (!(checkDuplicateRole(word)))
				duplicateRole.push_back ("Detective");
			else 
				disMount(word);
			for(int i=0;i<number;i++) {
				detectives.push_back(new Detective());
				players.push_back(detectives[detectives.size()-1]);
				players[players.size()-1] -> setRole ("Detective");
			}
		} else if (word == "Doctor") {
			if (!(checkDuplicateRole(word))) 
				duplicateRole.push_back ("Doctor");
			else 
				disMount(word);
			for(int i=0;i<number;i++) {					
				doctors.push_back(new Doctor());	
				players.push_back(doctors[doctors.size()-1]);
				players[players.size()-1] -> setRole ("Doctor");
			}
		} else if (word == "RouinTan") {
			if (!(checkDuplicateRole(word)))
				duplicateRole.push_back ("RouinTan");
			else 
				disMount(word);
			for(int i=0;i<number;i++) {
				rouintans.push_back(new Rouintan());
				players.push_back(rouintans[rouintans.size()-1]);		
				players[players.size()-1] -> setRole ("RouinTan");				
			}
		} else if (word == "Joker") {
			if (!(checkDuplicateRole(word)))
				duplicateRole.push_back ("Joker");
			else 
				disMount(word);
			for(int i=0;i<number;i++) {
				jokers.push_back(new Joker());
				players.push_back(jokers[jokers.size()-1]);
				players[players.size()-1] -> setRole ("Joker");
			}
		}		
	}
	day_num = 1;
	current_time = "Day";	
}
vector<string> Room::get_list () {
	return list;
}
void Room::list_pushback (string str) {
	list.push_back(str);
}
void Room::list_clear () {
	list.clear ();
}
void Room::votes_pushback (Vote* vote) {
	votes.push_back(vote);
}
vector<Vote*>& Room::get_votes() {
	return votes;
}
void Room::votes_clear () {
	for (int i = 0; i < players.size (); i++)
		players[i] -> clear_player_votes ();

	votes.clear ();
}
string Room::get_room_name(){
	return room_name;
}
string Room::get_cycle_status () {
	return current_time;
}
int Room::get_day_num () {
	return day_num;
}
void Room::cycle () {
	if (current_time == "Day")
		current_time = "Night";
		else {
			current_time = "Day";
			day_num++;
		}
}
int Room::get_joined_players_count () {
	return joined_players_count;
}
void Room::inc_joined_players_count () {
	joined_players_count++;
}
vector<Player*> Room::get_players () {
	return players;
}
vector<Mafia*> Room::get_mafias () {
	return mafias;
}
vector<Joker*> Room::get_jokers () {
	return jokers;
}
vector<Villager*> Room::get_villagers () {
	return villagers;
}
vector<Godfather*> Room::get_godfathers () {
	return godfathers;
}
vector<Silencer*> Room::get_silencers () {
	return silencers;
}
vector<Rouintan*> Room::get_rouintans () {
	return rouintans;
}
vector<Doctor*> Room::get_doctors () {
	return doctors;
}
vector<Detective*> Room::get_detectives () {
	return detectives;
}
void Room::immunedbyDoc_pushback (Player* player) {
		immunedbyDoc.push_back(player);
}
vector<Player*> Room::get_immunedbyDoc() {
	return immunedbyDoc;
}
void Room::immunedbyDoc_clear () {
	immunedbyDoc.clear ();
}
void Room::mutedPlayer_pushback (Player* player) {
	mutedPlayer.push_back(player);
}
vector<Player*>& Room::get_mutedPlayer() {
	return mutedPlayer;
}
void Room::mutedPlayer_clear () {
	mutedPlayer.clear ();
}
////////////////////////////////////////////


Vote::Vote (string _voter, string _votee, Room*& current_room) {
	for ( int i = 0; i < current_room -> get_players ().size (); i++ ) {
		if  (current_room -> get_players ()[i] -> get_player_name () == _voter )
			voter = current_room -> get_players ()[i];
		else if  (current_room -> get_players ()[i] -> get_player_name () == _votee )
			votee = current_room -> get_players ()[i];
		}
}
Player* Vote::get_voter () {
	return voter;
}
Player* Vote::get_votee () {
	return votee;
}



