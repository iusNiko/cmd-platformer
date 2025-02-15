# cmd-platformer
C++ platformer game running entirely in cmd

# how to compile
This is version only for linux. You need SFML library to compile it.
```
g++ -c main.cpp tile.cpp level.cpp
g++ main.o tile.o level.o -o platformer -lsfml-window -pthread -lX11
```

# cmd optimalization
I suggest using terminal app with GPU acceleration for the best effect.

# creating levels
To change tiles, use + and - on numpad.
M key saves file.

