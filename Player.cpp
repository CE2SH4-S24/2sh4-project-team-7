#include "Player.h"

 
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    // set the initial pos of the player in the middle of the board
    objPos startPos;
    startPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    
    playerPos = new objPosArrayList();  // initializes the player pos list
    playerPos->insertHead(startPos);     // inserts the initial pos at the head of the list

}


Player::~Player()
{
    // delete any heap members here

    delete playerPos; 

}

objPosArrayList *Player::getPlayerPos()
{
    return playerPos;
}



void Player::updatePlayerDir()    // Function to update the player's direction based on keyboard input
{
    // PPA3 input processing logic    

    char input = mainGameMechsRef->getInput();    // gets the input char from the game mechanics
    if (input != 0)
    {
        switch (input)
        {
            case 'W': 
            case 'w':
                if (myDir != DOWN) 
                myDir = UP;
                break;
            case 'A': 
            case 'a':
                if (myDir != RIGHT) 
                myDir = LEFT;
                break;
            case 'S': 
            case 's':
                if (myDir != UP) 
                myDir = DOWN;
                break;
            case 'D': 
            case 'd':
                if (myDir != LEFT) 
                myDir = RIGHT;
                break;
            case 27:                                        // ESC key to exit the game
                mainGameMechsRef->setExitTrue();
                break;
            default:
                break;
        }
    }

}

void Player::movePlayer()    // function to move the player based on the current direction
{
    // PPA3 Finite State Machine logic

    objPos headPos;
    playerPos->getHeadElement(headPos);    // gets the current head position of the player


    // Update the head position based on the current direction
    switch (myDir)
    {
        case LEFT:
            headPos.x--;
            if (headPos.x == 0) headPos.x = mainGameMechsRef->getBoardSizeX() - 2;
            break;
        case RIGHT:
            headPos.x++;
            if (headPos.x == mainGameMechsRef->getBoardSizeX() - 1) headPos.x = 1;
            break;
        case UP:
            headPos.y--;
            if (headPos.y == 0) headPos.y = mainGameMechsRef->getBoardSizeY() - 2;
            break;
        case DOWN:
            headPos.y++;
            if (headPos.y == mainGameMechsRef->getBoardSizeY() - 1) headPos.y = 1;
            break;
        case STOP:
        default:
            break;
    }


    // self-collision check
    for (int i = 1; i < playerPos->getSize(); i++)
    {
        objPos bodySegment;
        playerPos->getElement(bodySegment, i);
        if (headPos.x == bodySegment.x && headPos.y == bodySegment.y)
        {
            mainGameMechsRef->setLoseFlag();  // set the lose flag if the player collides with itself
            mainGameMechsRef->setExitTrue();  // set the exit flag to end the game
            return;
        }
    }

    playerPos->insertHead(headPos);  // insert the new head pos at the head of the list
    playerPos->removeTail();  // remove the tail position to maintain the length of the player

}

