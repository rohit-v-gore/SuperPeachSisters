#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), player_won(false)
{
    
}
StudentWorld::~StudentWorld(){
    cleanUp();
}

void StudentWorld::addActor(Actor* actptr) {
    gameActors.push_back(actptr);
}


int StudentWorld::init()
{
      ostringstream oss;
      ostringstream gtext;
      string gameText;
      string assPath = assetPath();
      oss << "level0";
      int k = getLevel();
      oss << setw(1) << k << ".txt";
      string fileName = oss.str();
    Level *g_lev = new Level(assPath);
    Level::LoadResult g_res = g_lev->loadLevel(fileName);
    if (g_res == Level::load_success){
        gtext << "Lives: "<< getLives() << " Level: " << getLevel() << " Points: " << getScore();
        for (int i = 0; i < GRID_WIDTH; i++)
            for (int j = 0; j < GRID_HEIGHT; j++){
                Level::GridEntry curr_obj = g_lev->getContentsOf(i, j);
               
                if ((curr_obj == Level::block) || (curr_obj == Level::star_goodie_block) ||
                   (curr_obj == Level::mushroom_goodie_block) || (curr_obj == Level::flower_goodie_block)) {
                    Block *newBlck = new Block(i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                    newBlck->SetWorld(this);
                    gameActors.push_back(newBlck);
                    if (curr_obj == Level::star_goodie_block) newBlck->setGoodie(3);
                    else if (curr_obj == Level::mushroom_goodie_block) newBlck->setGoodie(2);
                    else if (curr_obj == Level::flower_goodie_block) newBlck->setGoodie(1);
                    else newBlck->setGoodie(0);
                }
                else if(curr_obj == Level::peach){
                    Peach *newPch = new Peach(i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                    newPch->SetWorld(this);
                    peachptr = newPch;
                    gameActors.push_back(newPch);
                }
                else if (curr_obj == Level::koopa){
                    Koopa *newKoop = new Koopa(i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                    newKoop->SetWorld(this);
                    gameActors.push_back(newKoop);
                }
                else if (curr_obj == Level::pipe){
                    Pipe *newPipe = new Pipe(i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                    newPipe->SetWorld(this);
                    gameActors.push_back(newPipe);
                }
                else if (curr_obj == Level::flag){
                    Flag *newFlag = new Flag(i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                    newFlag->SetWorld(this);
                    gameActors.push_back(newFlag);
                }
                else if (curr_obj == Level::piranha){
                    Piranha *newPir = new Piranha(i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                    newPir->SetWorld(this);
                    gameActors.push_back(newPir);
                }
                else if (curr_obj == Level::goomba){
                    Goomba *newGoo = new Goomba(i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                    newGoo->SetWorld(this);
                    gameActors.push_back(newGoo);
                }
            }
        gameText = gtext.str();
        setGameStatText(gameText);
    }
    else {
        cerr << "Problem loading or reading file" << endl;
        exit(1);
    }
    delete g_lev;
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
      ostringstream gtext;
      string gameText;

    if (peachptr->amIDead()) {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }

    if (player_won) return GWSTATUS_PLAYER_WON;
    Actor* temp;
    list<Actor*>::iterator itr = gameActors.begin();
    while (itr != gameActors.end()){
        if ((*itr)->amIDead()){
            temp = (*itr);
            itr = gameActors.erase(itr);
            delete temp;
        }
        else itr++;
        }
    itr = gameActors.begin();
    while (itr != gameActors.end()){
        (*itr)->doSomething();
        itr++;
        
    }
    gtext << "Lives: "<< getLives() << " Level: " << getLevel() << " Points: " << getScore() << " ";
    if (peachptr->has_star_power()) gtext << "StarPower! ";
    if (peachptr->has_shoot_power()) gtext << "ShootPower! ";
    if (peachptr->has_jump_power()) gtext << "JumpPower! ";
    gameText = gtext.str();
    setGameStatText(gameText);



    return GWSTATUS_CONTINUE_GAME;

}

Actor* StudentWorld::isConflict(Actor* actptr, int x, int y, int conType){
    int checkX, checkY;
    list<Actor*>::iterator itr = gameActors.begin();
    while (itr != gameActors.end()){
        checkX = (*itr)->getX();
        checkY = (*itr)->getY();
        if (!(checkX + SPRITE_WIDTH <= x  || x + SPRITE_WIDTH <= checkX|| checkY + SPRITE_HEIGHT <= y  || y + SPRITE_HEIGHT <= checkY ) && actptr!=(*itr) && !(*itr)->amIDead()){
            if (conType == 0 && (*itr) == peachptr) return *itr;
            if (conType == 1 && (*itr)->doIblock()) return *itr;
            if (conType == 2 && (*itr) != peachptr && (*itr)->is_damageable()) return *itr;
        }
        itr++;
    }
    return nullptr;
}


void StudentWorld::cleanUp()
{
    Actor* temp;
    list<Actor*>::iterator itr = gameActors.begin();
    while (itr != gameActors.end()){
        temp = (*itr);
        itr = gameActors.erase(itr);
        delete temp;
        }
}
