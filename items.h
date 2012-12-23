#ifndef ITEMS__H
#define ITEMS__H

enum ITEM_TYPE {
    POTION
};

struct item {
    ITEM_TYPE type;
    int value;
};

void get_loot(int str) {
    // 50% chance of equipment
    if (rand() % 2 == 0) {
        bool armor = rand() % 2 == 0? true: false;
        int get_str = str / 10;

        printf("You get %s+%d %s!\n", armor? "": "a ", get_str, armor? "armor": "weapon");

        if (
            (armor  && player.armor >= get_str) ||
            (!armor && player.weapon >= get_str)  
        ) {
            printf("... Too bad that doesn't help you\n");
        } else {
            if (armor) player.armor  = get_str;
            else       player.weapon = get_str;
        }
    }

    // also 50% chance of potion
    if (rand() % 2 == 0) {
        int get_str = (rand() % 100 - (100 - str));
        get_str = get_str > 100? 100: get_str;
        item temp = {POTION, get_str};

        if (get_str > 0) {
            printf("You get a potion of heal %d!\n", get_str);

            if (player.num_items >= player.MAX_ITEMS)
                printf("... Too bad your inventory is full.\n");

            player.inv[player.num_items++] = temp;
        }
    }
}

#endif