#ifndef GameManager_h
#define GameManager_h

#include <stdio.h>

class GameManager
{
public:
	static GameManager* sharedGameManager();

	void ResetScore();
	int getScore();

	bool isGameLive;

	~GameManager();

private:
	GameManager();
	static GameManager* instance;

	int score;
};

#endif 

