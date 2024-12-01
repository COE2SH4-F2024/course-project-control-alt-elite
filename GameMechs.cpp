#include "GameMechs.h"

GameMechs::GameMechs()
{
    boardSizeX = 20;
    boardSizeY = 10;

    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    srand(time(NULL));
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;

    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    srand(time(NULL));
}

GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score += 1;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    int newX, newY;
    int playerLength = blockOff->getSize();

    int invalid;
    do{
        invalid = 0;

        newX = (rand() % (boardSizeX - 2)) + 1;
        newY = (rand() % (boardSizeY - 2)) + 1;

        for(int i = 0; i < playerLength; i++){
            invalid |= (newX == blockOff->getElement(i).pos->x && newY == blockOff->getElement(i).pos->y);
        }
    }while(invalid);

    food.setObjPos(newX, newY, 'O');
}

objPos GameMechs::getFoodPos() const
{
    return food;
}