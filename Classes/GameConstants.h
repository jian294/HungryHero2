#ifndef _GAMECONSTANTS_HEAD
#define _GAMECONSTANTS_HEAD
class GameConstants
{
public:
	GameConstants(void);
	~GameConstants(void);

	static const int GAME_STATE_FLYING = 1;
	static const int GAME_STATE_OVER = 2;


	static const int HERO_LIVES = 3;

	static const int HERO_MIN_SPEED = 650;
		
	static const int HERO_MAX_SPEED = 1400;


	static const int ITEM_TYPE_1 = 1;
	static const int ITEM_TYPE_2 = 2;
	static const int ITEM_TYPE_3 = 3;
	static const int ITEM_TYPE_4 = 4;
	static const int ITEM_TYPE_5 = 5;

	static const int ITEM_TYPE_COFFEE = 6;

	static const int ITEM_TYPE_MUSHROOM = 7;

	static const int OBSTACLE_TYPE_1 = 1;
	static const int OBSTACLE_TYPE_2 = 2;
	static const int OBSTACLE_TYPE_3 = 3;
	static const int OBSTACLE_TYPE_4 = 4;

	static const int OBJECT_TYPE_ITEM = 1;
	static const int OBJECT_TYPE_PARTICLE = 2;
	static const int OBJECT_TYPE_OBSTACLE = 3;


	static const int PARTICLE_TYPE_1 = 1;
	static const int PARTICLE_TYPE_2 = 2;

	static const int OBSTACLE_GAP = 1200;
	
	static const int OBSTACLE_SPEED = 300;

};
#endif
