#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


void Peach::doSomething(){
int keyVal;
Actor* isCon;
StudentWorld* p = GetWorld();
    double newX, newY;
    string actType;
    double currX = getX();
    double currY = getY();
    if (amIDead()) return;
    else{
        if (starPwr) {
            gameTicks--;
            if (gameTicks == 0) starPwr = false;
        }
        if (temp_invc) {
            gameTicksTemp--;
        if (gameTicksTemp <= 0) temp_invc = false;
        }
        if (rechargeTime > 0) rechargeTime--;
        isCon = p->isConflict(this, currX, currY, 3);
        if (isCon && isCon->is_enemy() && (jumpPwr || shootPwr)) temp_invc = true;
           if (isCon) isCon->bonk();
        if (remJumdist > 0) {
                newX = currX;
                newY = currY + 4;
                isCon = p->isConflict(this, newX, newY, 1);
                if (isCon){
                    isCon->bonk();
                    remJumdist = 0;
                    
                }
                else {
                    moveTo(newX, newY);
                    remJumdist--;
                }
        }
            else {
                newX = currX;
                newY = currY - 3;
                isCon = p->isConflict(this, newX, newY, 1);
                if (isCon == nullptr) moveTo(newX, newY-1);
            }
           
        }
bool validKey = p->getKey(keyVal);
    if (validKey) {
        if (keyVal == KEY_PRESS_LEFT){
            remJumdist = 0;
            setDirection(180);
            newX = currX - 4;
            newY = currY;
            isCon = p->isConflict(this, newX, newY, 1);
            if (isCon) isCon->bonk();
            else moveTo(newX, newY);
        }
        else if (keyVal == KEY_PRESS_RIGHT){
            remJumdist = 0;
            setDirection(0);
            newX = currX + 4;
            newY = currY;
            isCon = p->isConflict(this, newX, newY, 1);
            if (isCon) isCon->bonk();
            else moveTo(newX, newY);
        }
        else if (keyVal == KEY_PRESS_UP){
           double  belowX = currX;
           double  belowY = currY -1;
            isCon = p->isConflict(this, belowX, belowY, 1);
            if (isCon){
                if (jumpPwr) remJumdist = 12;
                else remJumdist = 8;
                p->playSound(SOUND_PLAYER_JUMP);
                
            }
        }
    
        else if (keyVal == KEY_PRESS_SPACE){
            if (shootPwr && rechargeTime == 0){
                double fbx, fby;
                int d = getDirection();
                fby = getY();
                fbx = getX();
                p->playSound(SOUND_PLAYER_FIRE);
                rechargeTime = 8;
                if (d == 0) fbx = fbx + 4;
                else fbx = fbx - 4;
                PeachFB* fbptr = new PeachFB (fbx, fby, d);
                fbptr->SetWorld(p);
                p->addActor(fbptr);
            }
        
        }
        }
    }


void Koopa::doSomething(){
    if (amIDead()) return;
    else{
        Actor* isCon;
        Actor* con;
        StudentWorld* p = GetWorld();
        double newX, newY, tempX, tempY;
        double currX = getX();
        double currY = getY();
        isCon = p->isConflict(this, currX, currY, 0);
        if (isCon) isCon->bonk();
        else {
            int Kdir = getDirection();
            if (Kdir == 0) newX = currX + 1;
            else newX = currX - 1;
            newY = currY;
            con = p->isConflict(this, newX, newY, 1);
            if (con) setDirection(Kdir + 180);
            else {
                if (Kdir == 0){
                     tempX = currX + SPRITE_WIDTH;
                     tempY = currY - SPRITE_HEIGHT;
                }
                else{
                     tempX = currX - SPRITE_WIDTH;
                     tempY = currY - SPRITE_HEIGHT;
                }
                    Actor* tempCon = p->isConflict(this, tempX, tempY, 1);
                    if (tempCon == nullptr) setDirection(Kdir + 180);
            }
            Kdir = getDirection();
            currX = getX();
            currY = getY();
            if (Kdir == 0) newX = currX +1;
            else newX = currX - 1;
            newY = currY;
            con = p->isConflict(this, newX, newY, 1);
            if (con == nullptr) moveTo(newX, newY);
        }
            
    }
}

void Koopa::bonk(){
    if (amIDead()) return;
    StudentWorld* koopWrld = GetWorld();
    Peach* p = koopWrld->ptrTopeach();
    if(p->has_star_power()){
    koopWrld->playSound(SOUND_PLAYER_KICK);
    koopWrld->increaseScore(100);
    SetDead();
    Shell* newShell = new Shell(getX(), getY(), getDirection());
    newShell->SetWorld(koopWrld);
    koopWrld->addActor(newShell);
    }
}



void Peach::bonk(){
    if (amIDead()) return;
    if (!starPwr && !temp_invc){
        hitPts--;
        gameTicksTemp = 10;
        temp_invc = true;
        if (shootPwr) shootPwr = false;
        if (jumpPwr) jumpPwr = false;
        if (hitPts > 0) GetWorld()->playSound(SOUND_PLAYER_HURT);
        else SetDead();
        
    }
}

void Block::bonk() {
    Goodie goo = b_g;
StudentWorld *p = GetWorld();
if (goo == none) p->playSound(SOUND_PLAYER_BONK);
else if (rel_goodie) p->playSound(SOUND_PLAYER_BONK);
else {
    p->playSound(SOUND_POWERUP_APPEARS);
    if (goo == flower) {
      Flower* newFlower = new Flower(getX(), getY()+8);
      newFlower->SetWorld(p);
      p->addActor(newFlower);
    } else if (goo == star) {
      Star* newStar = new Star(getX(), getY()+8);
      newStar->SetWorld(p);
      p->addActor(newStar);
    }
     else  {
      Mushroom* newMush = new Mushroom(getX(), getY()+8);
      newMush->SetWorld(p);
      p->addActor(newMush);
    }
    rel_goodie = true;
}
}

void Pipe::doSomething(){}

void Flag::doSomething(){
    if (amIDead()) return;
    else{
        Actor* isCon;
        StudentWorld* p = GetWorld();
        double currX = getX();
        double currY = getY();
        isCon = p->isConflict(this, currX, currY, 0);
        if (isCon){
                p->increaseScore(1000);
                SetDead();
                p->advanceToNextLevel();
            }

}
}
void Mario::doSomething(){
    if (amIDead()) return;
    else{
        Actor* isCon;
        StudentWorld* p = GetWorld();
        double currX = getX();
        double currY = getY();
        isCon = p->isConflict(this, currX, currY, 0);
        if (isCon){
                p->increaseScore(1000);
                SetDead();
                p->set_player_won();
            }

}
}
    

void Flower::doSomething(){
    if (amIDead()) return;
    Actor* isCon;
    StudentWorld* p = GetWorld();
    Peach* pp = p->ptrTopeach();
    double currX = getX();
    double currY = getY();
    double tempX;
    double tempY;
    double newX;
    double newY;
    isCon = p->isConflict(this, currX, currY, 0);
    if (isCon){
        p->increaseScore(50);
        pp->setShootPwr();
        pp->incrhitPts(2);
        SetDead();
        p->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    tempX = currX;
    tempY = currY - 2;
    Actor* tempCon = p->isConflict(this, tempX, tempY, 1);
    if (tempCon == nullptr) moveTo(tempX, tempY);
    newX = getX();
    newY = getY();
    int Kdir = getDirection();
    if (Kdir == 0) newX = newX + 2;
    else newX = newX - 2;
    tempCon =  p->isConflict(this, newX, newY, 1);
    if (tempCon) setDirection(Kdir+180);
    else moveTo(newX, newY);
}


void Mushroom::doSomething(){
    if (amIDead()) return;
    Actor* isCon;
        StudentWorld* p = GetWorld();
        Peach* pp = p->ptrTopeach();
        double currX = getX();
        double currY = getY();
        double tempX;
        double tempY;
        double newX;
        double newY;
        isCon = p->isConflict(this, currX, currY, 0);
        if (isCon){
            p->increaseScore(75);
            pp->setJumpPwr();
            pp->incrhitPts(2);
            SetDead();
            p->playSound(SOUND_PLAYER_POWERUP);
            return;
        }
        tempX = currX;
        tempY = currY - 2;
        Actor* tempCon = p->isConflict(this, tempX, tempY, 1);
        if (tempCon == nullptr) moveTo(tempX, tempY);
        newY = getY();
        newX = getX();
        int Kdir = getDirection();
        if (Kdir == 0) newX = newX + 2;
        else newX = newX - 2;
        tempCon =  p->isConflict(this, newX, newY, 1);
        if (tempCon) setDirection(Kdir+180);
        else moveTo(newX, newY);
    }



void Star::doSomething(){
    if (amIDead()) return;
    Actor* isCon;
       StudentWorld* p = GetWorld();
       Peach* pp = p->ptrTopeach();
       double currX = getX();
       double currY = getY();
       double tempX;
       double tempY;
       double newX;
       double newY;
       isCon = p->isConflict(this, currX, currY, 0);
       if (isCon){
           p->increaseScore(100);
           pp->setStarPwr(150);
           SetDead();
           p->playSound(SOUND_PLAYER_POWERUP);
           return;
       }
       tempX = currX;
       tempY = currY - 2;
       Actor* tempCon = p->isConflict(this, tempX, tempY, 1);
       if (tempCon == nullptr) moveTo(tempX, tempY);
       newX = getX();
       newY = getY();
       int Kdir = getDirection();
       if (Kdir == 0) newX = newX + 2;
       else newX = newX - 2;
       tempCon =  p->isConflict(this, newX, newY, 1);
       if (tempCon) setDirection(Kdir+180);
       else moveTo(newX, newY);
       
   }


void Goomba::doSomething(){
    if (amIDead()) return;
    else{
        Actor* isCon;
        Actor* con;
        StudentWorld* p = GetWorld();
        double newX, newY, tempX, tempY;
        double currX = getX();
        double currY = getY();
        isCon = p->isConflict(this, currX, currY, 0);
       if (isCon) isCon->bonk();
        else {
            int Kdir = getDirection();

            if (Kdir == 0) newX = currX + 1;
            else newX = currX - 1;
            newY = currY;
            con = p->isConflict(this, newX, newY, 1);
            if (con) setDirection(Kdir + 180);

            else {
                if (Kdir == 0){
                     tempX = currX + SPRITE_WIDTH;
                     tempY = currY - SPRITE_HEIGHT;
                }
                else{
                     tempX = currX - SPRITE_WIDTH;
                     tempY = currY - SPRITE_HEIGHT;
                }
                    Actor* tempCon = p->isConflict(this, tempX, tempY, 1);
                    if (tempCon == nullptr) setDirection(Kdir + 180);
                
            }
            Kdir = getDirection();
            currX = getX();
            currY = getY();
            if (Kdir == 0) newX = currX +1;
            else newX = currX - 1;
            newY = currY;
            con = p->isConflict(this, newX, newY, 1);
            if (con == nullptr) moveTo(newX, newY);
        }
            
    }
}


void Goomba::bonk() {
if (amIDead()) return;
    StudentWorld* goomWrld = GetWorld();
    Peach* p = goomWrld->ptrTopeach();
    if(p->has_star_power()){
    goomWrld->playSound(SOUND_PLAYER_KICK);
    goomWrld->increaseScore(100);
    SetDead();
    }
}


void Piranha::doSomething(){
    if (amIDead()) return;
    else{
       increaseAnimationNumber();
        Actor* isCon;
        StudentWorld* p = GetWorld();
        Peach* pp = p->ptrTopeach();
        double tempX, tempY;
        double currX = getX();
        double currY = getY();
        isCon = p->isConflict(this, currX, currY, 0);
       if (isCon) isCon->bonk();
       else {
           tempY = pp->getY();
           tempX = pp->getX();
           if (tempY >= currY - 1.5*SPRITE_HEIGHT && tempY <= currY + 1.5*SPRITE_HEIGHT) {
               if (tempX < currX) setDirection(180);
               else {
                   if (tempX > currX) setDirection(0);
               }
               if (fireDelay > 0) fireDelay--;
               else {
                   int d = getDirection();
                   if ((d == 0 && tempX - currX < 8*SPRITE_WIDTH) || (d == 180 && currX - tempX < 8*SPRITE_WIDTH)) {
                   PiranhaFB* newPfb = new PiranhaFB(currX, currY, d);
                   newPfb->SetWorld(p);
                   p->addActor(newPfb);
                   p->playSound(SOUND_PIRANHA_FIRE);
                   fireDelay = 40;
               }
           }
        }
    }
}
}

void Piranha::bonk(){
    if (amIDead()) return;
    StudentWorld* pWrld = GetWorld();
    Peach* p = pWrld->ptrTopeach();
    if(p->has_star_power()){
    pWrld->playSound(SOUND_PLAYER_KICK);
    pWrld->increaseScore(100);
    SetDead();
    }
}


void PiranhaFB::doSomething(){
    if (amIDead()) return;
    StudentWorld* p = GetWorld();
    Actor* isCon;
    double tempX, tempY;
    double currX = getX();
    double currY = getY();
    isCon = p->isConflict(this, currX, currY, 0);
    if (isCon){
        isCon->damage();
        SetDead();
    }
    else {
        tempX = currX;
        tempY = currY - 2;
        Actor* tempCon = p->isConflict(this, tempX, tempY, 1);
        if (tempCon == nullptr) moveTo(tempX, tempY);
        currX = getX();
        currY = getY();
        int d = getDirection();
        if (d==0) tempX = currX + 2;
        else tempX = currX - 2;
        tempY = currY;
        tempCon = p->isConflict(this, tempX, tempY, 1);
        if (tempCon) SetDead();
        else moveTo(tempX, tempY);
    }
}



void PeachFB::doSomething(){
    if (amIDead()) return;
        else {
    StudentWorld* p = GetWorld();
    Actor* isCon;
    double tempX, tempY;
    double currX = getX();
    double currY = getY();
    isCon = p->isConflict(this, currX, currY, 2);
    if (isCon){
        isCon->damage();
        SetDead();
    }
    else {
        tempX = currX;
        tempY = currY - 2;
        Actor* tempCon = p->isConflict(this, tempX, tempY, 1);
        if (tempCon == nullptr) moveTo(tempX, tempY);
        currX = getX();
        currY = getY();
        int d = getDirection();
        if (d==0) tempX = currX + 2;
        else tempX = currX - 2;
        tempY = currY;
        tempCon = p->isConflict(this, tempX, tempY, 1);
        if (tempCon) SetDead();
        else moveTo(tempX, tempY);
    
    }
}
}
void Shell::doSomething(){
    if (amIDead()) return;
    StudentWorld* p = GetWorld();
    Actor* isCon;
    double tempX, tempY;
    double currX = getX();
    double currY = getY();

    isCon = p->isConflict(this, currX, currY, 2);
    if (isCon){
        isCon->damage();
        SetDead();
    }
    else {
        tempX = currX;
        tempY = currY - 2;
        Actor* tempCon = p->isConflict(this, tempX, tempY, 1);
        if (tempCon == nullptr) moveTo(tempX, tempY);
        currX = getX();
        currY = getY();
        int d = getDirection();
        if (d==0) tempX = currX + 2;
        else tempX = currX - 2;
        tempY = currY;
        tempCon = p->isConflict(this, tempX, tempY, 1);
        if (tempCon) SetDead();
        else moveTo(tempX, tempY);
    }
}

void Koopa::damage(){
   if (!amIDead()) {
    StudentWorld* koopWrld = GetWorld();
    koopWrld->increaseScore(100);
    SetDead();
    Shell* newShell = new Shell(getX(), getY(), getDirection());
    newShell->SetWorld(koopWrld);
    koopWrld->addActor(newShell);
    }
}

void Goomba::damage(){
   if (!amIDead()) {
    StudentWorld* p = GetWorld();
    p->increaseScore(100);
    SetDead();
}
}

void Piranha::damage(){
   if (!amIDead()) {
    StudentWorld* p = GetWorld();
    p->increaseScore(100);
    SetDead();
}
}

void Peach::damage(){
    if (!amIDead()) bonk();
}
