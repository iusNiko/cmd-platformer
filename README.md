# cmd-platformer
C++ platformer game running entirely in cmd

# how to compile
This is version only for linux. You need SFML library to compile it.
```
g++ -c main.cpp tile.cpp level.cpp
g++ main.o tile.o level.o -o platformer -lsfml-window -pthread -lX11
```

# cmd optimalization
To play this game, I recommend to set screen buffer height to 30. Otherwise, game will run painfully slow.
You can also run this game in Powershell or Terminal to get even higher performance, but of course, you will need to change screen buffer size too.

# creating levels
+ and - on numpad changes tile.
M key saves file.

