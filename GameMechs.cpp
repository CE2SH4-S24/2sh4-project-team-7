#include "GameMechs.h"

GameMechs::GameMechs()
{

    input = '\0';            // initialize input to null char
    exitFlag = false;
    loseFlag = false;
    score = 0;               // initialize score to 0
    boardSizeX = 36;         
    boardSizeY = 18;         
    playerX = boardSizeX / 2;  // initializes players X pos to center of the board in X dir
    playerY = boardSizeY / 2;  // initializes players Y pos to center of the board in Y dir 
}

GameMechs::GameMechs(int boardX, int boardY)
{

    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    playerX = boardX / 2;
    playerY = boardY / 2;

}

// do you need a destructor?

GameMechs::~GameMechs() {

    //    note to self: destructor not needed for now since no dynamic memory to free as of yet that's why this is 
    //    empty but placing here in case needed later

}

bool GameMechs::getExitFlagStatus()
{
  
    return exitFlag;   // gets the exit flag status


}


char GameMechs::getInput()
{

    return input;   // gets the current input char



}

int GameMechs::getBoardSizeX()
{

    return boardSizeX;     // gets the size of the board along X axis


}

int GameMechs::getBoardSizeY()
{

    return boardSizeY;    // gets the size of the board along Y axis


}

 
void GameMechs::setExitTrue()
{

    exitFlag = true;     // sets the exit flag to true


}

void GameMechs::setInput(char this_input)
{

    input = this_input;    // sets the input char


}

void GameMechs::clearInput()
{

    input = '\0';       // clear the input char


}

int GameMechs::getScore() 
{
    return score;     // gets the current score
}

void GameMechs::incrementScore() 
{
    score++;           // increments the score by 1
}

void GameMechs::generateFood(objPos blockOff) {
    srand(static_cast<unsigned>(time(0)));   // seed the rand num generator 

    bool validPosition = false;     // flag to check for valid food pos
    while (!validPosition)
    {
        int randomX = rand() % (boardSizeX - 2) + 1;  // generates rand X pos within board excluding borders
        int randomY = rand() % (boardSizeY - 2) + 1;  // generates rand Y pos within board excluding borders  

        if (randomX != blockOff.x || randomY != blockOff.y)
        {
            foodPos.x = randomX;      // sets the X pos of the food
            foodPos.y = randomY;      // sets the Y pos of the food
            validPosition = true;     // marks the pos as valid  
        }
    }

    foodPos.symbol = 'O';    // food symbol
}

void GameMechs::getFoodPos(objPos &returnPos) 
{
    returnPos = foodPos;   // gets the pos of the food
}

int GameMechs::getPlayerX() 
{
    return playerX;       // gets the current player X pos

}

int GameMechs::getPlayerY() 
{
    return playerY;      // gets the current player Y pos

}

void GameMechs::movePlayerUp() {
    playerY = (playerY - 1 + boardSizeY) % boardSizeY;   // wraps around if moving out of bounds
    if (playerY == 0) playerY = boardSizeY - 2;          // correct pos if on the border
}

void GameMechs::movePlayerDown() {
    playerY = (playerY + 1) % boardSizeY;
    if (playerY == boardSizeY - 1) playerY = 1;
}

void GameMechs::movePlayerLeft() {
    playerX = (playerX - 1 + boardSizeX) % boardSizeX;
    if (playerX == 0) playerX = boardSizeX - 2;
}

void GameMechs::movePlayerRight() {
    playerX = (playerX + 1) % boardSizeX;
    if (playerX == boardSizeX - 1) playerX = 1;
}

bool GameMechs::getLoseFlagStatus() const  
{
    return loseFlag;    // gets the lose flag status

}

void GameMechs::setLoseFlag()              
{
    loseFlag = true;     // sets the lose flag to true

}

// Provide definitions of more member functions as required
// See Project Manual