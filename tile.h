#include <iostream>

using namespace std;

class Tile {
    private:
        char character; //display character
        int hardness;  //0: non-solid, 1: semi-solid, 2: solid
        bool damage; // Deals damage to player?
        bool start; // starting point of level
        bool finish; // ending point of level
        bool player; // is block occupied by player?


    public:
        Tile(char=' ', int=0, bool=0, bool=0, bool=0, bool=0);
        char getCharacter();
        int getHardness();
        bool getDamage();
        bool getStart();
        bool getFinish();
        bool getPlayer();

        //#######################

        void setCharacter(char);
        void setHardness(int);
        void setDamage(bool);
        void setStart(bool);
        void setFinish(bool);
        void setPlayer(bool);

        //#######################

        void setTile(char=' ', int=0, bool=0, bool=0, bool=0, bool=0);
};
