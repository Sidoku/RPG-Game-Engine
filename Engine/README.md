## Add any additional notes here

_your additional notes, or things TA's and instructors should know_

## Game/Engine Publicity

**Project Website**: https://posnil.wixsite.com/dengine

## Compilation Instructions

First you need these libraries installed:

    -SDL2

    -SDL2_tff

    -SDL2_mixer

    -Pybind

    -Tkinter

    -Pillow

To run the editor:

    -Go to the Engine folder
    
    -Edit the macbuild.py file to match your python version

    -Run the command: python3 macbuild.py

    -Now run the command: python3 EditorIntergrated.py

To start the game:

    -There are 2 ways to start the game:

    -One way is to click on "Start Random Game" to play the game with random customizations generated with 3 game levels.

        -The second way to start the game is to first customize the game according to the player's liking.
            -Different customizations offered:​​
                -Customize rows and columns, interconnectivity (lower the interconnectivity higher the difficulty)
                -Players can also customize the monster count and treasure percentage wanted in the game
                -Players also get the option of picking between 2 different tile themes, 2 types of player characters to choose from, and 2 types of monsters
                -If the player wants to continue customizing the game, there is a "Customize Level" drop-down menu that will allow for adjusting the settings for individual levels.
            -After customization the player can start the game by clicking on "Start Game" and the game will start with the configured customizations.

To play the game:

    -Use WASD or Arrow keys to move around the game world.

    -To perform actions, you need to roll dice. The dice roll determines the number of actions you can perform in that turn.

    -Press the "R" key to pick up the Axe.

    -You must have the Axe to defeat the monsters. Each monster requires 1 or 2 axe kills to die.

    -Press the spacebar to enter the attack stance and then press the direction key to attack in that direction.

    -Press the "T" key to pick up the treasure.

    -The game includes a maze, and your objective is to reach the end-level door without getting killed by monsters.

## Project Hieararchy

In the future, other engineers may take on our project, so we have to keep it organized given the following requirements below. Forming some good organization habits now will help us later on when our project grows as well. These are the required files you should have

### ./Engine Directory Organization

- Docs
  - Source Code Documentation
- Assets
  - Art assets (With the Sub directories music, sound, images, and anything else)
- src
  - source code(.cpp files) The make file or any build scripts that automate the building of your project should reside here.
- include
  - header files(.h and .hpp files)
- lib
  - libraries (.so, .dll, .a, .dylib files). Note this is a good place to put SDL
- bin
  - This is the directory where your built executable(.exe for windows, .app for Mac, or a.out for Linux) and any additional generated files are put after each build.
- EngineBuild (Optional)
  - You may optionally put a .zip to you final deliverable. One should be able to copy and paste this directory, and only this directory onto another machine and be able to run the game. This is optional because for this course we will be building your projects from source. However, in the game industry it is useful to always have a build of a game ready for testers, thus a game project hieararchy would likely have this directory in a repo or other storage medium.
- ThirdParty
  - Code that you have not written if any.

**Note: For the final project you may add additional directories if you like, for example for your game which demonstrates your engine works.**

**Additional Notes:**

1. src and include should only contain ".cpp" or ".hpp" files. Why? It makes it very fast to do a backup of your game project as one example. Secondly, binary files that are generated often clutter up directories. I should not see any binaries in your repository, you may use a '.gitignore' file to help prevent this automatically.
