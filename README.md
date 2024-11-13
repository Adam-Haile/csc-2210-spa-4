# CSC 2210 - SPA 4
## Hunt the Wumpus - The Homework Heist Remix
Adam Haile, Aiden Miller, Payton Dorger

## UML
![UML](./UML.png)

## Build Instructions
The application can be standalone ran via the [csc_2210_spa_4.exe]("./csc_2210_spa_4.exe").

To build and compile yourself: 
1. Clone the repository to your local machine.
2. Open the application is CLion.
3. Go to the Build > Clean
4. Run Build > Build Project

You should now have your own standalone executable available in [cmake-build-release]("./cmake-build-debug/csc_2210_spa_4.exe")

> Debug mode can be accessed via the settings (*) menu.

## CMAKE Version
Compiled with CMAKE 3.31

## Deviations from Original Design
1. Some additional unanticipated helper methods were added (mostly in Map).
2. Additional attributes in Player to allow for cameras to operate correctly.
