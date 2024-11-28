#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    GMRef = thisGMRef;
    myDir = STOP;
    playerPos.pos->x = GMRef->getBoardSizeX()/2;
    playerPos.pos->y = GMRef->getBoardSizeY()/2;
    playerPos.symbol = '@';
}

Player::Player()
{
    myDir = STOP;
    playerPos.pos->x = 10;
    playerPos.pos->y = 5;
    playerPos.symbol = '@';
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
    if(myDir==UP){
        playerPos.pos->y -= 1;
        if(playerPos.pos->y < 1){
            playerPos.pos->y = GMRef->getBoardSizeY() - 2;
        }
    }
    else if(myDir==DOWN){
        playerPos.pos->y += 1;
        if(playerPos.pos->y == GMRef->getBoardSizeY() - 1){
            playerPos.pos->y = 1;
        }
    }
    else if(myDir==LEFT){
        playerPos.pos->x -= 1;
        if(playerPos.pos->x < 1){
            playerPos.pos->x = GMRef->getBoardSizeX() - 2;
        }
    }
    else if(myDir==RIGHT){
        playerPos.pos->x += 1;
        if(playerPos.pos->x == GMRef->getBoardSizeX() - 1){
            playerPos.pos->x = 1;
        }
    }
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