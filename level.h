#include <iostream>
#include <unistd.h>
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include "tile.h"

using namespace std;

class Level{
  private:
    //level data
    Tile tilemap[120][30]; //Map
    int playerX, playerY; //Player position
    int gameSpeed; //how fast game loop will run. Lower means faster.
    int gravityPower; //gravity power
    int jumpHeight; //jump height
    int startingX, startingY; //starting point for player
    bool editMode; //Is game in editor mode?
    bool exit; //Should game exit to menu?
    bool victory; //Player won?

    //###########
    //###TILES###
    //###########
    static const int TILE_LIMIT = 1024;

    string id[TILE_LIMIT];       //id of the tile
    char character[TILE_LIMIT];  //display character of the tile
    int hardness[TILE_LIMIT];    //hardness of the tile
    bool damage[TILE_LIMIT];     //is tile dangerous for player?
    bool start[TILE_LIMIT];      //is tile a starting point?
    bool finish[TILE_LIMIT];     //is tile a finish point?
  public:
    const int LEVEL_X = 120; //Maximal level dimensions
    const int LEVEL_Y = 30;


    Level(int=0, int=0, int=24, int=1, int=7, int=0, int=0, bool=false, bool=true);
    void initIDs();

    //get variables
    bool getExit();
    bool getVictory();
    int getGameSpeed();
    bool getStart(int=0);
    int getPlayerX();
    int getPlayerY();
    int getConstTileLimit();

    string getTileId(int);
    char getTileCharacter(int);
    int getTileHardness(int);
    bool getTileDamage(int);
    bool getTileStart(int);
    bool getTileFinish(int);

    //set variables
    void setExit(bool);
    void setVictory(bool);
    void setEditMode(bool);
    void setGameSpeed(int);
    void setJumpHeight(int);
    void setStartingX(int);
    void setStartingY(int);

    void setTileId(int, string);
    void setTileCharacter(int, char);
    void setTileHardness(int, int);
    void setTileDamage(int, bool);
    void setTileStart(int, bool);
    void setTileFinish(int, bool);

    //tilemap

    void setTileOccupiedByPlayer(int=0);
    void checkStatus();

    //movement
    void moveRight();
    void moveLeft();
    void moveUp();
    void jump();
    void moveDown();

    void gravity();

    //Load/save functions
      //loading
    void loadTiles(string="tiles.txt");
    void loadLevel(string="level.txt");

      //saving
    void saveTiles(string="tiles.txt");
    void saveLevel(string="level.txt");

    //rendering
    void renderLevelFromPositionBWCharsEditor(int=0, int=0, int=1);
    void renderLevelFromPositionBWChars(int=0);

};
