#ifndef _GAME_HEAD
#define _GAME_HEAD

#include "cocos2d.h"
#include "WelcomeScene.h"
#include "InGameScene.h"
USING_NS_CC;

class Game
{
private:
    CCScene* m_screenWelcome;
	CCScene* m_ingameScene;
	static Game* game;
	int m_currentSceneID;
public:
	Game(void);
	CCScene* initScenes();
	~Game(void);
	static Game* getInstance();
	void switchScene(int sceneID);
};
#endif

