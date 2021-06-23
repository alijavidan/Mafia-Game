#include "Player.hpp"

void Player::setRole (string _role) {
	role = _role;
}
string Player::get_role () {
	return role;
}
void Player::add_vote () {
	votes_count++;
}
int Player::get_votes_count () {
	return votes_count;
}
void Player::clear_player_votes () {
	votes_count = 0;
}
void Player::immune_player () {
	immune = true;
}
void Player::mute_player () {
	mute_status = true;
}
bool Player::get_immune_status () {
	return immune;
}
void Player::notimmuneSetter () {
	immune = false;
}
void Player::notmuteSetter () {
	mute_status = false;
}
bool Player::get_mute_status () {
	return mute_status;
}
string Player::get_player_name() {
	return player_name;
}
void Player::nameSetter (string _player_name) {
	player_name = _player_name;
}
bool Player::get_death_status() {
	return death_status;
}
void Player::kill () {
	death_status = true;
}
void Player::notRouintanAnymore () {
}
bool Player::getRouintanStatus () {
}

//

string Mafia::get_player_name() {
	return player_name;
}
string Villager::get_player_name() {
	return player_name;
}
string Joker::get_player_name() {
	return player_name;
}
string Detective::get_player_name() {
	return player_name;
}
string Doctor::get_player_name() {
	return player_name;
}
string Godfather::get_player_name() {
	return player_name;
}
string Silencer::get_player_name() {
	return player_name;
}
string Rouintan::get_player_name() {
	return player_name;
}
//

bool Mafia::get_death_status() {
	return death_status;
}
bool Villager::get_death_status() {
	return death_status;
}
bool Joker::get_death_status() {
	return death_status;
}
bool Silencer::get_death_status() {
	return death_status;
}
bool Godfather::get_death_status() {
	return death_status;
}
bool Doctor::get_death_status() {
	return death_status;
}
bool Detective::get_death_status() {
	return death_status;
}
bool Rouintan::get_death_status() {
	return death_status;
}
//

Joker::Joker () {
	 death_status = false;
	 mute_status = false;
	 immune = false;
}
Mafia::Mafia () {
	 death_status = false;
	 mute_status = false;
	 immune = false;
}
Villager::Villager () {
	 death_status = false;
	 mute_status = false;
	 immune = false;
}
Detective::Detective () {
	 death_status = false;
	 mute_status = false;
	 immune = false;
	 has_detected = false;
}
Doctor::Doctor ()  {
	 death_status = false;
	 mute_status = false;
	 immune = false;
	 has_healed = false;
}
Rouintan::Rouintan ()  {
	 death_status = false;
	 mute_status = false;
	 immune = false;
	 rouintanStatus = true;
}
Godfather::Godfather ()  {
	 death_status = false;
	 mute_status = false;
	 immune = false;
}
Silencer::Silencer ()  {
	 death_status = false;
	 mute_status = false;
	 immune = false;
	 has_silenced = false;
}
//

void Mafia::kill () {
	death_status = true;
}
void Villager::kill () {
	death_status = true;
}
void Joker::kill () {
	death_status = true;
}
void Silencer::kill () {
	death_status = true;
}
void Godfather::kill () {
	death_status = true;
}
void Doctor::kill () {
	death_status = true;
}
void Detective::kill () {
	death_status = true;
}
void Rouintan::kill () {
	death_status = true;
}
//	

void Doctor::doHeal() {
	if (!has_healed)
		has_healed = true;
		else
			 throw alreadyHealed ();
}
void Silencer::doSilence () {	
	if (!has_silenced)
		has_silenced = true;
		else
			 throw alreadySilenced ();
}
void Detective::doDetect () {
	if (!has_detected)
		has_detected = true;
		else
		 throw alreadyAsked ();
}
void Rouintan::notRouintanAnymore () {
	rouintanStatus = false;
}
bool Rouintan::getRouintanStatus () {
	return rouintanStatus;
}
