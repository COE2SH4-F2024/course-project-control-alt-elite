#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

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

    // Create game mechs on heap
    game = new GameMechs(20, 10);
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
    if(game->getInput() != 0)  // if not null character
    {
        switch(game->getInput())
        {                      
            case ' ':  // exit
                game->setExitTrue();
                break;

            case 'w':
            case 'W':
                /*if(direction!=DOWN && direction!=UP){
                    direction = UP;
                }*/
                break;

            case 's':
            case 'S':
                /*if(direction!=DOWN && direction!=UP){
                    direction = DOWN;
                }*/
                break;

            case 'a':
            case 'A':
                /*if(direction!=RIGHT && direction!=LEFT){
                    direction = LEFT;
                }*/
                break;

            case 'd':
            case 'D':
                /*if(direction!=RIGHT && direction!=LEFT){
                    direction = RIGHT;
                }*/
                break;

            default:
                break;
        }
        game->clearInput();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    // Draw Screen Routine

    // Temporary
    int gameHeight = game->getBoardSizeY();
    int gameWidth = game->getBoardSizeX();

    int row, column;
    for(row = 0; row < gameHeight; row++){
        MacUILib_printf("%c", '\n');
        for(column = 0; column < gameWidth; column++){
            if(column == 0 || row == 0 || column == gameWidth - 1 || row == gameHeight - 1){
                MacUILib_printf("%c", '%');
            }
            else{
                MacUILib_printf("%c", ' ');
            }
        }
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

    MacUILib_uninit();
}
