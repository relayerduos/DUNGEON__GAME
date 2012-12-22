#ifndef PLAYER__H
#define PLAYER__H

struct PLAYER {
    const static int MAX_HEALTH = 100;
    const static int MAX_ITEMS  = 5;
    int health;
    int armor;
    int weapon;
    int num_items;
    item inv[MAX_ITEMS];
};

PLAYER player;

#endif