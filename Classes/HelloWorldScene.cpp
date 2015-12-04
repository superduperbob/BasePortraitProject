#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	this->scheduleUpdate();

	auto winSize = Director::getInstance()->getVisibleSize();

	cat = (Sprite*)rootNode->getChildByName("cat");
	background = (Sprite*)rootNode->getChildByName("background");
	background2 = (Sprite*)rootNode->getChildByName("background2");

	left = 0;

	tol = 5;

	//Set up a touch listener.
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	if (cat->getPosition().x <= 300)
	{
		left = 20;
	}

	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{	
	left = 0;
}

static const int scrollSpeed = 5.0f;

void HelloWorld::update(float delta)
{
	Vec2 Bg1Pos = background->getPosition();
	Vec2 Bg2Pos = background2->getPosition();

	background->setPosition(Bg1Pos.x, Bg1Pos.y + scrollSpeed);
	background2->setPosition(Bg2Pos.x, Bg2Pos.y + scrollSpeed);

	if (background->getPosition().y > 1400+ tol)
	{
		background->setPosition(Bg1Pos.x, -480 + scrollSpeed);
	}

	if (background2->getPosition().y > 1400 + tol)
	{
		background2->setPosition(Bg2Pos.x, -480 + scrollSpeed);
	}

	Vec2 catPos = cat->getPosition();
	cat->setPosition(catPos.x + left, catPos.y);
}

void HelloWorld::Start()
{
	auto winSize = Director::getInstance()->getVisibleSize();

	cat->setPosition(cat->getPosition().x, winSize.height*0.5f);
	left = 0;
	
}

void HelloWorld::GameOver()
{

}