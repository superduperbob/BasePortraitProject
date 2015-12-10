#ifndef GameManager_h
#define GameManager_h

#include <stdio.h>

class GameManager
{
public:
	~GameManager();
	static GameManager* sharedGameManager();

	bool isGameLive;

private:
	GameManager();
	static GameManager* instance;
};

#endif 

