#include "level.h"

using namespace std;

Level::Level(int px, int py, int gs, int gp, int jh, int sx, int sy, bool em, bool etm) {
  playerX = px;
  playerY = py;
  gameSpeed = gs;
  gravityPower = gp;
  jumpHeight = jh;
  startingX = sx;
  startingY = sy;
  editMode = em;
  exit = etm;

  //##TEST##

  /*
  tilemap[0][1].setCharacter('#');
  tilemap[0][1].setHardness(2);
  tilemap[0][1].setId("solid_block");
  tilemap[0][28].setCharacter('#');
  tilemap[0][28].setHardness(2);
  tilemap[0][28].setId("solid_block");
  tilemap[1][28].setCharacter('#');
  tilemap[1][28].setHardness(2);
  tilemap[1][28].setId("solid_block");
  tilemap[2][28].setCharacter('#');
  tilemap[2][28].setHardness(2);
  tilemap[2][28].setId("solid_block");
  tilemap[1][25].setCharacter('-');
  tilemap[1][25].setHardness(1);
  tilemap[1][25].setId("semi_solid_block");
  tilemap[2][25].setCharacter('-');
  tilemap[2][25].setHardness(1);
  tilemap[2][25].setId("semi_solid_block");
  */
}

void Level::initIDs() {
  for(int i=0; i<TILE_LIMIT; i++) {
    id[i]="0";
  }
}

//###################
//###GET VARIABLES###
//###################

bool Level::getExit() {
  return exit;
}

bool Level::getVictory() {
  return victory;
}

int Level::getGameSpeed() {
  return gameSpeed;
}

bool Level::getStart(int st) {
  if(st<TILE_LIMIT) {
    return start[st];
  }
  return false;
}

int Level::getPlayerX() {
  return playerX;
}

int Level::getPlayerY() {
  return playerY;
}

int Level::getConstTileLimit() {
  return TILE_LIMIT;
}



string Level::getTileId(int index) {
  return id[index];
}

char Level::getTileCharacter(int index) {
  return character[index];
}

int Level::getTileHardness(int index) {
  return hardness[index];
}

bool Level::getTileDamage(int index) {
  return damage[index];
}

bool Level::getTileStart(int index) {
  return start[index];
}

bool Level::getTileFinish(int index) {
  return finish[index];
}

//###################
//###SET VARIABLES###
//###################

void Level::setExit(bool ex) {
  exit = ex;
}

void Level::setVictory(bool win) {
  victory = win;
}

void Level::setEditMode(bool editor) {
  editMode=editor;
}

void Level::setGameSpeed(int speed) {
  gameSpeed=speed;
}

void Level::setJumpHeight(int height) {
  jumpHeight=height;
}

void Level::setStartingX(int x) {
  startingX=x;
}

void Level::setStartingY(int y) {
  startingY=y;
}




void Level::setTileId(int index, string tID) {
  id[index]=tID;
}

void Level::setTileCharacter(int index, char tChar) {
  character[index]=tChar;
}

void Level::setTileHardness(int index, int tHard) {
  hardness[index]=tHard;
}

void Level::setTileDamage(int index, bool tDMG) {
  damage[index]=tDMG;
}

void Level::setTileStart(int index, bool tStart) {
  start[index]=tStart;
}

void Level::setTileFinish(int index, bool tFinish) {
  finish[index]=tFinish;
}
//#############
//###TILEMAP###
//#############

void Level::setTileOccupiedByPlayer(int tile) {
    tilemap[playerX][playerY].setTile(id[tile], character[tile], hardness[tile], damage[tile], start[tile], finish[tile]);
}

void Level::checkStatus() {
  if(tilemap[playerX][playerY].getDamage()==true&&editMode==false) {
    exit = true;
  }
  else if(tilemap[playerX][playerY].getFinish()==true&&editMode==false) {
    victory = true;
    exit = true;
  }
}
//##############
//###MOVEMENT###
//##############

void Level::moveRight() {
  if((playerX+1)<LEVEL_X) {
    if(tilemap[playerX+1][playerY].getHardness()!=2||editMode==true) {
      playerX++;
      checkStatus();
    }
  }
}

void Level::moveLeft() {
  if((playerX-1)>=0) {
    if(tilemap[playerX-1][playerY].getHardness()!=2||editMode==true) {
      playerX--;
      checkStatus();
    }
  }
}

void Level::moveUp() {
  if((playerY-1)>=0) {
    if(tilemap[playerX][playerY-1].getHardness()!=2||editMode==true) {
      playerY--;
      checkStatus();
    }
  }
}

void Level::moveDown() {
  if((playerY+1)<LEVEL_Y) {
    if(tilemap[playerX][playerY+1].getHardness()==1||editMode==true) {
      playerY++;
      checkStatus();
    }
  }
}

//I don't use moveUp() in jump, beacuse i want to return if player up movement is blocked by something
void Level::jump() {
  if((playerY+1)>=LEVEL_Y) {
    for(int i=0; i<jumpHeight; i++) {
      if((playerY-1)>=0) {
        if(tilemap[playerX][playerY-1].getHardness()!=2||editMode==true) {
          playerY--;
          checkStatus();
          usleep(gameSpeed*1000);
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            moveRight();
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            moveLeft();
          }
        }
      }
      else {
        return;
      }
    }
  }
  else if(tilemap[playerX][playerY+1].getHardness()!=0) {
    for(int i=0; i<jumpHeight; i++) {
      if((playerY-1)>=0) {
        if(tilemap[playerX][playerY-1].getHardness()!=2||editMode==true) {
          playerY--;
          checkStatus();
          usleep(gameSpeed*1000);
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            moveRight();
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            moveLeft();
          }
        }
      }
      else {
        return;
      }
    }
  }
}

void Level::gravity() {
  for(int i=0; i<gravityPower; i++) {
    if((playerY+1)<LEVEL_Y) {
      if(tilemap[playerX][playerY+1].getHardness()==0||editMode==true) {
        playerY++;
        checkStatus();
      }
    }
  }
}

void Level::loadTiles(string fileName) {
  fstream file;
  file.open(fileName, ios::in);
  if(!file.good()) {
    cout<<"Error loading Tiles!"<<endl;
    setExit(true);
    return;
  }

  char tmp;
  for(int i=0; i<TILE_LIMIT; i++) {
    file>>id[i];
    file>>tmp;
    if(tmp=='a') {
      character[i]=' ';
    }
    else {
      character[i]=tmp;
    }
    file>>hardness[i];
    file>>damage[i];
    file>>start[i];
    file>>finish[i];
  }
}

void Level::saveTiles(string fileName) {
  fstream file;
  file.open(fileName, ios::out);
  for(int i=0; i<TILE_LIMIT; i++) {
    file<<id[i]<<endl;
    if(character[i]==' ') {
      file<<'a'<<endl;
    }
    else {
      file<<character[i]<<endl;
    }
    file<<hardness[i]<<endl;
    file<<int(damage[i])<<endl;
    file<<int(start[i])<<endl;
    file<<int(finish[i])<<endl;
  }
}

void Level::saveLevel(string levelName) {
  fstream file;
  file.open(levelName, ios::out);
  file<<startingX<<endl;
  file<<startingY<<endl;
  file<<gameSpeed<<endl;
  file<<jumpHeight<<endl;
  file<<gravityPower<<endl;
  for(int i=0; i<LEVEL_Y; i++) {
    for(int j=0; j<LEVEL_X; j++) {
        file<<tilemap[j][i].getId()<<endl;
    }
  }
}

void Level::loadLevel(string levelName) {
  fstream file;
  file.open(levelName, ios::in);
  if(!file.good()) {
    cout<<"Error Loading Level File!"<<endl;
    usleep(2000000);
    setExit(true);
    return;
  }
  file>>startingX;
  file>>startingY;
  file>>gameSpeed;
  file>>jumpHeight;
  file>>gravityPower;
  for(int i=0; i<LEVEL_Y; i++) {
    for(int j=0; j<LEVEL_X; j++) {
        string tmp;
        file>>tmp;
        tilemap[j][i].setId(tmp);
    }
  }
  for(int k=0; k<255; k++) {
    for(int i=0; i<LEVEL_Y; i++) {
      for(int j=0; j<LEVEL_X; j++) {
          if(tilemap[j][i].getId()==id[k]) {
            tilemap[j][i].setTile(id[k], character[k], hardness[k], damage[k], start[k], finish[k]);
          }
      }
    }
  }
  playerX=startingX;
  playerY=startingY;
}

void Level::renderLevelFromPositionBWCharsEditor(int startingPos, int selectedTile, int offset) {
  string output="";
  cout<<"\033[H\033[J"; //ASCII escape code for clear screen
  for(int i=0; i<30; i++) {
    for(int j=0; j<120; j++) {
      if(i==playerY&&j==playerX) {
        output.push_back('p');
      }
      else {
        output.push_back(tilemap[j][i].getCharacter());
      }
    }
    output.push_back('\n');
  }
  cout<<output;
  cout<<endl;
  cout<<"Selected Tile: ";
  cout<<character[selectedTile]<<" ("<<selectedTile<<")";
  cout<<"\n";
  cout<<"Scroll offset: "<<offset;
  std::cout.flush();
  usleep(5000);
}

void Level::renderLevelFromPositionBWChars(int startingPos) {
  string output="";
  cout<<"\033[H\033[J"; //ASCII escape code for clear screen
  for(int i=0; i<30; i++) {
    for(int j=0; j<120; j++) {
      if(i==playerY&&j==playerX) {
        output.push_back('p');
      }
      else {
        output.push_back(tilemap[j][i].getCharacter());
      }
    }
    output.push_back('\n');
  }
  cout<<output;
  usleep(5000);
}
