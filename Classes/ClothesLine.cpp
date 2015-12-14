#include "ClothesLine.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;

ClothesLine* ClothesLine::create()
{
	ClothesLine* myNode = new ClothesLine();
	if (myNode->init())
	{
		myNode->autorelease();
		return myNode;
	}
	else
	{
		CC_SAFE_DELETE(myNode);
		return nullptr;
	}
	return myNode;
}

bool ClothesLine::init()
{
	if (!Node::init())
	{
		return false;
	}

	//Load this object in from cocos studio.
	auto rootNode = CSLoader::createNode("Clothes1.png");
	addChild(rootNode);

	//Position this container at left,centre. Anchor point should also be (0.0f, 0.5f).
	auto winSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(0.0f, winSize.height*0.5f));
	this->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->scheduleUpdate();


	//Set references to the Sprite objects (pipes)
	Clothes_1 = (Sprite*)rootNode->getChildByName("Clothes_1");
	

	//Set the start positions.
	startXPosition = winSize.width;
	startYPosition_top = Clothes_1->getPositionY();
	Clothes_1->setPosition(startXPosition, startYPosition_top);
	

	//Speed of pipes at start.
	currentSpeed = 200.0f;

	return true;
}


ClothesLine::ClothesLine()
{
}


ClothesLine::~ClothesLine()
{
}
