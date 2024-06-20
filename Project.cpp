#include <iostream> 
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000


// Global pointers to access the player and game mechanics objects
Player *player;
GameMechs *gameMechanics;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while (!gameMechanics->getExitFlagStatus()) {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
    return 0;

}


void Initialize(void)   // Function to initialize the game
{
    MacUILib_init();  // Initialize the UI library
    MacUILib_clearScreen();  // Clear the screen
  
    gameMechanics = new GameMechs(36, 18);  // Create game mechanics object with board size 36x18
    player = new Player(gameMechanics);  // Create player object with reference to game mechanics

    // Generate food at a pos not occupied by the player
    objPos headPos;
    player->getPlayerPos()->getHeadElement(headPos);
    gameMechanics->generateFood(headPos);

}

void GetInput(void)   // Function to get user input
{
   
    if (MacUILib_hasChar()) {
        gameMechanics->setInput(MacUILib_getChar());  // Set the input character in game mechanics
    }


}

void RunLogic(void)   // Function to run game logic based on user input and game state
{

    char input = gameMechanics->getInput();
    if (input != 0)
    {
        if (input == 27) // ESC key for exit
        {
            gameMechanics->setExitTrue();
        }
        else
        {
            player->updatePlayerDir();     // Update player direction based on input
        }
        gameMechanics->clearInput();
    }

    player->movePlayer();     // Move player based on current direction


    // Collision detection with food
    objPosArrayList *playerBody = player->getPlayerPos();
    objPos headPos, foodPos;
    playerBody->getHeadElement(headPos);
    gameMechanics->getFoodPos(foodPos);

    if (headPos.x == foodPos.x && headPos.y == foodPos.y)
    {
        gameMechanics->generateFood(headPos);    // generate new food
        gameMechanics->incrementScore();         // increment score
        playerBody->insertHead(headPos);        // Extend the players body
    }
    
}

void DrawScreen(void)      // Function to draw the game screen
{
    MacUILib_clearScreen();    // Clear the screen for redrawing
    bool itemDrawn;

    objPosArrayList *playerBody = player->getPlayerPos();
    objPos bodySegment, foodPos;
    gameMechanics->getFoodPos(foodPos);

    for (int y = 0; y < gameMechanics->getBoardSizeY(); y++)
    {
        for (int x = 0; x < gameMechanics->getBoardSizeX(); x++)
        {
            itemDrawn = false;
            bool isBorder = (y == 0 || y == gameMechanics->getBoardSizeY() - 1 || x == 0 || x == gameMechanics->getBoardSizeX() - 1);

            if (foodPos.x == x && foodPos.y == y)
            {
                MacUILib_printf("%c", foodPos.symbol);     // Draw food  
                itemDrawn = true;
            }
            else
            {
                for (int i = 0; i < playerBody->getSize(); i++)
                {
                    playerBody->getElement(bodySegment, i);
                    if (bodySegment.x == x && bodySegment.y == y)
                    {
                        MacUILib_printf("%c", bodySegment.symbol);       // Draw player
                        itemDrawn = true;
                        break;
                    }
                }
            }

            if (!itemDrawn)
            {
                if (isBorder)
                {
                    MacUILib_printf("#");     // Draw border
                }
                else
                {
                    MacUILib_printf(" ");       // Draw empty space
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", gameMechanics->getScore());     // Display score
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{

    MacUILib_clearScreen();

    if (gameMechanics->getLoseFlagStatus() == true && gameMechanics->getExitFlagStatus() == true)
    {
        MacUILib_printf("You Have Lost! Final Score: %d", gameMechanics->getScore());   // prints if self collision
    }
    else
    {
        MacUILib_printf("Gamed Quitted. Final Score: %d", gameMechanics->getScore());  // otherwise if esc key pressed prints this
    }
    MacUILib_uninit();  // Uninitialize the UI library

    delete gameMechanics;  // Clean up game mechanics object
    delete player;  // Clean up player object
}
