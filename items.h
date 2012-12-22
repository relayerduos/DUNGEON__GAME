#ifndef ITEMS__H
#define ITEMS__H

enum ITEM_TYPE {
    POTION
};

struct item {
    ITEM_TYPE type;
    int value;
};

#endif