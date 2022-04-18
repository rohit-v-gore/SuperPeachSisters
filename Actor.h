#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor : public GraphObject{
public:
    Actor(int imageID, int startX, int startY, int dir, int depth, double size): GraphObject(imageID, startX, startY, dir, depth, size){
    }
    void SetAlive(){
        a_alive = true;
    }
    void SetDead(){
        a_alive = false;
    }
    bool amIDead(){
        return !a_alive;
    }
    virtual void bonk()=0;
    virtual void doSomething()=0;
virtual bool allow_pos_share(){ return true;}
    virtual bool is_damageable(){return true;}
    void SetWorld(StudentWorld* ptr){ myWorld = ptr;}
    StudentWorld* GetWorld() {return myWorld;}
    virtual bool doIblock()=0;
virtual bool may_contain_goodie()=0;
virtual bool is_enemy()=0;
virtual void damage(){}

private:
    bool a_alive;
    StudentWorld* myWorld;
};


class Block : public Actor {
    enum Goodie {star, mushroom, flower, none};
public:
    Block(int startX, int startY): Actor(IID_BLOCK, startX, startY, 0, 2, 1.0)
    {
        SetAlive();
        rel_goodie = false;
    }
    bool has_rel(){
        return rel_goodie;
    }

    bool may_contain_goodie() override{
        return true;
    }
    virtual bool allow_pos_share() override{
        return false;
    }
    virtual bool is_damageable() override{
        return false;
    }
    virtual void doSomething() override {}
    virtual void bonk() override;
    virtual bool doIblock() override {return true;}
    virtual bool is_enemy() override {return false;}
    Goodie getGoodie(){
        return b_g;
    }
    void setGoodie(int i) {
        if (i == 0) b_g = none;
        else if ( i==1) b_g = flower;
        else if (i == 2) b_g = mushroom;
        else if ( i == 3) b_g = star;
    }
private:
    Goodie b_g;
    bool rel_goodie;
    
    
};

class Peach : public Actor{
public:
    Peach(int startX, int startY) : Actor(IID_PEACH, startX, startY, 0, 0, 1.0),
    temp_invc(false), starPwr(false), jumpPwr(false), shootPwr(false), remJumdist(0), gameTicks(0), rechargeTime(0), gameTicksTemp(0), isJumping(false), hitPts(0)
    {
        SetAlive();
    }
    void doSomething() override;
    bool peach_invc(){
        return temp_invc; // public invincibility variable
    }
    bool has_star_power() {return starPwr;}
    bool has_jump_power() {return jumpPwr;}
    bool has_shoot_power() {return shootPwr;}
    virtual void bonk() override;
    virtual bool doIblock() override {return false;}
    bool may_contain_goodie() override{
        return false;
    }
     void setJumpPwr(){
        jumpPwr = true;
    }
    void setStarPwr (int ticks){
        starPwr = true;
        gameTicks = ticks;
    }
    void setShootPwr(){
        shootPwr = true;
    }
    void incrhitPts(int i){
        hitPts += i;
    }
    virtual bool is_enemy() override {return false;}
    void damage() override;
private:
    bool temp_invc;
    bool starPwr;
    bool jumpPwr;
    bool shootPwr;
    int remJumdist;
    int gameTicks;
    int rechargeTime;
    int gameTicksTemp;
    bool isJumping;
    int hitPts;
};

class Koopa : public Actor{
public:
    Koopa(int startX, int startY) : Actor(IID_KOOPA, startX, startY, 180 * randInt(0, 1), 0, 1.0){
        SetAlive(); // setting Koopa living status
    }
    void doSomething() override;
    virtual void bonk() override;
    virtual bool doIblock() override {return false;}
    bool may_contain_goodie() override{
        return false;
    }
    virtual bool is_enemy() override {return true;}
    void damage() override;
private:
    
    
};


class Pipe : public Actor{
public:
    Pipe(int startX, int startY) : Actor(IID_PIPE, startX, startY, 0, 2, 1.0){
        SetAlive(); // setting Koopa living status
    }
    void doSomething() override;
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return false;
    }
    virtual void bonk() override{}
    virtual bool doIblock() override {return true;}
    bool may_contain_goodie() override{
        return false;
    }
    virtual bool is_enemy() override {return false;}
private:
    
    
    
};


class Flag : public Actor{
public:
    Flag(int startX, int startY) : Actor(IID_FLAG, startX, startY, 0, 1, 1.0){
        SetAlive(); // setting flag living status
    }
    void doSomething() override;
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    bool may_contain_goodie() override{
        return false;
    }
    
    virtual void bonk() override{}
    virtual bool doIblock() override {return false;}
    virtual bool is_enemy() override {return false;}
    private:
    
};

class Mario: public Actor {
public:
    Mario(int startX, int startY) : Actor(IID_MARIO, startX, startY, 0, 1, 1.0){
        SetAlive(); // setting mario living status
    }
    
    void doSomething() override;
    
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    virtual void bonk() override{}
    virtual bool doIblock() override {return false;}
    bool may_contain_goodie() override{
        return false;
    }
    virtual bool is_enemy() override {return false;}
    private:
};

class Flower: public Actor{
public:
    Flower(int startX, int startY) : Actor(IID_FLOWER, startX, startY, 0, 1, 1.0){
        SetAlive();
    }
    
    void doSomething() override;
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    bool may_contain_goodie() override{
        return false;
    }
    virtual bool is_enemy() override {return false;}
    
    virtual void bonk() override{}
    virtual bool doIblock() override {return false;}
    private:
    
    
};

class Mushroom : public Actor{
public:
    Mushroom(int startX, int startY) : Actor(IID_MUSHROOM, startX, startY, 0, 1, 1.0){
        SetAlive();
    }
    
    void doSomething() override;
    
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    bool may_contain_goodie() override{
        return false;
    }
    virtual void bonk() override{}
    virtual bool doIblock() override {return false;}
    virtual bool is_enemy() override {return false;}
    private:
    
    
};

class Star : public Actor {
public:
    Star(int startX, int startY) : Actor(IID_STAR, startX, startY, 0, 1, 1.0){
        SetAlive();
    }
    
    void doSomething() override;
    
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    bool may_contain_goodie() override{
        return false;
    }
    virtual void bonk() override{}
    virtual bool doIblock() override {return false;}
    virtual bool is_enemy() override {return false;}
    private:
    
    
};

class Piranha : public Actor {
public:
    Piranha(int startX, int startY) : Actor(IID_PIRANHA, startX, startY, 180 * randInt(0, 1), 1, 1.0){
        SetAlive();
        setFireDelay(0);
    }
    
    void doSomething() override;
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    void setFireDelay(int fd){
        fireDelay = fd;
    }
    bool may_contain_goodie() override{
        return false;
    }
    virtual void bonk() override;
    virtual bool doIblock() override {return false;}
    virtual bool is_enemy() override {return true;}
    void damage() override;
private:
    int fireDelay;
    
};



class Goomba : public Actor {
public:
    Goomba(int startX, int startY) : Actor(IID_GOOMBA, startX, startY, 180 * randInt(0, 1), 1, 1.0){
        SetAlive();
    }
    
    void doSomething() override;
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    bool may_contain_goodie() override{
        return false;
    }
    virtual void bonk() override;
    virtual bool doIblock() override {return false;}
    virtual bool is_enemy() override {return true;}
    void damage() override;
private:
    
};



class PiranhaFB : public Actor {
public:
    PiranhaFB(int startX, int startY, int dir) : Actor(IID_PIRANHA_FIRE, startX, startY, dir, 1, 1.0){
        SetAlive();
        
    }
    
    void doSomething() override;
    
    
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    bool may_contain_goodie() override{
        return false;
    }
    virtual void bonk() override{}
    virtual bool doIblock() override {return false;}
    virtual bool is_enemy() override {return false;}
private:

};


class PeachFB : public Actor {
public:
    PeachFB(int startX, int startY, int dir) : Actor(IID_PEACH_FIRE, startX, startY, dir, 1, 1.0){
        SetAlive();
        
    }
    
    void doSomething() override;
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    bool may_contain_goodie() override{
        return false;
    }
    virtual void bonk() override{}
    virtual bool doIblock() override {return false;}
    virtual bool is_enemy() override {return false;}
private:

};





class Shell : public Actor {
public:
    Shell(int startX, int startY, int dir) : Actor(IID_SHELL, startX, startY, dir, 1, 1.0){
        SetAlive();
        
    }
    
    void doSomething() override;
    virtual bool is_damageable() override{
        return false;
    }
    virtual bool allow_pos_share() override{
        return true;
    }
    bool may_contain_goodie() override{
        return false;
    }
    virtual void bonk() override{}
    virtual bool doIblock() override {return false;}
    virtual bool is_enemy() override {return false;}
private:

};




#endif // ACTOR_H_
