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

    // Temporary
    int gameHeight = game->getBoardSizeY();
    int gameWidth = game->getBoardSizeX();

    objPos currentPlayerPos = player->getPlayerPos();
    objPos currentFoodPos = game->getFoodPos();

    int row, column;
    for(row = 0; row < gameHeight; row++){
        for(column = 0; column < gameWidth; column++){
            if(column == 0 || row == 0 || column == gameWidth - 1 || row == gameHeight - 1){
                MacUILib_printf("%c", '#');
            }
            else if(row == currentPlayerPos.pos->y && column == currentPlayerPos.pos->x)
            {
                MacUILib_printf("%c", currentPlayerPos.getSymbol());
            }
            else if(row == currentFoodPos.pos->y && column == currentFoodPos.pos->x)
            {
                MacUILib_printf("%c", currentFoodPos.getSymbol());
            }
            else{
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   

    // delete game mechs from heap
    delete game;
    delete player;

    MacUILib_uninit();
}
