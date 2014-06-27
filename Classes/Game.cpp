#include "Game.h"
USING_NS_CC;

Game::Game()
{
}


Game::~Game()
{
}

Game* Game::game = NULL;

CCScene* Game::initScenes()
{
	srand((unsigned)time( NULL ));

	m_screenWelcome = WelcomeScene::scene();
	m_screenWelcome->retain();
	m_ingameScene = InGameScene::scene();
	m_ingameScene->retain();

	m_currentSceneID = 1;
	return (CCScene *)m_screenWelcome;
	//return (CCScene *)m_ingameScene;
}

Game* Game::getInstance()
{
	if(NULL == game)
	{
		game = new Game();
	}
	return game;
}


void Game::switchScene(int sceneID)
{
	if(m_currentSceneID == sceneID)
	{
		return ;
	}

	switch(sceneID)
	{
	case 1:
		CCDirector::sharedDirector()->replaceScene(m_screenWelcome);
		break;
	case 2:
		CCDirector::sharedDirector()->replaceScene(m_ingameScene);
		break;
	}
	m_currentSceneID = sceneID;
}
