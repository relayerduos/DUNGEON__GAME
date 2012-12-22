#include "dungeon.h"

void start() {
    srand(time(0));
    
    player.health    = player.MAX_HEALTH;
    player.armor     = 0;
    player.weapon    = 0;
    player.num_items = 0;

    int i = 0;
    NUM_MONSTERS = 0;
    while (MONSTERS[i++] != NULL) NUM_MONSTERS++;
    
    printf("You awake in a dark dungeon cellar.\n");
    printf("You have been wrongly banished to a realm of despair.\n");
    printf("You know you must get past 10 different creatures of the realm of despair to escape.\n\n");

    pause();
}

void end(bool won) {
    if (won)
        printf("You have escaped the realm of despair. Your banishment is lifted and you return a free man.\n");
    else
        printf("You are dead. Your body is forever lost in despair.\n");

    pause();
}

int count_monsters() {
    int total = 0;
    for (int i = 0; i < NUM_MONSTERS; i++)
        total += MONSTERS[i]->chance;

    return total;
}

const monster* random_monster(int monster_total, const monster* last_monster) {
    for (;;) {
        int choice = rand() % monster_total;

        int total = 0;
        for (int i = 0; i < NUM_MONSTERS; i++) {
            total += MONSTERS[i]->chance;

            if (total >= choice)
                if (last_monster == NULL || strcmp(last_monster->name, MONSTERS[i]->name))
                    return MONSTERS[i];
        }
    }
}

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

const monster* fight(int monster_total, int& encounters_left, const monster* last_monster) {
    const monster* opponent = random_monster(monster_total, last_monster);

    printf("%s\n", opponent->message);

    char buff[128];
    while (player.health > 0) {
        printf("Current life: %d\n", player.health);
        printf("Weapon: +%d, Armor: +%d\n", player.weapon, player.armor);
        printf("You're facing: %s (Power %d)\n", opponent->name, opponent->str);
        printf("Do you wish to (f)ight, (r)un, or use an (i)tem?\n");

        fgets(buff, sizeof(buff), stdin);
        clear();

        bool respond = false;
        if (tolower(buff[0]) == 'f') {
            int attack = rand() % 100 + 10 * player.weapon;

            if (attack >= opponent->str * 1.5) {
                printf("You defeat your opponent!\n");
                get_loot(opponent->str);
                printf("%d battles remain.\n", --encounters_left);
                
                pause();
                return opponent;
            } else {
                printf("You attack valiantly but your foe still stands.\n");
                respond = true;
            }
        }
        else if (tolower(buff[0]) == 'r') {
            int attempt = rand() % 100;

            if (attempt >= 60) {
                printf("You run away successfully.\n");
                printf("%d battle%s remain.\n", encounters_left, encounters_left == 0? "": "s");
                pause();

                return opponent;
            } else {
                printf("You fail to escape.\n");
                respond = true;
            }
        } else if (tolower(buff[0] == 'i')) {
            if (player.num_items == 0) {
                printf("You have no items.\n");
                pause();
            } else {
                for (;;) {
                    printf("Items:\n");

                    for (int i = 0; i < player.num_items; i++)
                        printf("    %d: Potion of heal %d\n", i + 1, player.inv[i].value);

                    printf("Which item would you like to use (or go (b)ack)?\n");

                    fgets(buff, sizeof(buff), stdin);

                    if (tolower(buff[0]) == 'b') {
                        clear();
                        break;
                    } else {
                        int choice = atoi(buff) - 1;
                        clear();

                        if (!isdigit(buff[0]) || choice < 0 || choice >= player.num_items) {
                            printf("That's not an item you have...\n");
                            pause();
                        } else {
                            printf("You drink the potion and regain %d health.\n", player.inv[choice].value);

                            player.health += player.inv[choice].value;
                            player.health = player.health > player.MAX_HEALTH? player.MAX_HEALTH: player.health;

                            for (int i = choice + 1; i < player.num_items; i++)
                                player.inv[i-1] = player.inv[i];

                            player.num_items--;

                            respond = true;
                            break;
                        }
                    }
                }
            }
        }else {
            printf("Huh?\n");
            pause();
        }


        if (respond) {
            int roll = rand() % 100 + opponent->str;

            if (roll >= 10 + player.armor * 10) {
                int damage = (opponent->str / 4) + (rand() % opponent->str / 4) - player.armor * 2;
                damage = damage < 0? 0: damage;

                if (damage == 0)
                    printf("Your opponent strikes you but your armor absorbes the blow!\n");
                else
                    printf("Your opponent strikes you! It deals %d damage.\n", damage);
    
                player.health -= damage;
            } else {
                printf("Your opponent attempts to strike you but you deftly dodge the blow.\n");
            }

            pause();
        }
    }

    return opponent;
}

void do_dungeon() {
    start();
    int encounters_left = 10;
    int monster_total = count_monsters();

    const monster* last_monster = NULL;

    while (encounters_left > 0 && player.health > 0)
        last_monster = fight(monster_total, encounters_left, last_monster);

    end (player.health > 0);
}

int main() {
    bool play = true;
    while (play) {
        do_dungeon();

        printf("Play again (y/n)?\n");

        char buff[128];
        for (;;) {
            fgets(buff, sizeof(buff), stdin);

            if (tolower(buff[0]) == 'y') {
                clear();
                break;
            }
            else if (tolower(buff[0]) == 'n') {
                play = false;
                break;
            } else {
                printf("Huh?\n");
            } 
        }
    }
 
    clear();
    return EXIT_SUCCESS;
}