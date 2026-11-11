# DivineBout
An experiment at building my own game with an accompanying engine in SDL2. This is a work in progress, on the to-do list
- Tune the attack hitbox and re-cut the attack/run sprites on the Brynild sheet
- Give the Dummy's attack a hitbox so it can hurt the player
- Background asset

NOTE: This game is not for profit. All of the artistic assets used in it come from elsewhere aside from the Title Screen. They can be swapped out at any point. 

The style of game being emulated in Divine Bout is an action oriented boss rush game. Focus is put on 1v1 scenarios against robust and creative enemies rather than focusing on a large amount at once.

## Controls
- Any key on the title screen starts the test level
- Left / Right: run
- Up: jump
- Space: attack
- Backspace: return to the title screen

## Building
The Visual Studio solution lives in `PRMirai/` and expects SDL2 and SDL2_image (see the include and library paths in the project properties). The game loads its PNG files from the working directory, so run it from `PRMirai/`.

With GCC or Clang:

```bash
cd PRMirai && g++ -std=c++14 *.cpp $(sdl2-config --cflags --libs) -lSDL2_image -o DivineBout
```
