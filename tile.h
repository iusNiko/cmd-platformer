#include <iostream>

using namespace std;

class Tile {
    private:
        string id; //id of character
        char character; //display character
        int hardness;  //0: non-solid, 1: semi-solid, 2: solid
        bool damage; // Deals damage to player?
        bool start; // starting point of level?
        bool finish; // ending point of level?

    public:
        Tile(string="air", char=' ', int=0, bool=0, bool=0, bool=0);
        string getId();
        char getCharacter();
        int getHardness();
        bool getDamage();
        bool getStart();
        bool getFinish();

        //#######################

        void setId(string);
        void setCharacter(char);
        void setHardness(int);
        void setDamage(bool);
        void setStart(bool);
        void setFinish(bool);

        //#######################

        void setTile(string="air", char=' ', int=0, bool=0, bool=0, bool=0);
};
