#include "map.h"

map[3][0].set(
	(int[]){NORTH, EAST, WEST, -1},
	(action[]){{NOTHING}}
);

map[2][0].set(
	(int[]){EAST, -1},
	(action[]){{STORE, 1}}
);

map[4][0].set(
	(int[]){WEST, -1},
	(action[]){{LOOT, 1}}
);

map[3][1].set(
	(int[]){SOUTH, NORTH-1},
	(action[]){{BATTLE, 1}}
);

map[3][1].set(
	(int[]){SOUTH, -1},
	(action[]){{WIN}}
);