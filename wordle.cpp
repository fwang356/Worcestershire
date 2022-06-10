#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <ctime>
#include "wordle.h"
#ifndef PLAYER_H
#define PLAYER_H
#endif
using namespace std;

Wordle::Wordle()
{
    string line;
    int index = 0;

    ifstream file("words.txt");
    while (getline(file, line)) {
        this->words[index] = line;
        this->guesses[index] = line;
        index++;
    }
    file.close();

    ifstream filee("guesses.txt");
    while (getline(filee, line)) {
        this->guesses[index] = line;
        index++;
    }
    filee.close();
}

void Wordle::chooseWord() {
    srand((unsigned int)time(NULL));
    int seed = rand() % 2039;
    this->word = words[seed];
}

string Wordle::getWord() {
    return this->word;
}


string Wordle::processGuess(string guess)
{
    string out = "";
    string word = this->getWord();
    bool found = false;

    transform(guess.begin(), guess.end(), guess.begin(), ::toupper);

    for (int i = 0; i < 10368; i++) {
        if (guess == this->guesses[i]) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        return out = "INVALID";
    }
    

    if (guess == word)
    {
        return out = "CORRECT";
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            if (word[i] == guess[i])
            {
                out += "G";
            }
            else if (word.find(guess[i]) != -1)
            {
                out += "Y";
            }
            else
            {
                out += "_";
            }
        }
    }
    return out;
}

void Wordle::start()
{
    string name;

    cout << "Starting up Worcestershire..." << '\n';

    cout << "Enter Name: ";
    cin >> name;
    Player player = Player(name);
    this->play(player);
}

void Wordle::play(Player player)
{
    string guess;
    string word;
    string out;
    string again;

    this->chooseWord();
    word = this->getWord();

    while (player.getGuesses() < 6)
    {
        cout << "Guess #" << player.getGuesses() + 1 << ": ";
        cin >> guess;
        out = processGuess(guess);
        while (out == "INVALID") {
            cout << "Invalid guess. Please try again. \nGuess #" << player.getGuesses() + 1 << ": ";
            cin >> guess;
            out = processGuess(guess);
        }
        if (out == "CORRECT")
        {
            break;
        }

        player.setGuesses(player.getGuesses() + 1);
        cout << out << '\n'
             << "You have " << 6 - player.getGuesses() << " guesses remaining." << '\n';
    }

    if (out == "CORRECT")
    {
        player.setWins(player.getWins() + 1);
        cout << "Congrats! You successfully guessed " << word << "! \nPlay Again? (Y/N): ";
        cin >> again;
    }
    else
    {
        cout << "You are literally so bad. The word was TRASH just like you. Just kidding, the actual word was "
             << word << ". \nPlay again? (Y/N): ";
        cin >> again;
    }

    while (again != "y" && again != "Y" && again != "N" && again != "n")
    {
        cout << "Please enter Y or N. Play again? (Y/N): ";
    }

    if (again == "y" || again == "Y")
    {
        player.setGuesses(0);
       this->play(player);
    }
}