#include "ClothesLine.h"
#include "cocostudio/CocoStudio.h"
#include "GameManager.h"

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
	clothesLeft = (Sprite*)rootNode->getChildByName("clothesleft");
	clothesRight = (Sprite*)rootNode->getChildByName("clothesright");
	

	//Set the start positions.
	startYPosition = winSize.width;
	startXPosition_left = clothesLeft->getPositionX();
	startXPosition_right = clothesRight->getPositionX();
	clothesLeft->setPosition(startYPosition, startYPosition_left);
	clothesRight->setPosition(startYPosition, startYPosition_right);

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


void ClothesLine::update(float deltaTime)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		//Get the window size.
		auto  winSize = Director::getInstance()->getVisibleSize();

		//Move the pipes to the left.
		Vec2 currentLeftPos = clothesLeft->getPosition();
		clothesLeft->setPosition(currentLeftPos.y - currentSpeed*deltaTime, currentLeftPos.x);

		Vec2 currentRightPos = clothesRight->getPosition();
		clothesRight->setPosition(currentRightPos.y - currentSpeed*deltaTime, currentRightPos.x);
		
		//Did the x position (incorporating the sprite width) go off screen.
		if (currentLeftPos.y < -clothesRight->getBoundingBox().size.width*0.5f)
		{
			//Get the position just off screen to the right.
			float newYPos = winSize.width + clothesRight->getBoundingBox().size.width*0.5f;
			//Get a random position for the regenerated pipes.
			float xOffset = rand_0_1()*winSize.height*0.3f;

			//Set the new positionings.
			clothesLeft->setPosition(newYPos, currentLeftPos.X - xOffset);
			clothesRight->setPosition(newYPos, currentRightPos.X - xOffset);

		}
	}
}

//-------------------------------------------------------------------------

bool ClothesLine::clothesCollide(Rect collisionBoxToCheck)
{
	
	Rect modifiedClothesRight;
	modifiedClothesRight.size = clothesRight->getBoundingBox().size;
	modifiedClothesRight.origin = convertToWorldSpaceAR(clothesRight->getBoundingBox().origin);

	
	Rect modifiedClothesLeft;
	modifiedClothesLeft.size = clothesRight->getBoundingBox().size;
	modifiedClothesLeft.origin = convertToWorldSpaceAR(clothesLeft->getBoundingBox().origin);
	
	if (modifiedClothesRight.intersectsRect(collisionBoxToCheck) || modifiedClothesLeft.intersectsRect(collisionBoxToCheck))
	{
		return true;
	}

	return false;
}

void ClothesLine::reset()
{
	clothesLeft>setPosition(startYPosition, startXPosition_left);
	clothesRight->setPosition(startYPosition, startXPosition_right);

	currentSpeed = 200.0f;
}
