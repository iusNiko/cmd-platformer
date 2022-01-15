# cmd-platformer
C++ platformer game running entirely in cmd

# how to compile
You can open this as project in code::blocks and compile it, or you can use minGW64.
In both cases you need minGW64 with POSIX threads.
To compile without code::blocks, you can use following commands: 
```
g++.exe main.cpp tile.cpp
```
or
```
g++.exe main.cpp tile.cpp -static
```
for static libraries linking.

# cmd optimalization
To play this game, I recommend to set screen buffer height to 30. Otherwise, game will run painfully slow.
You can also run this game in Powershell or Terminal to get even higher performance, but of course, you will need to change screen buffer size too.

# creating levels
To create level, you need to enter editor mode. This is option 2 in main menu.
Keys from 1 to 0 allow you to select different tiles. Use enter to place tiles.
M key saves file.

# creating custom tiles
To create custom tiles, you need to edit cstiles.txt file. 
First line - character which will represent this tile in game. 
Second line - hardness of this tile (0 - non-solid, 1 - semi-solid, 2 - solid). 
Third line - will this tile kill player? 
Fourth line - is this tile a starting point? 
Fifth line - is this tile a finish? 
