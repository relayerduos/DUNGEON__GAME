#ifndef MAP__H
#define MAP__H


enum action_type {
	NOTHING,
	BATTLE,
	LOOT,
	STORE,
	MIMIC,
	NPC,
	WIN
};

struct action {
	action_type type;
	int level;
};

enum DIR {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
};

struct room {
	int exits[4];
	ACTION* action;
	bool completed;

	void set(int[] exists_inp, action* inp) {
		for (int i = 0; i < 4; i++)
			exists[i] = false;
	
		for (int i = 0; i < 4; i++) {
			if (exists_inp[i] == -1) break

			exists[exists_inp[i]] == true;
		}

		action = action_inp;
		completed = false;
	}
};

room map[5][5] = {0}; // cartesian coordinates

#endif