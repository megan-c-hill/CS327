Assignment 10: Megan Hill

I chose to port my rougelike game to Android.

I was able to maintain a lot of the features, but because there was a time constraint and this was more difficult than I
anticipated I did loose a few features some of which are what actually make the game interesting.

Features kept:
- Reading Description Files (kind of, it had to be significantly modified to work on Android)
- Generating Dungeon Features
- Monsters obey characteristics (including using distance maps)
- Game finishes when player or boss (Spongebob or Hardware bug is killed)
- Combat schematics (kind of, vectors were causing crashes so everyone has a damage of 10)
- Fog of War

Lost features:
- Load and save (No practical way to accomplish on Android)
- Colors
- Control player movement, and anything useful with items (Basically keyboard presses do nothing)
  Depending on when this assignment actually gets closed I might come back and try to add this in because the game is pretty boring

Things to know:
    When the game starts you will see a blank screen, then a keyboard will pop up. Press s on the keyboard to start game play.
    The board dimensions have been reduced to 17x26 in order to actually look okay on a mobile device.
    During this time the player will move around like a crazy person, with fog of war. There are objects on the floor, but there is no
    way to pick them up. When the game finishes the whole screen will be shown and all movement will be stop, but there is no message
    telling you the game is over. At this point you can press s again to start a new game.

I personally tested this on a portrait mode Pixel 2XL emulator. I did not try to make this scalable, so I'm sure it looks terrible on
almost any other device, that is not similar in dimensions. I have never tested this on a physical device, and have no idea what the result would be.

