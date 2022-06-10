#include <string>
#include "player.h"
using namespace std;

class Wordle {
    private:
        string words[2309];
        string guesses[12947];
        string word;

    public:
        Wordle();

        void chooseWord();
        string getWord();

        void start();
        void stop();
        void play(Player player);
        string processGuess(string guess);
};