#ifndef MONSTERS__H
#define MONSTERS__H

struct monster {
    const char* name;
    const char* message;
    int chance;
    int str;
};

int NUM_MONSTERS;

#define _(x,y,z,q) (monster[]) {{x,y,z,q}}

monster* MONSTERS[] = {
    _(
        "Small Rat",
        "You encounter a small rat, it is feral but it looks (mostly) harmless",
        50, 20
    ),
    _(
        "Ogre Brute",
        "A large door slams to the ground in front of you and an Ogre brute walks through the doorway. Saliva is drooling from his fanged mouth as he's hungry for fresh meat.",
        10, 80
    ),
    _(
        "Troll",
        "You are suddenly engorged with a rank smell in the air. A greenskin Troll is directly in your path and he just noticed you.",
        20, 60
    ),
    _(
        "Goblin",
        "You hear a sly snicker as a Goblin hobbles out in front of you.",
        20, 40
    ),
    _(
        "Skeleton",
        "An animated Skeleton lets loose a high pitch cackle as he readys his exposed bone arm to take a swing at you.",
        30, 50
   	),
    _(
        "Mad Lunatic",
        "You come across a Mad Lunatic, a once criminal who lost his mind in the dungeon.",
        30, 45
    ),
    _(
        "Large Spider",
        "A Large Spider lowers itself before you by a thick string of webbing.",
        30, 20
    ),
    _(
        "Small Spider",
        "A Small Spider is resting on the doornob to the next room.",
        50, 10
    ),
    _(
        "Giant Spider",
        "A Giant Spider creeps out from the dark.",
        20, 55
    ),
    _(
        "Eredran, the Frozen Dragon of the North",
        "You have found the lair of Eredran, the Frozen Dragon of the North. He's already noticed you, but it's not too late to run.",
        1, 100
    ),
    _(
        "Large Centipede",
        "A Large Centipede blocks your path.",
        20, 20
    ),
    _(
        "Succubus",
        "A Succubus fails to seduce you. She's now angered and ready to attack.",
        20, 69
    ),
    NULL
};

#undef _

#endif