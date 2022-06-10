#include <string>
#include "player.h"
using namespace std;

Player::Player(string name) {
    this->name = name;
    this->guesses = 0;
    this->wins = 0;
}

string Player::getName() {
    return this->name;
}

int Player::getGuesses() {
    return this->guesses;
}

int Player::getWins() {
    return this->wins;
}

void Player::setGuesses(int num) {
    this->guesses = num;
}

void Player::setWins(int num) {
    this->wins = num;
}