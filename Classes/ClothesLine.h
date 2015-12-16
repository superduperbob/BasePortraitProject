#ifndef __CLOTHESLINE_H__
#define __CLOTHESLINE_H__

#include "cocos2d.h"

class ClothesLine : public cocos2d::Node
{
public:
	ClothesLine();
	~ClothesLine();

	virtual bool init() override;
	static ClothesLine* create();

	void         update(float);

	bool         clothesCollide(cocos2d::Rect collisionBoxToCheck);
	void         reset();

private:
	cocos2d::Sprite* clothesLeft;
	cocos2d::Sprite* clothesRight;
	
	float            startXPosition;
	float            startXPosition_left;
	float            startXPosition_right;
	float            currentSpeed;
};

#endif