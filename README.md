# CasioBasic
Mish-mash of code written in Casio Basic. Written for the fx-9860GII, might work on other calculators, not really sure.

Also, */sdkC/* now contains projects written in C with the Casio fx-9860G SDK, this code *obviously* runs at least 100x faster than Casio Basic, and frankly a lot easier to write, in a language with more reasonable syntax.

## File Types
- **.g1m** - Full "compiled" (formatted) file to be added to your calculator through the cable and [CASIO FA-124](https://edu.casio.com/forteachers/er/software/) (scroll to "Program Link Software"). Will create several files upon installation onto the calculator.
- **.bide** - Full plain-text file meant for use when opening the file using [BIDE](https://www.planet-casio.com/Fr/logiciels/voir_un_logiciel_casio.php?showid=118) (by Zezombye, requires Java).
- **.casiobasic** - An imaginary file type for the individual programs that will be extracted once installed onto your calculator; but in plain-text.
- **.g1a** - Compiled C program for calcuator (a little more nuanced install, still using FA-124)
- **.c** - ... It's a C source file.

## Programs
- **galaxy**, a basic "destroy the asteroids and upgrade your ship" kind of game. It runs very slowly, both because of the high amount of objects, and the inefficiency of the code. The game is unfinished and lacking of ship upgrades, but it's the first game that really showed me you can do some impressive stuff with Casio Basic.
- **sdkC/Raycast**, A raycasted 3d engine, runs at a *decent* fps, my first attempt with using the Casio fx-9860G SDK.
- **sdkC/Tetris**, Soviet block game
