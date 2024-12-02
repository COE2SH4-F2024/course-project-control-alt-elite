#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Global gameMechs pointer
GameMechs* game = nullptr;
Player* player =  nullptr;

int main(void)
{

    Initialize();

    while(game->getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Create game mechs and player on heap
    game = new GameMechs(20, 10);
    player = new Player(game);

    game->generateFood(player->getPlayerPos());
}

void GetInput(void)
{
    if (MacUILib_hasChar()){
        game->setInput(MacUILib_getChar());
    }
    else{
        game->clearInput();
    }

}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    
    // Draw Screen Routine

    // Game boundaries
    int gameHeight = game->getBoardSizeY();
    int gameWidth = game->getBoardSizeX();

    // Player postition list
    objPosArrayList* currentPlayerPos = player->getPlayerPos();
    int playerLength = currentPlayerPos->getSize();

    // Food posistion
    objPos currentFoodPos = game->getFoodPos();

    bool blankFlag = true;
    for(int row = 0; row < gameHeight; row++){
        for(int column = 0; column < gameWidth; column++){
            
            // Reset blankFlag
            blankFlag = true;

            // Print boundaries
            if(column == 0 || row == 0 || column == gameWidth - 1 || row == gameHeight - 1){
                MacUILib_printf("%c", '#');
                blankFlag = false;
            }

            // Print food
            else if(row == currentFoodPos.pos->y && column == currentFoodPos.pos->x)
                {
                    MacUILib_printf("%c", currentFoodPos.getSymbol());
                    blankFlag = false;
                }

            // Otherwise print other elements
            else{
                for(int i = 0; i<playerLength; i++){
                    if(row == currentPlayerPos->getElement(i).pos->y && column == currentPlayerPos->getElement(i).pos->x)
                    {
                        MacUILib_printf("%c", currentPlayerPos->getElement(i).getSymbol());
                        blankFlag = false;
                        break;
                    }
                }
            }
            
            // If blank print space
            if(blankFlag){
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }

    // Print score
    cout << endl << "Score: " << game->getScore();
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();

    // Game end message
    if(game->getLoseFlagStatus()){
        cout << "You Lose!" << endl << endl << "Final Score: " << game->getScore() << endl;
    }
    else{
        cout << "You exited with a score of " << game->getScore() << endl;
    }

    // delete heap variables
    delete game;
    delete player;

    MacUILib_uninit();
}
