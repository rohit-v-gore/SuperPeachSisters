#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>
#include <list>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
    ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    Actor* isConflict(Actor* actptr, int x, int y, int conType);
    void addActor(Actor* actptr);
    Peach* ptrTopeach() {return peachptr;}
    void set_player_won(){
        player_won = true;
    }

private:
    list<Actor*> gameActors;
    Peach* peachptr;
    bool player_won;
    
};

#endif // STUDENTWORLD_H_
