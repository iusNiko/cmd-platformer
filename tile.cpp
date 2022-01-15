#include <iostream>
#include "tile.h"

using namespace std;

Tile::Tile(char displayCharacter, int blockHardness, bool isDangerous, bool isStart, bool isFinish, bool isPlayer) {
    character=displayCharacter;
    hardness=blockHardness;
    damage=isDangerous;
    start=isStart;
    finish=isFinish;
    player=isPlayer;
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

bool Tile::getPlayer() {
    return player;
}

//#############################

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

void Tile::setPlayer(bool isPlayer) {
    player=isPlayer;
}

void Tile::setTile(char displayCharacter, int blockHardness, bool isDangerous, bool isStart, bool isFinish, bool isPlayer) {
    character=displayCharacter;
    hardness=blockHardness;
    damage=isDangerous;
    start=isStart;
    finish=isFinish;
    player=isPlayer;
}
