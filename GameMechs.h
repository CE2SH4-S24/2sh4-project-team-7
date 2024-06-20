#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{   
    // GameMechs is the Game Mechanism class
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;

        int boardSizeX;
        int boardSizeY;

        bool loseFlag;      // flag to determine if the player has lost
        int score;          // players score
        int playerX;        // players X pos on the board
        int playerY;        // players Y pos on the board
        objPos foodPos;     // pos of the food on the board

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();
        
        bool getExitFlagStatus();
        void setExitTrue();

        bool getLoseFlagStatus() const; 
        void setLoseFlag();

        char getInput();
        void setInput(char thisInput);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        int getScore();
        void incrementScore();

        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);

        int getPlayerX();              // returns the current X pos of player
        int getPlayerY();              // returns the current Y pos of player
        void movePlayerUp();
        void movePlayerDown();
        void movePlayerLeft();
        void movePlayerRight();



};

#endif