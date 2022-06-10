#include <string>
using namespace std;

class Player {
    private:
        string name;
        int guesses;
        int wins;
    
    public:
        Player(string name);

        string getName(void);

        int getGuesses(void);
        int getWins(void);

        void setGuesses(int num);
        void setWins(int num);
};