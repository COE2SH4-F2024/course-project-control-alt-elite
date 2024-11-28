#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    GMRef = thisGMRef;
    myDir = STOP;
    playerPos.pos->x = 5;
    playerPos.pos->y = 5;
    playerPos.symbol = '*';
}

Player::Player()
{
    myDir = STOP;
    playerPos.pos->x = 5;
    playerPos.pos->y = 5;
    playerPos.symbol = '*';
}

Player::Player(int xPos, int yPos, char sym)
{
    playerPos.pos->x = xPos;
    playerPos.pos->y = yPos;
    playerPos.symbol = sym;
}

Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 
    if(GMRef->getInput() != 0)  // if not null character
    {
        switch(GMRef->getInput())
        {                      
            case ' ':  // exit
                GMRef->setExitTrue();
                break;

            case 'w':
            case 'W':
                if(myDir!=DOWN && myDir!=UP){
                    myDir = UP;
                }
                break;

            case 's':
            case 'S':
                if(myDir!=DOWN && myDir!=UP){
                    myDir = DOWN;
                }
                break;

            case 'a':
            case 'A':
                if(myDir!=RIGHT && myDir!=LEFT){
                    myDir = LEFT;
                }
                break;

            case 'd':
            case 'D':
                if(myDir!=RIGHT && myDir!=LEFT){
                    myDir = RIGHT;
                }
                break;

            default:
                break;
        }
        GMRef->clearInput();
    }         
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added

enum
{
    UP, 
    DOWN,
    LEFT,
    RIGHT,
    STOP
}Dir;