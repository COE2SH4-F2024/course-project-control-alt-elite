#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    GMRef = thisGMRef;
    myDir = STOP;
    score = 0;

    playerPosList = new objPosArrayList;
    int x = GMRef->getBoardSizeX()/2;
    int y = GMRef->getBoardSizeY()/2;
    playerPosList->insertHead(objPos(x, y, '*'));
}

Player::Player()
{
    myDir = STOP;
    score = 0;

    playerPosList = new objPosArrayList;
    playerPosList->insertHead(objPos(10, 5, '*'));
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
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
    if(myDir != STOP){
        int oldX = playerPosList->getHeadElement().pos->x;
        int oldY = playerPosList->getHeadElement().pos->y;

        int newX = oldX;
        int newY = oldY;

        // PPA3 Finite State Machine logic
        if(myDir==UP){
            if(oldY < 2){
                newY = GMRef->getBoardSizeY() - 2;
            }
            else{
                newY -= 1;
            }
        }
        else if(myDir==DOWN){
            if(oldY == GMRef->getBoardSizeY() - 2){
                newY = 1;
            }
            else{
                newY += 1;
            }
        }
        else if(myDir==LEFT){
            if(oldX < 2){
                newX = GMRef->getBoardSizeX() - 2;
            }
            else{
                newX -= 1;
            }
        }
        else if (myDir==RIGHT){
            if(oldX == GMRef->getBoardSizeX() - 2){
                newX = 1;
            }
            else{
                newX += 1;
            }
        }

        objPos newHead = objPos(newX, newY, '*');
        playerPosList->insertHead(newHead);
        
        if(GMRef->getFoodPos().isPosEqual(&newHead)){
            GMRef->generateFood(playerPosList);
            score += 1;
        }
        else{
            playerPosList->removeTail();
        }

        if(checkSelfCollision()){
            GMRef->setExitTrue();
            GMRef->setLoseFlag();
        }
    }
}

// More methods to be added

bool Player::checkSelfCollision(){
    objPos headPos = playerPosList->getHeadElement();
    int playerLength = playerPosList->getSize();

    for(int i = 1; i < playerLength; i++){
        if(playerPosList->getElement(i).isPosEqual(&headPos)){
            return true;
        }
    }

    return false;
}

int Player::getScore(){
    return score;
}

enum
{
    UP, 
    DOWN,
    LEFT,
    RIGHT,
    STOP
}Dir;