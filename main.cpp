#include <iostream>
#include <windows.h>
#include <thread>
#include <cstdio>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include "tile.h"

using namespace std;

int levelX, levelY; //level dimensions
Tile *levelPointer, *renderPointer, *levelArrayAdress; //levelPointer is used to manipulate game world, renderPointer is used by render thread and levelArrayAdress is used to reset first and second pointer to level[0][0] adress
int *tilePointer, *tileArrayAdress;
int playerPos; //player's current position
int startingPos; //player's starting position
int gravity; //gravity strength
int jumpHeight; //how high can player jump
char playerCharacter = 'p'; //character which represents player
int movementRate; //how often can player move
bool gameOver=0, victory=0; //self explanatory
string inputHistory;
const int blockLimit = 255; //max number of blocks possible to load
int debugTime = 0; //variable used to slow down things for debbuging
int tilesCount; //number of loaded tiles
string customTilesFilename; //file name of custom tiles file
string levelFileName; //file name of level you want to load
int selectedTile; //Tile selected in editor
bool editMode; //is edit mode on?

//this arrays contain loaded blocks' properties
char character[blockLimit]; //display character
int hardness[blockLimit];  //0: non-solid, 1: semi-solid, 2: solid
bool damage[blockLimit]; // Deals damage to player?
bool start[blockLimit]; // starting point of level
bool finish[blockLimit]; // ending point of level

//resets levelPointer to &level[0][0]
void resetPointer() {
    levelPointer = levelArrayAdress;
}

//resets renderPointer to &level[0][0]
void resetRenderPointer() {
    renderPointer = levelArrayAdress;
}

//resets tilePointer to &tilemap[0][0]
void resetTilePointer() {
    tilePointer=tileArrayAdress;
}

void tilemapInit() {
    resetTilePointer();
    for(int i=0; i<levelX*levelY; i++) {
        *tilePointer = 0;
        tilePointer++;
    }
}

void render() {
    while(gameOver==false&&victory==false) {
        resetRenderPointer();
        string output="";
        for(int i=0; i<levelY; i++) {
            for(int j=0; j<levelX; j++) {
                if(renderPointer->getPlayer()==true) {
                    output.push_back(playerCharacter);
                }
                else {
                    output.push_back(renderPointer->getCharacter());
                }
                renderPointer++;
            }
            output += "\n";
        }
        system("cls");
        cout<<output;
        if(editMode==true) {
            cout<<"\nSelected tile: "<<character[selectedTile];
        }

    }
}

bool isPlayerKilled() {
    if(gameOver==false) {
        resetPointer();
        levelPointer+=playerPos;
        if(levelPointer->getDamage()==true) {
            return true;
        }
        return false;
    }
    return true;
}

bool isPlayerVictorious() {
    if(victory==false) {
        resetPointer();
        levelPointer+=playerPos;
        if(levelPointer->getFinish()==true) {
            return true;
        }
        return false;
    }
    return false;
}

void moveRight() {
    resetPointer();
    levelPointer += playerPos;
            levelPointer++;
            if(((playerPos+1)%levelX==0)||(levelPointer->getHardness()==2)) {
                levelPointer--;
            }
            else {
                levelPointer->setPlayer(true);
                levelPointer--;
                levelPointer->setPlayer(false);
                playerPos++;
            }
    gameOver = isPlayerKilled();
    victory = isPlayerVictorious();
    resetPointer();
}

void moveLeft() {
    resetPointer();
    levelPointer += playerPos;
            levelPointer--;
            if(((playerPos-1)%levelX==levelX-1)||(levelPointer->getHardness()==2)) {
                levelPointer++;
            }
            else {
                levelPointer->setPlayer(true);
                levelPointer++;
                levelPointer->setPlayer(false);
                playerPos--;
            }
    gameOver = isPlayerKilled();
    victory = isPlayerVictorious();
    resetPointer();
}

void jump() {
    resetPointer();
    levelPointer += playerPos;
            levelPointer += levelX;
            //you can't jump mid-air
            if((levelPointer->getHardness()!=0)||(playerPos+levelX)>=levelX*levelY) {
                for(int i=0; i<jumpHeight; i++) {

                    if((playerPos-levelX)>0) {
                        resetPointer();
                        levelPointer+=playerPos;
                        levelPointer-=levelX;
                        if(levelPointer->getHardness()!=2) {
                            levelPointer->setPlayer(true);
                            levelPointer+=levelX;
                            levelPointer->setPlayer(false);
                            playerPos-=levelX;
                            gameOver = isPlayerKilled();
                            victory = isPlayerVictorious();
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        break;
                    }

                    //movement mid-air
                    if(GetKeyState('D') & 0x8000) {
                        moveRight();
                    }
                    if(GetKeyState('A') & 0x8000) {
                        moveLeft();
                    }
                    //############

                    Sleep(movementRate);
                }
            }
    resetPointer();
}

void moveDown() {
    resetPointer();
        levelPointer+=playerPos;
        if((playerPos+levelX)<(levelX*levelY)) {
            levelPointer+=levelX;
            if(levelPointer->getHardness()==1) {
                levelPointer->setPlayer(true);
                levelPointer-=levelX;
                levelPointer->setPlayer(false);
                playerPos+=levelX;
                gameOver = isPlayerKilled();
                victory = isPlayerVictorious();
            }
        }
    resetPointer();
}

void gameLoop() {
    while(true) {
        //movement
        if(GetKeyState('D') & 0x8000) {
            moveRight();
        }

        if(GetKeyState('A') & 0x8000) {
            moveLeft();
        }

        if(GetKeyState('S') & 0x8000) {
            moveDown();
        }

        if((GetKeyState('W') & 0x8000)||(GetKeyState(VK_SPACE) & 0x8000)) {
            jump();
        }
        //############


        //gravity
        for(int i=0; i<gravity; i++) {
            resetPointer();
            levelPointer+=playerPos;
            if((playerPos+levelX)<(levelX*levelY)) {
                levelPointer+=levelX;
                if(levelPointer->getHardness()==0) {
                    levelPointer->setPlayer(true);
                    levelPointer-=levelX;
                    levelPointer->setPlayer(false);
                    playerPos+=levelX;
                    gameOver = isPlayerKilled();
                }
            }
        }
        //########


        Sleep(movementRate); //without sleep it is too fast
    }
}

void setTile(int id, int pos) {
    resetPointer();
    levelPointer+=pos;
    levelPointer->setTile(character[id], hardness[id], damage[id], start[id], finish[id], false);
    resetPointer();
}

void setTilemap(int id, int pos) {
    resetTilePointer();
    tilePointer+=pos;
    *tilePointer=id;
    resetTilePointer();
}

int readVanillaTiles() {
    fstream file;
    file.open("basetiles.txt", ios::in);
    if(file.good()==false) {
        cout<<"error 1: basetiles.txt loading error!";
        Sleep(3000);
        return 1;
    }
    else {
        string line;
        int field=0, i=0;
        while(getline(file, line)) {
            switch(field){
                case 0: character[i] = line[0]; field=1; break;
                case 1: hardness[i] = std::stoi(line); field=2; break;
                case 2: damage[i] = std::stoi(line); field=3; break;
                case 3: start[i] = std::stoi(line); field = 4; break;
                case 4: finish[i] = std::stoi(line); field = 0; i++; break;
            }
            cout<<"read complete"<<endl;
            Sleep(debugTime);
        }
        cout<<"**Basetiles loaded!**\n";
        Sleep(debugTime*2);
        tilesCount+=i;
    }
    file.close();
    return 0;
}

int readCustomTiles(string fileName) {
    fstream file;
    file.open(fileName, ios::in);
    if(file.good()==false) {
        cout<<"warning 1: no custom tiles file found! File name: "<<fileName<<endl;
        Sleep(3000);
        return -1;
    }
    else {
        string line;
        int field=0, i=tilesCount;
        while(getline(file, line)) {
            switch(field){
                case 0: character[i] = line[0]; field=1; break;
                case 1: hardness[i] = std::stoi(line); field=2; break;
                case 2: damage[i] = std::stoi(line); field=3; break;
                case 3: start[i] = std::stoi(line); field = 4; break;
                case 4: finish[i] = std::stoi(line); field = 0; i++; break;
            }
            cout<<"custom read complete"<<endl;
            Sleep(debugTime);
        }
        cout<<"**Custom tiles loaded!**\n";
        Sleep(debugTime*2);
        tilesCount+=i-tilesCount;
    }
    file.close();
    return 0;
}

int loadLevelXY(string fileName) {
    fstream file;
    file.open(fileName, ios::in);
    if(file.good()==false) {
        cout<<"error 2: level file not found! File name: "<<fileName<<endl;
        Sleep(3000);
        return 2;
    }
    file>>levelX;
    cout<<"levelX = "<<levelX<<endl;
    Sleep(debugTime*5);
    file>>levelY;
    cout<<"levelY = "<<levelY<<endl;
    Sleep(debugTime*5);
    file.close();
    return 0;
}

int loadLevel(string fileName) {
    fstream file;
    file.open(fileName, ios::in);
    if(file.good()==false) {
        cout<<"error 2: level file not found! Filename: "<<fileName<<endl;
        Sleep(3000);
        return 2;
    }
    file>>levelX;
    file>>levelY;
    file>>gravity;
    file>>jumpHeight;
    file>>movementRate;
    file>>playerPos;

    cout<<"levelX: "<<levelX<<endl<<"levelY: "<<levelY<<endl<<"gravity: "<<gravity<<endl<<"jump height: "<<jumpHeight<<endl<<"movement rate: "<<movementRate<<endl<<"player position: "<<playerPos<<endl;
    Sleep(debugTime*5);
    int tmp;
    resetPointer();
    resetTilePointer();
    for(int i=0; i<levelX*levelY; i++) {
        file>>tmp;
        *tilePointer=tmp;
        cout<<tmp;
        tilePointer++;
    }
    cout<<endl;
    file.close();
    return 0;
}

void saveLevel(string fileName) {
    fstream file;
    file.open(fileName, ios::out);

    file<<levelX<<endl;
    file<<levelY<<endl;
    file<<gravity<<endl;
    file<<jumpHeight<<endl;
    file<<movementRate<<endl;
    file<<startingPos<<endl;

    int tmp;
    resetTilePointer();
    for(int i=0; i<levelX*levelY; i++) {
        tmp=*tilePointer;
        file<<tmp<<endl;
        tilePointer++;
    }
    file.close();
}

void editorLoop() {
    while(true) {
        if(GetKeyState('D') & 0x8000) {
            resetPointer();
            levelPointer += playerPos;
            levelPointer++;
            if(((playerPos+1)%levelX==0)) {
                levelPointer--;
            }
            else {
                levelPointer->setPlayer(true);
                levelPointer--;
                levelPointer->setPlayer(false);
                playerPos++;
            }
        resetPointer();
        }
        if(GetKeyState('A') & 0x8000) {
            resetPointer();
            levelPointer += playerPos;
            levelPointer--;
            if(((playerPos-1)%levelX==levelX-1)) {
                levelPointer++;
            }
            else {
                levelPointer->setPlayer(true);
                levelPointer++;
                levelPointer->setPlayer(false);
                playerPos--;
            }
            resetPointer();
        }
        if(GetKeyState('S') & 0x8000) {
            resetPointer();
            levelPointer+=playerPos;
            if((playerPos+levelX)<(levelX*levelY)) {
                levelPointer+=levelX;
                levelPointer->setPlayer(true);
                levelPointer-=levelX;
                levelPointer->setPlayer(false);
                playerPos+=levelX;
            }
            resetPointer();
        }
        if(GetKeyState('W') & 0x8000) {
            if((playerPos-levelX)>0) {
                resetPointer();
                levelPointer+=playerPos;
                levelPointer-=levelX;
                levelPointer->setPlayer(true);
                levelPointer+=levelX;
                levelPointer->setPlayer(false);
                playerPos-=levelX;
                resetPointer();
            }
        }

        if(GetKeyState(VK_RETURN) & 0x8000) {
            setTile(selectedTile, playerPos);
            if(start[selectedTile]==1) {
                startingPos=playerPos;
            }
            setTilemap(selectedTile, playerPos);
        }
        if(GetKeyState('M') & 0x8000) {
            saveLevel(levelFileName);
        }

        Sleep(movementRate);
    }
}

void tileIdSelectorLoop() {
    while(true) {
        if(GetKeyState('1') & 0x8000) {
            selectedTile = 0;
        }
        if(GetKeyState('2') & 0x8000) {
            selectedTile = 1;
        }
        if(GetKeyState('3') & 0x8000) {
            selectedTile = 2;
        }
        if(GetKeyState('4') & 0x8000) {
            selectedTile = 3;
        }
        if(GetKeyState('5') & 0x8000) {
            selectedTile = 4;
        }
        if(GetKeyState('6') & 0x8000) {
            selectedTile = 5;
        }
        if(GetKeyState('7') & 0x8000) {
            selectedTile = 6;
        }
        if(GetKeyState('8') & 0x8000) {
            selectedTile = 7;
        }
        if(GetKeyState('9') & 0x8000) {
            selectedTile = 8;
        }
        if(GetKeyState('0') & 0x8000) {
            selectedTile = 9;
        }

        Sleep(movementRate);
    }
}

int main()
{
    customTilesFilename = "cstiles.txt";
    //###MENU
    char selection;
    cout<<"***MENU***\n";
    cout<<"1. Start level\n";
    cout<<"2. Level editor\n";
    selection = getch();
    //#######

    if(selection=='1') {

        system("cls");
        cout<<"Level filename: ";
        cin>>levelFileName;

        //load tiles
        if(readVanillaTiles()==1) {
            return 1;
        }
        readCustomTiles(customTilesFilename);

        //load level dimensions
        if(loadLevelXY(levelFileName)==2) {
            return 2;
        }

        //init
        Tile level[levelX][levelY];
        int tilemap[levelX][levelY];

        tileArrayAdress = &tilemap[0][0];
        levelArrayAdress = &level[0][0]; //It will be used to reset pointer to &level[0][0]
        resetTilePointer();
        resetPointer();
        resetRenderPointer();
        tilemapInit();

        //load level
        if(loadLevel(levelFileName)==2) {
            return 2;
        }
        //recreate level from tilemap
        resetTilePointer();
        for(int i=0; i<levelX*levelY; i++) {
            setTile(*tilePointer, i);
            tilePointer++;
        }

        //starting player position
        levelPointer+=playerPos;
        levelPointer->setPlayer(true);
        //############################

        resetPointer();

        //start render thread
        system("cls");
        std::thread renderThread(render);

        //start player movement thread
        std::thread gameThread(gameLoop);

        while(true) {
            if(gameOver==true) {
                system("cls");
                cout<<"Game Over!\n"<<"inputs list:\n";
                cin>>inputHistory;
            }
            else if(victory==true) {
                system("cls");
                cout<<"You won!\n"<<"inputs list:\n";
                cin>>inputHistory;
            }
            Sleep(100);
        }

    }
    else if(selection=='2') {
        system("cls");
        cout<<"1. Create new level\n";
        cout<<"2. Load existing level\n";
        selection=getch();
        if(selection=='1') {
            system("cls");
            cout<<"Level filename: ";
            cin>>levelFileName;
            cout<<"\nLevel width: ";
            cin>>levelX;
            cout<<"\nLevel height: ";
            cin>>levelY;
            cout<<"\nGravity Strength: ";
            cin>>gravity;
            cout<<"\nJump height: ";
            cin>>jumpHeight;
            cout<<"\nMovement rate (higher means slower movement): ";
            cin>>movementRate;

            //load tiles
            if(readVanillaTiles()==1) {
                return 1;
            }
            readCustomTiles(customTilesFilename);

            //init
            Tile level[levelX][levelY];
            int tilemap[levelX][levelY];

            tileArrayAdress = &tilemap[0][0];
            levelArrayAdress = &level[0][0]; //It will be used to reset pointer to &level[0][0]
            resetTilePointer();
            resetPointer();
            resetRenderPointer();
            tilemapInit();

            //starting player position
            levelPointer+=playerPos;
            levelPointer->setPlayer(true);

            //start render thread
            system("cls");
            std::thread renderThread(render);

            //start editor thread
            std::thread editorThread(editorLoop);

            //start selector thread
            std::thread selectorThread(tileIdSelectorLoop);

            editMode=true;

            while(true) {
                Sleep(1000);
            }
        }
        else if(selection=='2') {

            cout<<"Level file name: ";
            cin>>levelFileName;

            if(loadLevelXY(levelFileName)==2) {
                return 2;
            }

            //load tiles
            if(readVanillaTiles()==1) {
                return 1;
            }
            readCustomTiles(customTilesFilename);

            //init
            Tile level[levelX][levelY];
            int tilemap[levelX][levelY];

            tileArrayAdress = &tilemap[0][0];
            levelArrayAdress = &level[0][0]; //It will be used to reset pointer to &level[0][0]
            resetTilePointer();
            resetPointer();
            resetRenderPointer();
            tilemapInit();

            //load level
            loadLevel(levelFileName);

            //recreate level from tilemap
            resetTilePointer();
            for(int i=0; i<levelX*levelY; i++) {
                setTile(*tilePointer, i);
                tilePointer++;
            }


            //starting player position
            levelPointer+=playerPos;
            levelPointer->setPlayer(true);

            //start render thread
            system("cls");
            std::thread renderThread(render);

            //start editor thread
            std::thread editorThread(editorLoop);

            //start selector thread
            std::thread selectorThread(tileIdSelectorLoop);

            editMode=true;

            while(true) {
                Sleep(1000);
            }
        }
    }

    cout<<"error 3: non-existing option selected";
    Sleep(2000);
    return 3;
}
