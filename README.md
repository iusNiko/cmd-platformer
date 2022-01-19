# cmd-platformer
C++ platformer game running entirely in cmd

# how to compile
This is version only for linux. You need SFML library to compile it.
```
g++ -c main.cpp tile.cpp level.cpp
g++ main.o tile.o level.o -o platformer -lsfml-window -pthread -lX11
```

# cmd optimalization
I reccomend using gnome terminal, xfce terminal or similar to those.

# creating levels
+ and - on numpad changes tile.
M key saves file.

