# SuperCoolGame

SuperCoolGame is a text based game written in C++. 

# Features

* Game can be saved and loaded at any time. Uses a custom format for saving game states.
* Fancy output using UTF8-characters for borders etc.
* ANSI coloring.
* Custom output stream handles boxes, dividers colors and automatic line wrapping. 
* Many ways to interact with the environment including talking to NPC, picking up items, equipping items etc.
* Combat with multiple targets at the same time.
* Enemies can move between rooms during the game.
* Game remembers the three latest commands entered. These can be reused by typing the corresponding number.
* Fully completable game with an engaging story :)

# Screenshots

![alt tag](http://i.imgur.com/krlIJlo.png)
![alt tag](http://i.imgur.com/u2uVCws.png)
![alt tag](http://i.imgur.com/AGvNYFL.png)
![alt tag](http://i.imgur.com/K7cFVLs.png)

Screenshots are taken in zshell on a fullscreen terminal using the Solarized Dark colortheme and the font Menlo regular. 
Most other fonts will not handle correct layout of UTF8 characters to produce good looking boxes.

# Running the game
* Enter the game folder.
* Type 'make' to build the game
* Type 'bin/Game.out' to run the game
