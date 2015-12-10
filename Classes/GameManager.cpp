#include "GameManager.h"

GameManager* GameManager::instance = NULL;

GameManager* GameManager::sharedGameManager()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}
	return instance;
}
GameManager::GameManager()
{
	isGameLive = false;
}

GameManager::~GameManager()
{

}


