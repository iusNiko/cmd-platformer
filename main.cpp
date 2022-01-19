#include <cstdio>
#include <stdio.h>

#include <unistd.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <X11/Xlib.h>
#include <limits>
#include "level.h"

using namespace std;

Level l;
int selectedTile;
int selection;
int afterExit;
int offset=1;
string levelFileName;

void gameLoop() {
  while(!l.getExit()) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      l.moveRight();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      l.moveLeft();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      l.jump();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      l.moveDown();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      l.setExit(true);
    }

    l.gravity();
    usleep(l.getGameSpeed()*1000);
  }
  return;
}

void editorLoop() {
  l.setEditMode(true);
  while(!l.getExit()) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      l.moveRight();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      l.moveLeft();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      l.moveUp();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      l.moveDown();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
      if((selectedTile+offset)<l.getConstTileLimit()) selectedTile+=offset;
      else selectedTile = 0;
      usleep(120000);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
      if((selectedTile-offset)>=0) selectedTile-=offset;
      else selectedTile = l.getConstTileLimit()-1;
      usleep(120000);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
      l.setTileOccupiedByPlayer(selectedTile);
      if(l.getStart(selectedTile)==true) {
        l.setStartingX(l.getPlayerX());
        l.setStartingY(l.getPlayerY());
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
      l.saveLevel(levelFileName);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
      l.setExit(true);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
      offset = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
      offset = 2;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
      offset = 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
      offset = 4;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
      offset = 5;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
      offset = 6;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
      offset = 7;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
      offset = 8;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
      offset = 9;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
      offset = 0;
    }

    usleep(l.getGameSpeed()*1000);
  }
  l.setEditMode(false);
  return;
}

void tileEditor() {
  while(!l.getExit()) {
    int id;
    int iTMP;
    char cTMP;
    string sTMP;
    bool bTMP;

    std::cin.clear();
    cout<<"\033[H\033[J";
    cout<<"Edit Tile: ";
    std::cout.flush();
    cin>>id;
    cout<<"\033[H\033[J";
    cout<<"Tile ID: "<<l.getTileId(id)<<endl;
    cout<<"Display Character: "<<l.getTileCharacter(id)<<endl;
    cout<<"Hardness: ";
    if(l.getTileHardness(id)==0) {
      cout<<"No collision"<<endl;
    }
    else if(l.getTileHardness(id)==1) {
      cout<<"Semi-solid"<<endl;
    }
    else if(l.getTileHardness(id)==2) {
      cout<<"Solid"<<endl;
    }
    cout<<"Is Tile Dangerous? ";
    if(l.getTileDamage(id)==true) {
      cout<<"yes"<<endl;
    }
    else {
      cout<<"no"<<endl;
    }
    cout<<"Is Tile Start? ";
    if(l.getTileStart(id)==true) {
      cout<<"yes"<<endl;
    }
    else {
      cout<<"no"<<endl;
    }
    cout<<"Is Tile Finish? ";
    if(l.getTileFinish(id)==true) {
      cout<<"yes"<<endl;
    }
    else {
      cout<<"no"<<endl;
    }
    cout<<endl;
    cout<<"#########################"<<endl;
    cout<<"1. Edit ID"<<endl;
    cout<<"2. Edit Displat Character"<<endl;
    cout<<"3. Edit Hardness"<<endl;
    cout<<"4. Edit Damage"<<endl;
    cout<<"5. Edit Start"<<endl;
    cout<<"6. Edit Finish"<<endl;

    cin>>selection;

    cout<<"#########################"<<endl;
    cout<<"Enter new value: "<<endl;

    switch (selection) {
      case 1: cin>>sTMP; l.setTileId(id, sTMP); break;
      case 2: cin>>cTMP; l.setTileCharacter(id, cTMP); break;
      case 3: cin>>iTMP; l.setTileHardness(id, iTMP); break;
      case 4: cin>>bTMP; l.setTileDamage(id, bTMP); break;
      case 5: cin>>bTMP; l.setTileStart(id, bTMP); break;
      case 6: cin>>bTMP; l.setTileFinish(id, bTMP); break;
    }
    l.saveTiles();

    std::cout.flush();
  }
}

void renderLoopBWChars() {
  while(!l.getExit()) {
    l.renderLevelFromPositionBWChars();
  }
  return;
}

void renderLoopBWCharsEditor() {
  while(!l.getExit()) {
    l.renderLevelFromPositionBWCharsEditor(0, selectedTile, offset);
  }
  return;
}

void menu() {
  cout<<"\033[H\033[J";
  cout<<"****MAIN MENU****\n";
  cout<<"1. Start Level\n";
  cout<<"2. Level Editor\n";
  cout<<"3. Settings\n";
  cin>>selection;
  cout<<endl<<selection<<endl;

  if(selection==1){
    cout<<"\033[H\033[J";
    cout<<"Level name: ";
    std::cout.flush();
    cin>>levelFileName;
    l.loadLevel(levelFileName);

    std::thread renderThread(renderLoopBWChars);
    std::thread gameThread(gameLoop);

    renderThread.join();
    gameThread.join();
  }
  else if(selection==2) {
    cout<<"\033[H\033[J";
    cout<<"****EDITOR MENU****\n";
    cout<<"1. Create New Level\n";
    cout<<"2. Load Existing Level\n";
    cout<<"3. Edit Tiles\n";
    std::cout.flush();
    cin>>selection;

    if(selection==1) {
      int tmp;
      cout<<"Level filename: ";
      cin>>levelFileName;
      cout<<"\nGame Speed: ";
      cin>>tmp;
      l.setGameSpeed(tmp);
      cout<<"\nJump Height: ";
      cin>>tmp;
      l.setJumpHeight(tmp);

      std::thread editorRenderThread(renderLoopBWCharsEditor);
      std::thread editorThread(editorLoop);

      editorRenderThread.join();
      editorThread.join();
    }
    else if(selection==2) {
      cout<<"Level filename: ";
      std::cout.flush();
      cin>>levelFileName;

      l.loadLevel(levelFileName);

      std::thread editorRenderThread(renderLoopBWCharsEditor);
      std::thread editorThread(editorLoop);

      editorRenderThread.join();
      editorThread.join();
    }
    else if(selection==3) {
      tileEditor();
    }
  }
  return;
}

int main() {
  XInitThreads();

  l.loadTiles();

  while(true) {
    if(l.getExit()==true) {
      usleep(5000);
      l.setExit(false);
      menu();
    }
    while(!l.getExit()) {
      usleep(200000);
    }

    if(l.getVictory()==true) {
      l.setVictory(false);
      cout<<"\033[H\033[J";
      cout<<"You Won!"<<endl;
      cout<<"Press 'Enter' to continue"<<endl;
      cin>>afterExit;
      std::cin.clear();
      std::cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
    }
    else {
      cout<<"\033[H\033[J";
      cout<<"Game Over!"<<endl;
      cout<<"Press 'Enter' to continue"<<endl;
      cin>>afterExit;
      std::cin.clear();
      std::cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
    }

    usleep(50000);
  }

  return 0;
}
