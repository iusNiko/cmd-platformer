#include "tile.h"

using namespace std;

Tile::Tile(string tileId, char displayCharacter, int blockHardness, bool isDangerous, bool isStart, bool isFinish) {
    id=tileId;
    character=displayCharacter;
    hardness=blockHardness;
    damage=isDangerous;
    start=isStart;
    finish=isFinish;
}

string Tile::getId() {
  return id;
}

char Tile::getCharacter() {
    return character;
}

int Tile::getHardness() {
    return hardness;
}

bool Tile::getDamage() {
    return damage;
}

bool Tile::getStart() {
    return start;
}

bool Tile::getFinish() {
    return finish;
}

//#############################

void Tile::setId(string tileId) {
  id = tileId;
}

void Tile::setCharacter(char displayCharacter) {
    character=displayCharacter;
}

void Tile::setHardness(int blockHardness) {
    hardness=blockHardness;
}

void Tile::setDamage(bool isDangerous) {
    damage=isDangerous;
}

void Tile::setStart(bool isStart) {
    start=isStart;
}

void Tile::setFinish(bool isFinish) {
    finish=isFinish;
}

void Tile::setTile(string tileId, char displayCharacter, int blockHardness, bool isDangerous, bool isStart, bool isFinish) {
    id=tileId;
    character=displayCharacter;
    hardness=blockHardness;
    damage=isDangerous;
    start=isStart;
    finish=isFinish;
}
