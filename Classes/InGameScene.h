#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "GameBackground.h"
#include "Game.h"
#include "ObjectPool.h"
#include "ScorePanel.h"
#include "Item.h"
#include "Particle.h"
#include "Obstacle.h"
#include "GameOverContainer.h"
USING_NS_CC;

class InGameScene : public Layer
{
private:
	static Scene* staScene;
	static InGameScene* m_instance;

	Hero* m_hero;
	float touchY;
	GameBackground* bg;
	ScorePanel* m_scorePanel;
	GameOverContainer* m_gameOverContainer;

	int m_lives;
	float m_playerSpeed;
	float m_cameraShake;
	float m_hitObstacle;
	float m_distance;
	float m_score;


	int m_gameState;

	void _shakeAnimation();

	ObjectPool* m_ItemPool;
	Array* m_foodItemArray;

	ObjectPool* m_eatParticlesPool;
	Array* m_eatParticlesArray;

	ObjectPool* m_obstaclePool;
	Array* m_obstacleArray;


	ObjectPool* m_windParticlesPool;
	Array* m_winParticlesArray;

	//************************************       
	// ����˵����Ԥ���������ļ� 
	// �� �� ֵ: void  
	// Ȩ    ��: private 
	// �� �� �ߣ�Kanefan     
	// �������ڣ�2013/10/02        
	//************************************  
	void _preloadMusic();


	void _createFoodItems();
	void _animateItems(float delta);

	//************************************       
	// ����˵���������Ե�ʳ����������Ч
	// ��    ��: Node * item ʳ��ITEM
	// ��    ��: int count ���ӵ�����
	// �� �� ֵ: void  
	// Ȩ    ��: private 
	// �� �� �ߣ�Kanefan     
	// �������ڣ�2013/10/02        
	//************************************  
	void _createEatParticles(Node* item, int count = 2);

	//************************************       
	// ����˵������ʳ����Ч��EnterFrameִ��
	// ��    ��: float delta ÿ֡���
	// �� �� ֵ: void  
	// Ȩ    ��: private 
	// �� �� �ߣ�Kanefan     
	// �������ڣ�2013/10/02        
	//************************************  
	void _animateEatParticles(float delta);

	

	//�����¸��ϰ�����ֵļ��
	float m_obstacleGapCount;

	void _initObstacle(float delta);
	void _createObstacle(int type, float distance);
	void _animateObstacles(float delta);

	ParticleSystemQuad* m_particleCoffee;
	ParticleSystemQuad* m_particleMushroom;

	float m_coffeePower;
	float m_mushroomPower;


	void _createWindParticles();
	void _animateWindParticles();

	void _disposeItem( Item* item );
	void _disposeEatParticle( Particle* particle );
	void _disposeObstacle( Obstacle* obstacle ) ;
	void _disposeWindParticle( Particle* wind ) ;

	void _showGameOver();
public:
	InGameScene(void);
	~InGameScene(void);
	CREATE_FUNC(InGameScene);
	static Scene* scene();
	static InGameScene* getInstance();
	bool init();

	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *pTouch, Event *pEvent);

	void onEnter();

	void startGame();

	void onExit();

	void update(float delta);
};

