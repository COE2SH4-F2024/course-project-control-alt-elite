#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000

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

    while(exitFlag == false)  
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

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    // Draw Screen Routine

    // Temporary
    int gameHeight = 10;
    int gameWidth = 20;

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

    MacUILib_uninit();
}
