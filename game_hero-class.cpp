#include <bits/stdc++.h>
struct Game_Hero{
    long h=10;
    bool z=0;
    Game_Hero(int health=10, bool Zombi=0){
        h=health;
        z=Zombi;
    }
    bool isDead(){
        return h==0;
    }
    int livePoints(){
        return h;
    }
    void damage(int damage=5){
        h-=damage;
        if (h<0){
            h=0;
        }
    }
    void heal(int health=3){
        if (h or z){
            h+=health;
        }
    }
};