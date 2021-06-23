#include "functions.hpp"

bool numberChecker ( const string& s ) {
    return ( strspn( s.c_str(), "-.0123456789" ) == s.size() );
}

void dashChecker ( string str ) {
	if ( str[0] != '-' )
		throw invalidRoleFormat ();
}

void roleChecker ( string str ) {
	if ( str != "Joker" && str != "Villager" && str != "Detective" && str != "Doctor" && str != "RouinTan" && str != "Mafia" && str != "GodFather" && str != "Silencer" )
		throw invalidRole ();
}

void checkRoom ( string str, vector<Room*> &rooms, Room* &current_room, string type ) {
	bool flag = false;
	for ( int i = 0; i < rooms.size (); i++ )
		if ( str == rooms[i] -> get_room_name() )
			flag = true;
	
	if ( type == "validate")
		if (!flag)
			throw invalidRoom ();
		else if ( type == "duplicate")
			if (flag) 
				throw duplicateRoom ();
}

string MafiaVillager (string str) {
	if (str == "GodFather" || str == "Silencer")
		return "Mafia";
	else if (str == "Doctor" || str == "Detective" || str == "RouinTan")
		return "Villager";
	else 
		return "";
}

void ratioCheck (string str) {
	istringstream iss(str);
	int MafiaCount = 0;
	int VillagerCount = 0;
	int OtherMafiaRolesCount = 0;
	int OtherVillagerRolesCount = 0;
	string word;
	int number;
	while (iss>>word) {
		word.erase(word.begin());
		if (word == "Mafia") {
			iss >> number;
			MafiaCount += number;
		} else if (word == "Villager") {
			iss >> number;
			VillagerCount += number;
		} else if (MafiaVillager(word) == "Mafia") { 
			iss >> number;
			OtherMafiaRolesCount += number;
		} else {
			iss >> number;
			OtherVillagerRolesCount += number; 
		}
	}
	if (OtherMafiaRolesCount > MafiaCount)
		throw invalidRatio ();
	else if (OtherVillagerRolesCount > VillagerCount) 
		throw invalidRatio ();
}

int countAlives (Room* &current_room, string whichCase) {
	int count = 0;
	for (int i = 0; i < current_room -> get_players ().size (); i++)
		if ( current_room -> get_players ()[i] -> get_role () == whichCase || MafiaVillager (current_room -> get_players ()[i] -> get_role ()) == whichCase )
			if (!(current_room -> get_players ()[i] -> get_death_status ()))
					count++;
	
	return count;
}

void checkGameStatus (Room* &current_room) {
	if ( current_room != NULL ) {
		if ( countAlives(current_room, "Mafia") == 0 ) {
			cout << "Victory!\n";
			throw exit_exception ();
		} else if (countAlives(current_room, "Villager") <= countAlives(current_room, "Mafia")) {
			cout << "Loose!\n";
			throw exit_exception ();
		}
	}
}

void create_room (vector<Room*> &rooms, Room* &current_room) {

	string room_name;

	cin >> room_name;

	string str;

	try {	
		getline ( cin , str );
	 	checkRoom (room_name, rooms, current_room, "duplicate");
	} catch ( duplicateRoom dR ) {
		cout << "Duplicate Room\n";
		return;
	}

	istringstream MyParser ( str );

	string word;

	for ( int c = 1; MyParser >> word; c++ ) {

		if ( c % 2 == 0 ) {
			
			try {
			if ( !numberChecker (word) ) {
				if ( word[0] == '-' )
					throw invalidFormat ();
				else
					throw invalidNumberFormat ();
			}
			} catch ( invalidFormat iF ) {
				cout << "Invalid Format\n";
				return;
			} catch ( invalidNumberFormat iNF ) {
				cout << "Invalid Number Format\n";
				return;
			}

			} else {

				try {

					if ( numberChecker (word) ) 
						throw invalidFormat ();
					
					dashChecker (word);

					word.erase ( word.begin () );

					roleChecker (word);
						
				} catch ( invalidFormat iF ) {
					cout << "Invalid Format\n";					
					return;
				} catch ( invalidRole iR ) {
					cout << "Invalid Role\n";
					return;
				} catch ( invalidRoleFormat iRF ) {
					cout << "Invalid Role Format\n";
					return;
				}

			}

	}
	try {
		ratioCheck (str);
	} catch (invalidRatio iR) {
		cout << "Invalid Roles' Ratio Format\n";
		return;
	}
	rooms.push_back(new Room(str, room_name));
	current_room = rooms[rooms.size()-1];

	checkGameStatus (current_room);
}

void switch_room (vector<Room*> &rooms, Room* &current_room) {

	string str;

	cin >> str;

	try {
		
		checkRoom (str, rooms, current_room, "validate");

		for (int i=0;i<rooms.size();i++)
			if(rooms[i] -> get_room_name() == str)
				current_room = rooms[i];

	} catch ( invalidRoom iR ) {

		cout << "Invalid room name\n";

	}


}

void randomize (vector<Room*> &rooms, Room* &current_room){
	vector<int> db;
	int random;
	while (db.size() != current_room -> get_players ().size ()) {
		bool duplicate = true;
		while (duplicate) {
			random = rand () % current_room -> get_players ().size ();
			bool bl = false;
			for ( int i = 0; i < db.size (); i++ )
				if (db[i] == random)
					bl = true;
			if (!bl)
				duplicate = false; 
		}
		db.push_back (random);
		for (int j=0;j<current_room -> get_players ().size();j++)
			if(current_room -> get_players ()[j] -> get_player_name() == ""){
				current_room -> get_players ()[j] -> nameSetter(current_room -> get_list ()[random]);
				cout << current_room -> get_players ()[j] -> get_player_name () << " is " << current_room -> get_players ()[j] -> get_role () << endl;
				break;
			}
	}
	cout << "Day "<< current_room -> get_day_num () << endl;
}
void join (vector<Room*> &rooms, Room* &current_room) {
	string line;
	string word;
	getline(cin,line);
	istringstream iss(line);		
	line.erase(line.begin());
	while(iss>>word) {
		current_room -> inc_joined_players_count ();
		try {
			if(current_room -> get_joined_players_count () > current_room -> get_players ().size())
				throw manyUsers();
			current_room -> list_pushback(word);
		} catch (manyUsers mU){
			cout<<"many users\n";
			return;	
		}
	}
	if (current_room -> get_joined_players_count () == current_room -> get_players ().size ()) {
		randomize(rooms, current_room);
		current_room -> list_clear ();
	}
}

void checkUser (string player_name, Room* &current_room) {
	bool bl = false;
	for ( int i = 0; i < current_room -> get_players ().size (); i++ )
		if ( current_room -> get_players ()[i] -> get_player_name () == player_name )
			bl = true;
	if (!bl)
		throw invalidUser ();
}

void voteAllowance (string player_name, Room* &current_room) {
	for (int i = 0; i < current_room -> get_players ().size (); i++)
		if (current_room -> get_players ()[i] -> get_player_name () == player_name)
			if ((current_room -> get_players ()[i] -> get_role () != "Mafia" && MafiaVillager(current_room -> get_players ()[i] -> get_role ()) != "Mafia") || current_room -> get_players ()[i] -> get_role () == "Villager")
				throw notAllowed ();
}

bool compareLogin (Player* player1, Player* player2) { 
	return (player1 -> get_player_name ().compare (player2 -> get_player_name ()) < 0);
}

void end_vote (vector<Room*> &rooms, Room* &current_room) {
	for (int i = 0; i < current_room -> get_votes ().size (); i++ )
		for (int j = 0; j < current_room -> get_players ().size (); j++)
			if ( current_room -> get_players ()[j] -> get_player_name () == current_room -> get_votes ()[i] -> get_votee () -> get_player_name () )
				current_room -> get_players ()[j] -> add_vote ();
	
	Player* player = current_room -> get_players ()[0];
	vector<Player*> candidatePlayers;

	for (int i = 0; i < current_room -> get_players ().size (); i++ )
		if (current_room -> get_players ()[i] -> get_votes_count () > player -> get_votes_count ())
			player = current_room -> get_players ()[i];

	for (int i = 0; i < current_room -> get_players ().size (); i++ )
		if (current_room -> get_players ()[i] -> get_votes_count () == player -> get_votes_count () )
			candidatePlayers.push_back(current_room -> get_players ()[i]);

	int randPlayer = rand () % candidatePlayers.size ();
	
	player = candidatePlayers[randPlayer];

	candidatePlayers.clear ();

	if (!(player -> get_immune_status ()))
		if (!(player -> get_role () == "RouinTan") && !(player -> getRouintanStatus ()))
			player -> kill ();
		else 
			player -> notRouintanAnymore ();

	if(player -> get_role () == "Joker" && player -> get_death_status () && current_room -> get_cycle_status () == "Day")
		throw jokerWon ();
	
	if (current_room -> get_cycle_status () == "Day")
		for (int i = 0; i < current_room -> get_mutedPlayer ().size (); i++)
			current_room -> get_mutedPlayer ()[i] -> notmuteSetter ();

	if (current_room -> get_cycle_status () == "Day") {
		if (player -> get_death_status ())
		cout << "Died " << player -> get_player_name () << endl;
	} else  
		cout << "Mafia try to kill " << player -> get_player_name () << endl;

	current_room -> cycle ();
	cout << current_room -> get_cycle_status () << " " << current_room -> get_day_num () << endl;

	for (int i = 0; i < current_room -> get_mutedPlayer ().size (); i++)
	    for (int j = 0; j < current_room -> get_mutedPlayer ().size (); j++)
	        if (current_room -> get_mutedPlayer ()[i] == current_room -> get_mutedPlayer ()[j])
	            if (i != j)
	                current_room -> get_mutedPlayer ().erase(current_room -> get_mutedPlayer ().begin()+i);

	 sort (current_room -> get_mutedPlayer ().begin (), current_room -> get_mutedPlayer ().end (), compareLogin);

	if (current_room -> get_cycle_status () == "Day") 
		if (current_room -> get_day_num () >= 2) { 
			if (current_room -> get_silencers ().size () != 0)
				for (int i = 0; i < current_room -> get_mutedPlayer ().size (); i++)
					cout << "Silenced " << current_room -> get_mutedPlayer ()[i] -> get_player_name () << endl; 
	
	if (!(player -> get_immune_status ()))
		cout << "Killed " << player -> get_player_name () << endl;
	}

	current_room -> immunedbyDoc_clear ();
	if (current_room -> get_cycle_status () == "Night")
		current_room -> mutedPlayer_clear ();
	for (int i = 0; i < current_room -> get_immunedbyDoc ().size (); i++)
		current_room -> get_immunedbyDoc ()[i] -> notimmuneSetter ();

	current_room -> votes_clear();

	checkGameStatus (current_room);
}

void checkDeathStatus (string player_name, Room* &current_room) {
	for (int i = 0;i< current_room -> get_players ().size (); i++)
		if (current_room -> get_players ()[i] -> get_player_name () == player_name)
			if (current_room -> get_players ()[i] -> get_death_status ())
				throw userDead ();
}

void checkMuteStatus (string player_name, Room* &current_room) {
	for ( int i = 0; i < current_room -> get_players ().size (); i++ )
		if ( current_room -> get_players ()[i] -> get_player_name () == player_name )
			if ( current_room -> get_players ()[i] -> get_mute_status () )
				throw muteUser ();
}

void vote (vector<Room*> &rooms, Room* &current_room) { 

	string line;
	getline(cin, line);
	line.erase(line.begin());
	istringstream iss(line);
	string word;
	string voter, votee;
	
	for (int i = 0;iss>>word; i++) {
		try {
			checkUser (word, current_room);
			if (i == 0) {
				if ( current_room -> get_cycle_status () == "Night") 
					voteAllowance (word, current_room);
				if ( current_room -> get_cycle_status () == "Day")
					checkMuteStatus (word, current_room); 	
				voter = word;
				}
				else {
					checkDeathStatus (word, current_room);
					votee = word;
				}
		} catch (invalidUser iU) {
			cout << "User Not Joined\n";
			return;
		}
		catch (notAllowed nA) {
			cout << "This user can not vote\n";
			return;
		}
		catch (userDead uD) {
			cout << "User already died\n";
			return;
		}
		catch (muteUser mU) {
			cout << "This user has been silenced before\n";
			return;
		}
	}

	current_room -> votes_pushback(new Vote (voter, votee, current_room)); 

	for (int i = 0; i < current_room -> get_votes ().size () - 1; i++)
		if (current_room -> get_votes ()[i] -> get_voter () == current_room -> get_votes ()[current_room -> get_votes ().size ()-1] -> get_voter () )
			current_room -> get_votes ().erase(current_room -> get_votes ().begin()+i);

	if (current_room -> get_cycle_status () == "Night" && current_room -> get_votes ().size () == countAlives (current_room, "Mafia")) 
		end_vote (rooms, current_room);
}

void heal (Room* &current_room) {
	string line;
	getline (cin,line);
	line.erase(line.begin());
	istringstream iss(line);
	string healer, target;
	iss >> healer >> target;

	try {
		bool bl = false;
		for ( int i = 0; i < current_room -> get_doctors ().size (); i++)
			if (current_room -> get_doctors ()[i] -> get_player_name () == healer) {
				bl = true;
				if (!(current_room -> get_doctors ()[i] -> get_death_status ())) 
					try {
						for (int j = 0; j < current_room -> get_players ().size (); j++)
							if (current_room -> get_players ()[j] -> get_player_name () == target)
								if (current_room -> get_players ()[j] -> get_death_status ()) 
									throw deadUser ();
								else { 
									current_room -> get_players ()[j] -> immune_player ();
									current_room -> immunedbyDoc_pushback(current_room -> get_players ()[j]);
									current_room -> get_doctors ()[i] -> doHeal ();
								}
					} catch (alreadyHealed aH) {
						cout << "Doctor has already healed\n";
						return;
					}
				else 
					throw unableUser ();
			}
		if (!bl)
			throw unableUser ();

	} catch (deadUser dU) {
		cout << "Person is dead\n";
	} catch (unableUser uU) {
		cout << "User can not heal\n";
	} 

}

void detect (Room* &current_room) {
	
	string line;
	getline (cin,line);
	line.erase(line.begin());
	istringstream iss(line);
	string detective, suspect;
	iss >> detective >> suspect;

	try {
		bool bl = false;
		for ( int i = 0; i < current_room -> get_detectives ().size (); i++)
			if (current_room -> get_detectives ()[i] -> get_player_name () == detective) {
				bl = true;
				if (!(current_room -> get_detectives ()[i] -> get_death_status ())) 
					try {
						for (int j = 0; j < current_room -> get_players ().size (); j++)
							if (current_room -> get_players ()[j] -> get_player_name () == suspect)
								if (current_room -> get_players ()[j] -> get_death_status ()) 
									throw deadUser ();
								else {
									if ((MafiaVillager(current_room -> get_players ()[j] -> get_role ()) == "Mafia" || current_room -> get_players ()[j] -> get_role () == "Mafia") && current_room -> get_players ()[j] -> get_role () != "GodFather")
										cout << "Yes\n";
									else 
										cout << "No\n";	

									current_room -> get_detectives ()[i] -> doDetect ();
								}
					} catch (alreadyAsked aA) {
						cout << "Detective has already asked\n";
						return;
					}
				else 
					throw unableUser ();
			}
		if (!bl)
			throw unableUser ();

	} catch (deadUser dU) {
		cout << "Person is dead\n";
	} catch (unableUser uU) {
		cout << "User can not ask\n";
	} 

}

void silence (Room* &current_room) {
	
	string line;
	getline (cin,line);
	line.erase(line.begin());
	istringstream iss(line);
	string silencer, target;
	iss >> silencer >> target;

	try {
		bool bl = false;
		for ( int i = 0; i < current_room -> get_silencers ().size (); i++)
			if (current_room -> get_silencers ()[i] -> get_player_name () == silencer) {
				bl = true;
				if (!(current_room -> get_silencers ()[i] -> get_death_status ())) 
					try {
						for (int j = 0; j < current_room -> get_players ().size (); j++)
							if (current_room -> get_players ()[j] -> get_player_name () == target)
								if (current_room -> get_players ()[j] -> get_death_status ()) 
									throw deadUser ();
								else { 
									current_room -> get_players ()[j] -> mute_player ();
									current_room -> mutedPlayer_pushback(current_room -> get_players ()[j]);
									current_room -> get_silencers ()[i] -> doSilence ();
								}
					} catch (alreadySilenced aS) {
						cout << "Silencer has already silenced\n";
						return;
					}
				else 
					throw unableUser ();
			}
		if (!bl)
			throw unableUser ();
		
	} catch (deadUser dU) {
		cout << "Person is dead\n";
	} catch (unableUser uU) {
		cout << "User can not silence\n";
	} 

}

void get_room_state (Room* &current_room) {
	cout << "Mafia = " << countAlives (current_room, "Mafia") << endl;
	cout << "Villager = " << countAlives (current_room, "Villager") << endl;
}

void selection ( string str, vector<Room*> &rooms, Room* &current_room) {
	try {
		if ( str == "Create_room" )
			create_room (rooms, current_room);
		else if ( str == "Switch_room" )
			switch_room (rooms, current_room);
		else if ( str == "Join" )	
			join (rooms, current_room);
		else if ( str == "Vote" )	
			vote (rooms, current_room);
		else if ( str == "End_vote" )	
			end_vote (rooms, current_room);
		else if ( str == "Heal" )	
			heal (current_room);
		else if ( str == "Silence" )	
			silence (current_room);
		else if ( str == "Detect" )	
			detect (current_room);
		else if ( str == "Get_room_state" )	
			get_room_state (current_room);
		else 
			throw wrongKeyword ();	
	} catch ( wrongKeyword& wK ) {

		cout << "Wrong Keyword\n";
		getline ( cin , str );

	}
}

